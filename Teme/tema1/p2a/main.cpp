//a) n texte cu lungimile L(1),...,L(n) urmează a fi aşezate pe o bandă. Pentru a citi textul de pe poziţia
//k, trebuie citite textele de pe poziţiile 1,2,...,k. Pentru fiecare text i se cunoaşte şi frecvenţa f(i) cu care
//acesta este citit. Să se determine o modalitate de aşezare a textelor pe bandă astfel încât timpul total de
//acces să fie minimizat. Timpul total de acces pentru o așezare a textelor corespunzătoare unei
//permutări p se definește ca fiind Tn = Sum(f(pi) * (L(p1) + L(p2) + ... + L(pi))), i = 1,n
//O(n log n) Pe prima linie a fişierului de
//intrare se dă n, iar pe următoarele linii lungimea și frecvenţa fiecărui text


///Solutie
//se sorteaza descrescator dupa raportul frecventa / lungime
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

struct text {
    int lungime, frecventa, index;
};

void citire(vector <text> &sir) {
    int n, i;
    text t;
    f >> n;
    for(i = 0; i < n; i++) {
        f >> t.lungime >> t.frecventa;
        t.index = i + 1;
        sir.push_back(t);
    }
}

int cmp(text t1, text t2) {
    float x = (float)t1.frecventa / (float)t1.lungime;
    float y = (float)t2.frecventa / (float)t2.lungime;
    return x > y;
}

void detTimpTotal(vector <text> sir) {
    int i;
    sort(sir.begin(), sir.end(), cmp);
    for(i = 0; i < sir.size(); i++) {
        g << sir[i].index << " ";
    }
}

int main()
{
    vector <text> sir;
    citire(sir);
    detTimpTotal(sir);
    f.close();
    g.close();
    return 0;
}
