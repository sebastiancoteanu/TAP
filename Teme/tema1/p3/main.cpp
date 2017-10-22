//Se consideră o mulţime de n activităţi
//care trebuie planificate pentru a folosi o aceeaşi resursă. Această resursă poate fi folosită de o singură
//activitate la un moment dat. Toate activităţile au aceeaşi durată (să presupunem 1). Pentru fiecare
//activitate i se cunosc termenul limită până la care se poate executa ti (raportat la ora de început 0, 1 <= ti
//<= n) şi profitul pi care se primeşte dacă activitatea i se execută la timp (cu respectarea termenului
//limită). Să se determine o submulţime de activităţi care se pot planifica astfel încât profitul total
//obţinut să fie maxim.

#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

typedef struct {
    int termenLimita, profit, index;
}activitate;

int cmp (activitate a1, activitate a2){
    return a1.profit > a2.profit;
}

void citire (vector <activitate> &activitati) {
    int n, i;
    activitate a;
    f >> n;
    for(i = 0; i < n ; i++) {
        f >> a.profit >> a.termenLimita;
        a.index = i + 1;
        activitati.push_back(a);
    }
    sort(activitati.begin(), activitati.end(), cmp);
}

void setProgramActivitati(int *&programActivitati, vector <activitate> activitati) {
    int termenLimitaMaxim = INT_MIN, i;
    for(i = 0; i < activitati.size(); i++) {
        termenLimitaMaxim = max(termenLimitaMaxim, activitati[i].termenLimita);
    }
    programActivitati = new int[termenLimitaMaxim + 1];
    for(i = 0; i <= termenLimitaMaxim; i++) {
        programActivitati[i] = i;
    }
}

int termenLiber (int *&programActivitati, int termenLimita) {
    if(termenLimita == programActivitati[termenLimita]) {
        return termenLimita;
    }
    return programActivitati[termenLimita] = termenLiber(programActivitati, programActivitati[termenLimita]);
}

void ocupaTermenLiber(int *&programActivitati, int t1, int t2) {
    programActivitati[t2] = t1;
}

void creeazaProgramActivitati (int *programActivitati, vector <activitate> activitati) {
    int i;
    for(i = 0; i < activitati.size(); i++) {
        int tL = termenLiber(programActivitati, activitati[i].termenLimita);
        if(tL > 0) {
            ocupaTermenLiber(programActivitati, tL - 1, tL);
            g << activitati[i].index << " ";
        }
    }
}

int main()
{
    vector <activitate> activitati;
    int *programActivitati;
    citire(activitati);
    setProgramActivitati(programActivitati, activitati);
    creeazaProgramActivitati(programActivitati, activitati);
    f.close();
    g.close();
    return 0;
}
