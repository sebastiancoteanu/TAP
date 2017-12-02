/// Directions in t
/// 1 -> t[i - 1][j - 1] / 2 -> t[i - 1][j] / 3 -> t[i][j - 1]
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

void read(char *(&seq1), char *(&seq2), int penalty[27][27]) {
    int i, j, numberOfPenalties, normalPenalty;
    char *aux = new char[256], c1, c2;
    ifstream f("date.in");

    f >> aux;
    seq1 = new char[strlen(aux)];
    strcpy(seq1, aux);
    f >> aux;
    seq2 = new char[strlen(aux)];
    strcpy(seq2, aux);
    cout << "Space penalty: ";
    cin >> penalty[0][0];

    cout << "Normal penalty: ";
    cin >> normalPenalty;
    for(i = 1; i <= 26; i++) {
        for(j = 1; j <= 26; j++) {
            if(i != j) {
                penalty[i][j] = normalPenalty;
            }
            else {
                penalty[i][j] = 0;
            }
        }
    }
    cout << "Number of penalties: ";
    cin >> numberOfPenalties;
    for(i = 0; i < numberOfPenalties; i++) {
        cout << "First letter: ";
        cin >> c1;
        cout << "Second letter: ";
        cin >> c2;
        cout << "Penalty: ";
        cin >> penalty[c1 - 64][c2 - 64];
        penalty[c2 - 64][c1 - 64] = penalty[c1 - 64][c2 - 64];
    }
    f.close();
}

ofstream g("date.out");

vector<char> s1, s2;

void display(int i, int j, char *seq1, char *seq2, int **t, int penalty) {
    int posi, posj;
    if(i == 0 && j == 0) {
        g << penalty << '\n';
    }
    posi = i;
    posj = j;
    if(posi == 0) {
        posi = 1;
    }
    if(posj == 0) {
        posj = 1;
    }
    if(t[i][j] == 1) {
        display(i - 1, j - 1, seq1, seq2, t, penalty);
        s1.push_back(seq1[posi - 1]);
        s2.push_back(seq2[posj - 1]);

    }
    else if(t[i][j] == 2) {
        display(i - 1, j, seq1, seq2, t, penalty);
        s1.push_back(seq1[posi - 1]);
        s2.push_back('-');

    }
    else if(t[i][j] == 3) {
        display(i, j - 1, seq1, seq2, t, penalty);
        s1.push_back('-');
        s2.push_back(seq2[posj - 1]);
    }
}

void dp(char *seq1, char *seq2, int penalty[27][27]) {
    int n = strlen(seq1), m = strlen(seq2), i, j;
    int **d = new int*[n + 1], **t = new int*[n + 1];
    for(i = 0; i <= n; i++) {
        d[i] = new int[m + 1]();
        t[i] = new int[m + 1]();
    }
    for(i = 1; i <= n; i++) {
        d[i][0] = penalty[0][0] * i;
        t[i][0] = 2;
    }
    for(j = 1; j <= m; j++) {
        d[0][j] = penalty[0][0] * j;
        t[0][j] = 3;
    }
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= m; j++) {
            d[i][j] = d[i - 1][j - 1] + penalty[seq1[i - 1] - 64][seq2[j - 1] - 64];
            t[i][j] = 1;
            if(d[i][j] > d[i - 1][j] + penalty[0][0]) {
                d[i][j] = d[i - 1][j] + penalty[0][0];
                t[i][j] = 2;
            }
            if(d[i][j] > d[i][j - 1] + penalty[0][0]) {
                d[i][j] = d[i][j - 1] + penalty[0][0];
                t[i][j] = 3;
            }
        }
    }
    display(n, m, seq1, seq2, t, d[n][m]);
    for(i = 0; i < s1.size(); i++) {
        g << s1[i];
    }
    g << '\n';
    for(i = 0; i < s2.size(); i++) {
        g << s2[i];
    }
    g << '\n';
    g.close();
}

int main()
{
    char *seq1, *seq2;
    int penalty[27][27];
    read(seq1, seq2, penalty);
    dp(seq1, seq2, penalty);
    return 0;
}
