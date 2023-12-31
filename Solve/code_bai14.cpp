/*
Given a convex polygon with n vertices with integer coordinates xi,yi. The vertices are listed counterclockwise and no three vertices are in a straight line. Show a way to draw a diagonal line through 2 vertices and divide the polygon into 2 parts with the least different areas.
Input data
First line: n≤10^3
Ith line in the following n lines: xi,yi, (|xi|, |yi| <= 10^9)
Result:
Contains 2 integers which are the ordinal numbers of the 2 selected peaks.
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y, index;
};

double area(vector<Point> a) {
    double s = 0;
    for (int i = 0; i < a.size(); ++i) {
        s += a[i].x * a[(i + 1) % a.size()].y - a[i].y * a[(i + 1) % a.size()].x;
    }

    return abs(s) / 2;
}

double triangleArea(Point a, Point b, Point c) {
    return abs((b.x - a.x) * (b.y + a.y) + (c.x - b.x) * (c.y + b.y) + (a.x - c.x) * (a.y + c.y)) / 2.0;
}

int main() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
        a[i].index = i + 1;
    }

    double minArea = 1e9;
    int index1, index2;
    for (int i = 0; i < n; ++i) {
        double area1 = triangleArea(a[i], a[(i + 1) % n], a[(i + 2) % n]);
        double area2 = area(a) - area1;
        if (abs(area1 - area2) < minArea) {
            minArea = abs(area1 - area2);
            index1 = a[i].index;
            index2 = a[(i + 2) % n].index;
        }
    }

    cout << index1 << " " << index2;
    return 0;
}