#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

ofstream g("date.out");

void readData(int &m, vector<string> &smallStrings, string &bigString) {
    int i;
    string sampleString;
    ifstream date;

    sampleString = '0';
    smallStrings.push_back(sampleString);
    sampleString = '1';
    smallStrings.push_back(sampleString);

    date.open("date.in");
    date >> m;
    for(i = 0; i < m; i++) {
        date >> sampleString;
        smallStrings.push_back(sampleString);
    }
    m += 2;
    date.close();

    date.open("cod.in");
    date >> bigString;
    date.close();
}

int match(string smallString, int startPosition, string bigString) {
    int i, j = 0;
    for(i = startPosition; i < startPosition + smallString.length(); i++) {
        if(smallString[j] != bigString[i]) {
            return 0;
        }
        j++;
    }
    return 1;
}

void display(int *t, string bigString, int pos) {
    if(t[pos] == -1) {
        for(int i = t[pos] + 1; i <= pos; i++) {
            g << bigString[i];
        }
        return;
    }
    display(t, bigString, t[pos]);
    g << " + ";
    for(int i = t[pos] + 1; i <= pos; i++) {
        g << bigString[i];
    }

}

void dp(int m, vector<string> smallStrings, string bigString) {
    string aux;
    int n = bigString.size(), rightIndex = 0, i, j;
    int *d = new int[n + 2](), *t = new int[n + 2];

    d[0] = 1;
    t[0] = -1;
    while(!d[n]) {
        for(i = rightIndex; i >= 0; i--) {
            if(!d[i])
                continue;
            for(j = 0; j < m; j++) {
                aux = smallStrings[j];
                if(i + aux.length() <= n && match(aux, i, bigString)) {
                    if(!d[i + aux.length()]) {
                        d[i + aux.length()] = d[i] + 1;
                        t[i + aux.length() - 1] = i - 1;
                        rightIndex = max(rightIndex, (int)(i + aux.length()));
                    }
                    else if(d[i + aux.length()] > d[i] + 1){
                        d[i + aux.length()] = d[i - 1] + 1;
                        t[i + aux.length() - 1] = i - 1;
                        rightIndex = max(rightIndex, (int)(i + aux.length()));
                    }
                }
            }
        }
    }
    display(t, bigString, n - 1);
}

int main()
{
    vector<string> smallStrings;
    string bigString;
    int numberOfStrings;
    readData(numberOfStrings, smallStrings, bigString);
    dp(numberOfStrings, smallStrings, bigString);
    return 0;
}
