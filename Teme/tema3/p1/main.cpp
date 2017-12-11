#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

struct Cube {
    int len, color;
};

int cmp(Cube c1, Cube c2) {
    return c1.len > c2.len;
}

void read(vector<Cube> &cubes, int &numberOfCubes, int &numberOfColors) {
    Cube c;
    int i;
    f >> numberOfCubes >> numberOfColors;
    for(i = 0; i < numberOfCubes; i++) {
        f >> c.len >> c.color;
        cubes.push_back(c);
    }
}

void recursiveDisplay(vector<Cube> cubes, int *t, int pos) {
    if(pos == -1) {
        return;
    }
    recursiveDisplay(cubes, t, t[pos]);
    g << cubes[pos].len << " " << cubes[pos].color << '\n';
}

void dp(vector<Cube> &cubes) {
    int i, j, *d = new int[cubes.size()], *t = new int[cubes.size()], *nr = new int[cubes.size()](), maxHeight, posMax = 0, maxInNr = 0;
    for(i = 0; i < cubes.size(); i++) {
        t[i] = -1;
        d[i] = cubes[i].len;
    }
    nr[0] = 1;
    for(i = 0; i < cubes.size(); i++) {
        maxHeight = 0;
        for(j = i - 1; j >= 0; j--) {
            if(cubes[i].color != cubes[j].color && cubes[i].len != cubes[j].len) {
                if(d[j] + cubes[i].len > d[i]) {
                    t[i] = j;
                    d[i] = d[j] + cubes[i].len;
                    maxHeight = max(maxHeight, d[i]);
                }
            }
        }
        for(j = i - 1; j >= 0; j--) {
            if(cubes[i].color != cubes[j].color && cubes[i].len != cubes[j].len) {
                if(d[j] + cubes[i].len == maxHeight) {
                    nr[i]++;
                }
            }
        }
        if(d[i] > d[posMax]) {
            posMax = i;
        }
        maxInNr = max(maxInNr, nr[i]);
    }
    i = posMax;
    j = 0;
    recursiveDisplay(cubes, t, posMax);
    for(i = 0; i < cubes.size(); i++) {
        if(maxInNr == nr[i]) {
            j++;
        }
    }

    g << j << '\n';
}

int main()
{
    int numberOfCubes, numberOfColors;
    vector<Cube> cubes;
    read(cubes, numberOfCubes, numberOfColors);
    sort(cubes.begin(), cubes.end(), cmp);
    dp(cubes);
    f.close();
    g.close();
    return 0;
}
