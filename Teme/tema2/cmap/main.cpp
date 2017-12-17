#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cstdlib>

using namespace std;

ifstream f("cmap.in");
ofstream g("cmap.out");

struct Point {
    double x, y;
};

struct solution {
    Point p1, p2;
    double dist;
};

double getDistBetween(Point p1, Point p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

void read(int &n, vector<Point> &pointsx, vector<Point> &pointsy) {
    int i;
    f >> n;
    for(i = 0; i < n; i++) {
        Point p;
        f >> p.x >> p.y;
        pointsx.push_back(p);
        pointsy.push_back(p);
    }
}

int cmpx(Point p1, Point p2) {
    return p1.x < p2.x;
}

int cmpy(Point p1, Point p2) {
    return p1.y < p2.y;
}

void restructure(vector<Point> pointsx, vector<Point> pointsy, int left, int mid, int right, vector <Point> &pointsyLeft, vector <Point> &pointsyRight) {
    vector<Point> pts;
    int i, k = 0;
    pointsyLeft.clear();
    pointsyRight.clear();
    for(i = left; i <= right; i++) {
        if(pointsy[i].x <= pointsx[mid].x) {
            pointsyLeft.push_back(pointsy[i]);
        }
    }
    for(i = left; i <= right; i++) {
        if(pointsy[i].x > pointsx[mid].x) {
            pointsyRight.push_back(pointsy[i]);
        }
    }
}

solution divImp(vector<Point> pointsx, vector<Point> pointsy, int left, int right) {
    int l = right - left + 1, i;
    solution s;
    if(l < 4) {
        s.dist = INT_MAX;
        for(int i = left; i <= right; i++) {
            for(int j = i + 1; j <= right; j++) {
                double dist = getDistBetween(pointsx[i], pointsx[j]);
                if(s.dist > dist) {
                    s.dist = dist;
                    s.p1 = pointsx[i];
                    s.p2 = pointsx[j];
                }
            }
        }
    } else {
        int mid = (left + right) / 2;

        vector<Point> pointsyLeft, pointsyRight;
        pointsyLeft.clear();
        pointsyRight.clear();
        restructure(pointsx, pointsy, left, mid, right, pointsyLeft, pointsyRight);

        for(int i = 0; i < pointsyLeft.size(); i++) cout << pointsyLeft[i].x << " ";
        cout << '\n' << '\n';

        solution s1 = divImp(pointsx, pointsyLeft, left, mid); // solution from left
        solution s2 = divImp(pointsx, pointsyRight, mid + 1, right); // solution from right

        if(s1.dist <= s2.dist) {
            s = s1;
        } else {
            s = s2;
        }

        // pts = pointsY intersected with BAND
        vector<Point> pts;
        for(int i = left; i <= right; i++) {
            double x = pointsy[i].x - pointsx[mid].x;
            if(fabs(x) <= s.dist) {
                pts.push_back(pointsy[i]);
            }
        }

        for(int i = 0; i < pts.size(); i++) {
            for(int j = i + 1; j <= i + 7 && j < pts.size(); j++) {
                double dist = getDistBetween(pts[i], pts[j]);
                if(s.dist > dist) {
                    s.dist = dist;
                    s.p1 = pts[i];
                    s.p2 = pts[j];
                }
            }
        }
    }
    return s;
}

int main()
{
    int n;
    vector<Point> pointsx, pointsy;
    read(n, pointsx, pointsy);

    // sort pointsx by x coordinate
    sort(pointsx.begin(), pointsx.end(), cmpx);

    // sort pointsy by y coordinate
    sort(pointsy.begin(), pointsy.end(), cmpy);

    solution s = divImp(pointsx, pointsy, 0, n - 1);

    g << s.dist << '\n';

    f.close();
    g.close();
    return 0;
}
