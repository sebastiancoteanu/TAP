#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

struct interval {
    int start, finish;
};

struct lecture {
    int start, finish, *nextLecture;
};

vector <interval> readData() {
    int numberOfIntervals, j;
    interval i;
    vector <interval> intervals;
    cin >> numberOfIntervals;
    for(j = 0; j < numberOfIntervals; j++) {
        cin >> i.start >> i.finish;
        intervals.push_back(i);
    }
    return intervals;
}

int cmp(interval i1, interval i2) {
    return i1.start < i2.start;
}

int intervalsAreCompatible (interval i1, interval i2) {
    if(i1.finish <= i2.start) return 1;
    return 0;
}

void displayData(vector <stack <interval> > lectureHalls) {
    cout << '\n';
    for(int j = 0; j < lectureHalls.size(); j++) {
        cout << "Lecture Hall No. " << j + 1 << " :" << '\n';
        while(!lectureHalls[j].empty()) {
            int k = 0;
            cout <<"Lecture " << ++k << " " << lectureHalls[j].top().start << " - " << lectureHalls[j].top().finish << '\n';
            lectureHalls[j].pop();
        }
        cout << '\n';
    }
}

void getMinimumNumberOfHalls(vector <interval> intervals) {
    int j, k;
    vector <stack <interval> > lectureHalls;
    for(k = 0; k < intervals.size(); k++) {
        int lectureHasBeenAdded = 0;
        for(j = 0; j < lectureHalls.size(); j++) {
            if(intervalsAreCompatible(lectureHalls[j].top(), intervals[k])) {
                lectureHalls[j].push(intervals[k]);
                lectureHasBeenAdded = 1;
                break;
            }
        }
        if(!lectureHasBeenAdded) {
            stack <interval> lectures;
            lectures.push(intervals[k]);
            lectureHalls.push_back(lectures);
        }
    }
    displayData(lectureHalls);
}

int main()
{
    vector <interval> intervals = readData();
    sort(intervals.begin(), intervals.end(), cmp);
    getMinimumNumberOfHalls(intervals);
    return 0;
}
