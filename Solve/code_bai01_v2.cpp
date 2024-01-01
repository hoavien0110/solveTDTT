// C++ code for segment tree with sum
// range and update query

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
vector<int> A, ST;

void build(int node, int L, int R)
{

	// Leaf node where L == R
	if (L == R) {
		ST[node] = A[L];
	}
	else {

		// Find the middle element to
		// split the array into two halves
		int mid = (L + R) / 2;

		// Recursively travel the
		// left half
		build(2 * node, L, mid);

		// Recursively travel the
		// right half
		build(2 * node + 1, mid + 1, R);

		// Storing the sum of both the
		// children into the parent
		ST[node] = __gcd(ST[2 * node], ST[2 * node + 1]);
	}
}

int query(int node, int tl, int tr, int l, int r)
{

	// If it lies out of range then
	// return 0
	if (r < tl or tr < l)
		return 0;

	// If the node contains the range then
	// return the node value
	if (l <= tl and tr <= r)
		return ST[node];
	int tm = (tl + tr) / 2;

	// Recursively traverse left and right
	// and find the node
	return __gcd(query(2 * node, tl, tm, l, r), query(2 * node + 1, tm + 1, tr, l, r));
}

// Driver code
int main()
{
    int n, k;
    cin >> n >> k;

	// Create a segment tree of size 4*n
    A.resize(n);
	ST.resize(4 * n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
	// int n = 6;
	// A = { 0, 1, 3, 5, -2, 3 };

	// Build a segment tree
	build(1, 0, n - 1);

    // Tìm ước chung lớn nhất trong đoạn con có k phần tử

    int result = 1;  // Giả sử ước chung lớn nhất ban đầu là 1
    for (int i = 0; i + k - 1 < n; i++) {
        // Tìm ước chung lớn nhất trong đoạn con có k phần tử
        result = max(result, query(1, 0, n - 1, i, i + k - 1));
    }
    cout << result << endl;
	return 0;
}
