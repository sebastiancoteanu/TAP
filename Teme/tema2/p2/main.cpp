#include <iostream>
#include <math.h>
#include <cstdlib>

using namespace std;

int numberOfPieces = 0;

void readData(int &n, int &x, int &y) {
    cin >> n >> x >> y;
    n = 1 << n;
}

int getArea(int middleX, int middleY, int holeX, int holeY) {
    if(holeX <= middleX) {
        if(holeY <= middleY) {
            return 1;
        }
        return 2;
    }
    else {
        if(holeY <= middleY) {
            return 3;
        }
        return 4;
    }
}

void matrixImpera(int table[100][100], int leftX, int leftY, int length, int holeX, int holeY) {
    int middleX = (leftX + leftX + length) / 2, middleY = (leftY + leftY + length) / 2;
    int area = getArea(middleX, middleY, holeX, holeY);
    if(length == 0) {
        return;
    }
    numberOfPieces++;
    switch(area) {
        case 1:
            table[middleX][middleY + 1] = numberOfPieces;
            table[middleX + 1][middleY] = numberOfPieces;
            table[middleX + 1][middleY + 1] = numberOfPieces;

            matrixImpera(table, leftX, leftY, length / 2, holeX, holeY);
            matrixImpera(table, leftX, middleY + 1, length / 2, middleX, middleY + 1);
            matrixImpera(table, middleX + 1, leftY, length / 2, middleX + 1, middleY);
            matrixImpera(table, middleX + 1, middleY + 1, length / 2, middleX + 1, middleY + 1);
            break;
        case 2:
            table[middleX][middleY] = numberOfPieces;
            table[middleX + 1][middleY] = numberOfPieces;
            table[middleX + 1][middleY + 1] = numberOfPieces;

            matrixImpera(table, leftX, leftY, length / 2, middleX, middleY);
            matrixImpera(table, leftX, middleY + 1, length / 2, holeX, holeY);
            matrixImpera(table, middleX + 1, leftY, length / 2, middleX + 1, middleY);
            matrixImpera(table, middleX + 1, middleY + 1, length / 2, middleX + 1, middleY + 1);
            break;
        case 3:
            table[middleX][middleY] = numberOfPieces;
            table[middleX][middleY + 1] = numberOfPieces;
            table[middleX + 1][middleY + 1] = numberOfPieces;

            matrixImpera(table, leftX, leftY, length / 2, middleX, middleY);
            matrixImpera(table, leftX, middleY + 1, length / 2, middleX, middleY + 1);
            matrixImpera(table, middleX + 1, leftY, length / 2, holeX, holeY);
            matrixImpera(table, middleX + 1, middleY + 1, length / 2, middleX + 1, middleY + 1);
            break;
        case 4:
            table[middleX][middleY] = numberOfPieces;
            table[middleX][middleY + 1] = numberOfPieces;
            table[middleX + 1][middleY] = numberOfPieces;

            matrixImpera(table, leftX, leftY, length / 2, middleX, middleY);
            matrixImpera(table, leftX, middleY + 1, length / 2, middleX, middleY + 1);
            matrixImpera(table, middleX + 1, leftY, length / 2, middleX + 1, middleY);
            matrixImpera(table, middleX + 1, middleY + 1, length / 2, holeX, holeY);
            break;
        default:
            cout << "Error" << '\n';
    }
}

int main()
{
    int i, j, x, y, table[100][100], n;
    readData(n, x, y);
    matrixImpera(table, 0, 0, n - 1, x, y);
    system("cls");
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            cout << table[i][j] << " ";
        }
        cout << '\n';
    }
    return 0;
}
