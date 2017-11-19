#include <fstream>
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

void citire(int &n, vector<Point> &points) {
    int i;
    f >> n;
    for(i = 0; i < n; i++) {
        Point p;
        f >> p.x >> p.y;
        points.push_back(p);
    }
}

int cmp(Point p1, Point p2) {
    return p1.x < p2.x;
}

void interclass(vector<Point> &points, int left, int mid, int right) {
    vector<Point> pts;
    int j = left, k = mid + 1;
    while(j <= mid && k <= right) {
        if(points[j].y <= points[k].y) {
            pts.push_back(points[j]);
            j++;
        }
        else {
            pts.push_back(points[k]);
            k++;
        }
    }
    while(j <= mid) {
        pts.push_back(points[j]);
        j++;
    }
    while(k <= right) {
        pts.push_back(points[k]);
        k++;
    }
}

solution divImp(vector<Point> points, int left, int right) {
    int l = right - left + 1;
    solution s;
    if(l < 4) {
        s.dist = 1000000001;
        for(int i = left; i <= right; i++) {
            for(int j = i + 1; j <= right; j++) {
                double dist = getDistBetween(points[i], points[j]);
                if(s.dist > dist) {
                    s.dist = dist;
                    s.p1 = points[i];
                    s.p2 = points[j];
                }
            }
        }
    } else {
        int mid = (left + right) / 2;
        solution s1 = divImp(points, left, mid); // solution from left
        solution s2 = divImp(points, mid + 1, right); // solution from right

        if(s1.dist <= s2.dist) {
            s = s1;
        } else {
            s = s2;
        }

        // interclass left and right side
        interclass(points, left, mid, right);

        // pts = pointsY intersected with BAND
        vector<Point> pts;
        for(int i = left; i <= right; i++) {
            double x = points[i].x - points[mid].x;
            if(fabs(x) <= s.dist) {
                pts.push_back(points[i]);
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
    vector<Point> points;
    citire(n, points);

    // sort points by x coordinate
    sort(points.begin(), points.end(), cmp);

    solution s = divImp(points, 0, n - 1);

    g << s.dist << '\n';

    f.close();
    g.close();
    return 0;
}
