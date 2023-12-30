#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

const int MAX_N = 1e5 + 5;
const int MAX_K = 20;  // log2(MAX_N) rounded up

vector<int> a(MAX_N);
vector<vector<int>> sparseTable(MAX_N, vector<int>(MAX_K));

void buildSparseTable(int n) {
    // Khởi tạo sparse table cho mảng a
    for (int i = 0; i < n; i++) {
        sparseTable[i][0] = a[i];
    }

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 0; i + (1 << j) - 1 < n; i++) {
            sparseTable[i][j] = __gcd(sparseTable[i][j - 1], sparseTable[i + (1 << (j - 1))][j - 1]);
        }
    }
}

int query(int l, int r) {
    // Trả về ước chung lớn nhất trong đoạn từ l đến r
    int k = log2(r - l + 1);
    return __gcd(sparseTable[l][k], sparseTable[r - (1 << k) + 1][k]);
}

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    buildSparseTable(n);

    int result = 1;  // Giả sử ước chung lớn nhất ban đầu là 1

    for (int i = 0; i + k - 1 < n; i++) {
        // Tìm ước chung lớn nhất trong đoạn con có k phần tử
        result = max(result, query(i, i + k - 1));
    }

    cout << result << endl;

    return 0;
}
