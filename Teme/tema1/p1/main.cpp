//Se dau n cuburi cu laturile diferite două câte două. Fiecare cub are o culoare, codificată cu un
//număr de la 1 la p (p dat).
//Să se construiască un turn de înălţime maximă de cuburi în care un cub nu poate fi aşezat pe un cub
//de aceeaşi culoare sau cu latură mai mică decât a sa – O(n logn). Pe prima linie a fişierului de intrare
//se dau n şi p, iar pe următoarele linii latura şi culoarea fiecărui cub. În fişierul de ieşire se vor afişa
//înălţimea turnului obţinut şi indicele cuburilor folosite (de la bază la vârf).

#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

struct cub {
    int latura, culoare, indice;
};

void citire(int  &n, int &p, vector <cub> &cuburi) {
    cub c;
    int i;
    f >> n >> p;
    for(i = 0; i < n; i++) {
        f >> c.latura >> c.culoare;
        c.indice = i + 1;
        cuburi.push_back(c);
    }
}

int cmp(cub c1, cub c2) {
    return c1.latura > c2.latura;
}

pair <vector<cub>,int> build(int  n, int p, vector <cub> cuburi) {
    int i, h;
    vector <cub> turn;
    sort(cuburi.begin(), cuburi.end(), cmp);
    turn.push_back(cuburi[0]);
    h = cuburi[0].latura;
    for(i = 1; i < cuburi.size(); i++) {
        if(turn[turn.size() - 1].culoare != cuburi[i].culoare) {
            turn.push_back(cuburi[i]);
            h += cuburi[i].latura;
        }
    }
    return make_pair(turn, h);
}

void afis(pair <vector <cub>,int> turn) {
    int i;
    g << turn.second << '\n';
    for(i = 0; i < turn.first.size(); i++) {
        g << turn.first[i].indice << " ";
    }
}

int main()
{
    vector <cub> cuburi;
    int n, p;
    citire(n, p, cuburi);
    pair <vector<cub>,int> turn = build(n, p, cuburi);
    afis(turn);
    f.close();
    g.close();
    return 0;
}
