/*
each point is pair<double, double>
calculate the area of a triangle
*/
#include <iostream>
#include <vector>
using namespace std;

double calculateTriangleArea(pair<double, double> a, pair<double, double> b, pair<double, double> c) {
    double area = 0;
    area += (b.first - a.first) * (b.second + a.second);
    area += (c.first - b.first) * (c.second + b.second);
    area += (a.first - c.first) * (a.second + c.second);
    area /= 2;
    return area;
}

int main() {
    int n;
    cin >> n;
    vector<pair<double, double>> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].first >> points[i].second;
    }

    cout << calculateTriangleArea(points[0], points[2], points[1]);
    return 0;
}