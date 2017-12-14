#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream g("date.out");

struct activity {
    int p, t, l;
};

void readData(int &n, vector <activity> &activities) {
    int i;
    ifstream f;
    f.open("date.in");
    f >> n;
    for(i = 0; i < n; i++) {
        activity a;
        f >> a.p >> a.t >> a.l;
        activities.push_back(a);
    }
    f.close();
}

int cmp(activity a1, activity a2) {
    return a1.t < a2.t;
}

int getMaxDeadline(vector <activity> activities) {
    int i, maxim = INT_MIN;
    for(int i = 0; i < activities.size(); i++) {
        maxim = max(maxim, activities[i].t);
        cout << activities[i].t << " ";
    }
    cout << '\n';
    return maxim;
}

void dp(vector <activity> activities) {
    int d = getMaxDeadline(activities), **B = new int*[activities.size() + 1], i, j, n = activities.size(), t;
    for(i = 0; i <= n; i++) {
        B[i] = new int[d + 1];
    }
    for(i = 0; i <= d; i++) {
        B[0][i] = 0;
    }
    for(i = 1; i <= n; i++) {
        for(j = 0; j <= d; j++) {
            t = min(j, activities[i - 1].t) - activities[i - 1].l;
            if(t < 0) {
                B[i][j] = B[i - 1][j];
            }
            else {
                B[i][j] = max(B[i - 1][j], activities[i - 1].p + B[i - 1][t]);
            }
        }
    }
    for(i = 0; i < n; i++) {
        for(j = 0; j < d; j++) {
            cout << B[i][j] << " ";
        }
        cout << '\n';
    }
}

int main()
{
    int n;
    vector <activity> activities;
    readData(n, activities);
    sort(activities.begin(), activities.end(), cmp);
    dp(activities);
    return 0;
}
