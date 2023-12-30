#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    int x, y, index;
};

// Hàm tính khoảng cách Euclid giữa hai điểm
double distance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// Hàm so sánh cosine của góc giữa ba điểm
bool compare(const pair<double, int>& a, const pair<double, int>& b) {
    return a.first < b.first;
}

// Hàm tính cosine của góc giữa ba điểm
double calculateCosTriangle(const Point& A, const Point& B, const Point& C) {
    double a = distance(B, C);
    double b = distance(A, C);
    double c = distance(A, B);

    return (pow(b, 2) + pow(c, 2) - pow(a, 2)) / (2 * b * c);
}

int main() {
    int n;
    cin >> n;

    vector<Point> points(n);

    // Nhập thông tin về các điểm
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
        points[i].index = i + 1;
    }

    // Tìm điểm có tung độ thấp nhất
    Point A = *min_element(points.begin(), points.end(), [](const Point& p1, const Point& p2) {
        return p1.y < p2.y;
    });

    // Tạo điểm B có cùng tung độ với A
    Point B = {A.x + 1, A.y, 0};

    // Tính cosine giữa các điểm và sắp xếp chúng theo thứ tự tăng dần
    vector<pair<double, int>> angles;
    for (int i = 0; i < n; ++i) {
        if (points[i].index != A.index) {
            double angle = calculateCosTriangle(A, B, points[i]);
            angles.push_back({angle, points[i].index});
        }
    }

    sort(angles.begin(), angles.end(), compare);

    // Lấy vị trí i để chia tập điểm thành hai phần bằng nhau
    int i = n / 2 - 1;

    // Hiển thị kết quả
    cout << A.index << " " << angles[i].second << endl;

    return 0;
}
