#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

ifstream f("date.in");
ofstream g("date.out");

struct text {
    int lungime, index, indexBanda;
};

struct banda {
    int timpAcces, index;
};

struct comparator {
    bool operator()(banda b1, banda b2) {
        return b1.timpAcces > b2.timpAcces;
    }
};

void citire(vector <text> &sir, int &nrBenzi) {
    int n, i;
    text t;
    f >> n >> nrBenzi;
    for(i = 0; i < n; i++) {
        f >> t.lungime;
        t.index = i + 1;
        sir.push_back(t);
    }
}

int cmp(text t1, text t2) {
    return t1.lungime < t2.lungime;
}

int cmpIdx(text t1, text t2) {
    return t1.indexBanda < t2.indexBanda;
}

void adaugare(vector <text> sir, int nrBenzi) {
    int i, j;
    priority_queue<banda, vector<banda>, comparator> minHeap;
    banda b;
    for(i = 0; i < nrBenzi; i++) {
        b.index = i + 1;
        b.timpAcces = sir[i].lungime;
        sir[i].indexBanda = b.index;
        minHeap.push(b);
    }
    for(i = nrBenzi; i < sir.size(); i++) {
        b = minHeap.top();
        minHeap.pop();
        sir[i].indexBanda = b.index;
        b.timpAcces += (b.timpAcces + sir[i].lungime);
        minHeap.push(b);
    }
    sort(sir.begin(), sir.end(), cmpIdx);
    g << "Banda nr. " << 1 << '\n' << sir[0].index << " ";
    for(i = 1; i < sir.size(); i++ ) {
        if(sir[i].indexBanda != sir[i - 1].indexBanda) {
            g << '\n' << "Banda nr. " << sir[i].indexBanda << '\n';
        }
        g << sir[i].index << " ";
    }

}

int main()
{
    vector <text> sir;
    int nrBenzi;
    citire(sir, nrBenzi);
    sort(sir.begin(), sir.end(), cmp);
    adaugare(sir, nrBenzi);
    f.close();
    g.close();
    return 0;
}
