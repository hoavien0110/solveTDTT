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
    int x, y;
};

double calculateArea(vector<Point> a) {
    double s = 0;
    for (int i = 0; i < a.size(); ++i) {
        s += (a[i].x - a[(i + 1) % a.size()].x) * (a[i].y + a[(i + 1) % a.size()].y);
    }
    return abs(s) / 2;
}

double triangleArea(Point a, Point b, Point c) {
    return abs((b.x - a.x) * (b.y + a.y) + (c.x - b.x) * (c.y + b.y) + (a.x - c.x) * (a.y + c.y)) / 2.0;
}

void solve(int n, vector<Point> a) {
    double bigArea = calculateArea(a);
    int j = 1;
    int firstPoint = 0, secondPoint = 0;
    double diff = std::numeric_limits<double>::infinity();
    double currentArea = 0;

    for (int i = 0; i < n; i++) {
        while (bigArea - 2 * currentArea > 0)
        {
            if (abs(bigArea - 2 * currentArea) < diff) {
                diff = abs(bigArea - 2 * currentArea);
                firstPoint = i;
                secondPoint = j;
            }
            currentArea += triangleArea(a[i], a[j], a[(j + 1) % n]);
            j = (j + 1) % n;
        }
        if (abs(bigArea - 2 * currentArea) < diff) {
            diff = abs(bigArea - 2 * currentArea);
            firstPoint = i;
            secondPoint = j;
        }
        currentArea -= triangleArea(a[i], a[(i + 1) % n], a[j]);
    }
    cout << firstPoint + 1 << " " << secondPoint + 1 << endl;
}

int main() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    solve(n, a);
    // cout << calculateArea(a) << endl;

    return 0;
}