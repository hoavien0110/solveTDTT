#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

int binarySearch(const vector<pair<int, int>>& arr, int target) {
    int low = 0, high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid].first == target) {
            return mid;
        } else if (arr[mid].first < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;
}

int main() {
    int m, n;
    cin >> m >> n;

    vector<pair<int, int>> a(m), b(n);

    for (int i = 0; i < m; i++) {
        cin >> a[i].first;
        a[i].second = i + 1; // Chỉ số bắt đầu từ 1
    }

    for (int j = 0; j < n; j++) {
        cin >> b[j].first;
        b[j].second = j + 1; // Chỉ số bắt đầu từ 1
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int i = 0, j = 0;
    int minSum = abs(a[0].first + b[0].first);

    for (int k = 0; k < m; k++) {
        int l = binarySearch(b, -a[k].first);
        // số lớn nhất nhỏ hơn hoặc bằng -a[k].first

        if (l < n) {
            // xét số vừa tìm được
            int currentSum = abs(a[k].first + b[l].first);
            if (currentSum < minSum) {
                i = a[k].second;
                j = b[l].second;
                minSum = currentSum;
            }
        }

        if (l > 0) {
            // xét số nhỏ hơn số vừa tìm được
            int currentSum = abs(a[k].first + b[l - 1].first);
            if (currentSum < minSum) {
                i = a[k].second;
                j = b[l - 1].second;
                minSum = currentSum;
            }
        }
    }

    cout << i << " " << j << endl;
    return 0;
}
