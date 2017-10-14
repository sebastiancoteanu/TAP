#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct interval {
    int start, finish;
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
    return i1.finish < i2.finish;
}

int intervalsAreCompatible (interval i1, interval i2) {
    if(i1.finish <= i2.start) return 1;
    return 0;
}

void getShows(vector <interval> intervals) {
    cout << '\n' << "Selected Intervals:" << '\n';
    cout << intervals[0].start << " " << intervals[0].finish << '\n';
    int lastAddedIndex = 0;
    for(int j = 1; j < intervals.size(); j++) {
        if(intervalsAreCompatible(intervals[lastAddedIndex], intervals[j])) {
            cout << intervals[j].start << " " << intervals[j].finish << '\n';
            lastAddedIndex = j;
        }
    }
}

int main()
{
    vector <interval> intervals = readData();
    sort(intervals.begin(), intervals.end(), cmp);
    getShows(intervals);
    return 0;
}
