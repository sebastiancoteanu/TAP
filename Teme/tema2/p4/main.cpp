#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

ifstream f("cmap.in");
ofstream g("cmap.out");

struct Point {
    double x, y;
};

struct solution {
    Point p1, p2;
    double dist;
}sol;

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

int cmpY(Point p1, Point p2) {
    return p1.y < p2.y;
}

void display(int n, vector<Point> points) {
    int i;
    for(i = 0; i < n; i++) {
        g << points[i].x << " " << points[i].y << '\n';
    }
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

solution divImp(vector<Point> &pointsX, vector<Point> &pointsY, int left, int right) {
    int l = right - left + 1;
    if(l < 4) {
        sort(pointsY.begin() + left, pointsY.begin() + l, cmpY);
        for(int i = left; i <= right; i++) {
            for(int j = left + 1; j <= right; j++) {
                double dist = getDistBetween(pointsX[i], pointsX[j]);
                if(sol.dist > dist) {
                    sol.dist = dist;
                    sol.p1 = pointsX[i];
                    sol.p2 = pointsX[j];
                }
            }
        }
    } else {
        int mid = (left + right) / 2;
        solution s1 = divImp(pointsX, pointsY, left, mid); // solution from left
        solution s2 = divImp(pointsX, pointsY, mid + 1, right); // solution from right
        if(s1.dist <= s2.dist) {
            sol = s1;
        } else {
            sol = s2;
        }
        interclass(pointsY, left, mid, right);
        vector<Point> pts;
        // pts = pointsY intersected with BAND
        for(int i = left; i <= right; i++) {
            if(fabs(pointsY[i].x - pointsY[mid].x) <= sol.dist) {
                pts.push_back(pointsY[i]);
            }
        }
        for(int i = 0; i <= pts.size(); i++) {
            for(int j = i + 1; j <= i + 7; j++) {
                double dist = getDistBetween(pts[i], pts[j]);
                if(sol.dist > dist) {
                    sol.dist = dist;
                    sol.p1 = pts[i];
                    sol.p2 = pts[j];
                }
            }
        }
        return sol;
    }
}

int main()
{
    int n, i;
    sol.dist = INT_MAX;
    vector<Point> pointsX, pointsY;
    citire(n, pointsX);
    // sort pointsX by x coordinate
    sort(pointsX.begin(), pointsX.end(), cmp);
    // copy pointsX over pointsY
    for(i = 0; i < n; i++) {
        pointsY.push_back(pointsX[i]);
    }
    solution sl = divImp(pointsX, pointsY, 0, n - 1);
    g << sl.dist << '\n';
    g << sl.p1.x << " " << sl.p1.y << '\n';
    g << sl.p2.x << " " << sl.p2.y << '\n';
    f.close();
    g.close();
    return 0;
}
