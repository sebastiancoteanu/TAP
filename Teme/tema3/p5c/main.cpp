#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ofstream g("date.out");

struct activity {
    int profit, deadline, lngth, index;
};

void readData(int &n, vector <activity> &activities) {
    int i;
    ifstream f;
    f.open("date.in");
    f >> n;
    activity ax;
    activities.push_back(ax);
    for(i = 1; i <= n; i++) {
        activity a;
        a.index = i;
        f >> a.profit >> a.deadline >> a.lngth;
        activities.push_back(a);
    }
    f.close();
}

int cmp(activity a1, activity a2) {
    return a1.deadline < a2.deadline;
}

int getMaxDeadline(vector <activity> activities) {
    int i, maxim = INT_MIN;
    for(int i = 1; i < activities.size(); i++) {
        maxim = max(maxim, activities[i].deadline);
    }
    return maxim;
}

void displaySchedule(int **B, int n, int d, vector <activity> activities) {
    if(n == 0) {
        return;
    }
    if(B[n][d] == B[n - 1][d]) {
        displaySchedule(B, n - 1, d, activities);
    }
    else {
        int t = min(d, activities[n].deadline) - activities[n].lngth;
        displaySchedule(B, n - 1, t, activities);
        g << activities[n].index  << " ";
    }
}

void dp(vector <activity> activities) {
    int maxDeadline = getMaxDeadline(activities), **B = new int*[activities.size() + 1], i, j, n = activities.size() - 1, t;
    for(i = 0; i <= n; i++) {
        B[i] = new int[maxDeadline + 1];
    }
    for(i = 0; i <= maxDeadline; i++) {
        B[0][i] = 0;
    }
    for(i = 1; i <= n; i++) {
        for(j = 0; j <= maxDeadline; j++) {
            t = min(j, activities[i].deadline) - activities[i].lngth;
            if(t < 0) {
                B[i][j] = B[i - 1][j];
            }
            else {
                B[i][j] = max(B[i - 1][j], activities[i].profit + B[i - 1][t]);
            }
        }
    }
    g << B[n][maxDeadline] << '\n';
    displaySchedule(B, n, maxDeadline, activities);
}

int main()
{
    int n;
    vector <activity> activities;
    readData(n, activities);
    sort(activities.begin() + 1, activities.end(), cmp);
    dp(activities);
    return 0;
}
