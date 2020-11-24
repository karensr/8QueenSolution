// ConsoleApplication2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

uint64_t positionMap[64];
uint64_t solvedPositions[100];
int position = 0;

#define posY(x) (x / 8)
#define posX(x) (x % 8)

uint64_t getPositionMap(int position) {
    uint64_t pmap = 0;
    int i;
    int X = posX(position);
    int Y = posY(position);
    uint64_t val = 0xFF;

    int posx, posy;

    pmap |=  val << (Y * 8);
    
    for (i = 0; i < 8; i++) {
        pmap |= ((uint64_t)0x1) << (X + i * 8);
    }

    val = 1;
    posx = X;
    posy = Y;

    while (posx < 8 && posy < 8) {
        i = posx + posy * 8;
        pmap |= val << i;
        posy++;
        posx++;
    }

    posx = X;
    posy = Y;

    while (posx >= 0 && posy >= 0) {
        i = posx + posy * 8;
        pmap |= val << i;
        posy--;
        posx--;
    }

    posx = X;
    posy = Y;

    while (posx < 8 && posy >= 0) {
        i = posx + posy * 8;
        pmap |= val << i;
        posy--;
        posx++;
    }

    posx = X;
    posy = Y;

    while (posx >= 0 && posy < 8) {
        i = posx + posy * 8;
        pmap |= val << i;
        posy++;
        posx--;
    }

    return pmap;
}

void calcValidQpos(uint64_t map, int N) {
    uint64_t val = 1;
    for (int i = 0; i < 8; i++) {
        if (map & (val << (i + N * 8))) {
            continue;
        }
        else {
            if (N == 7) {
                solvedPositions[position + 1] = solvedPositions[position];
                solvedPositions[position] |= val << (i + N * 8);
                position++;
                return;
            }
            else {
                solvedPositions[position] |= val << (i + N * 8);
                calcValidQpos(map | positionMap[(i + N * 8)], N + 1);
                solvedPositions[position] &= ~(val << (i + N * 8));
            }
        }
    }
}

int main()
{
    for (int i = 0; i < 64; i++) {
        positionMap[i] = getPositionMap(i);
    }
    /*
    cout << "Queens positons reservation" << "\n";

    for (int i = 0; i < 64; i++) {
        uint64_t tmpmap = positionMap[i];
        cout <<"\n\n" << i << ":\n";
        for (int j = 0; j < 64; j++) {
            if ((j % 8) == 0) {
                cout << "\n";
            }
            if (tmpmap & (((uint64_t)0x1) << j)) {
                cout << "1 ";
            }
            else {
                cout << "0 ";
            }
        }
    }
    */
    calcValidQpos(0, 0);

    cout << "\n\nDetected " << position << " valid positions.\n";

    for (int i = 0; i < position; i++) {
        uint64_t tmpmap = solvedPositions[i];
        cout << "\n\n" << i << ":\n";
        for (int j = 0; j < 64; j++) {
            if ((j % 8) == 0) {
                cout << "\n";
            }
            if (tmpmap & (((uint64_t)0x1) << j)) {
                cout << "1 ";
            }
            else {
                cout << "0 ";
            }
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

