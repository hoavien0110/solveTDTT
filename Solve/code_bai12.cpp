#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<long long> generatePerfectSquares() {
    vector<long long> squares;
    for (long long i = 1; i <= 31; ++i) {
        squares.push_back(i * i);
    }
    return squares;
}

pair<long long, long long> findCoordinates(long long S, const vector<long long>& squares) {
    for (long long x : squares) {
        long long y = S - x;
        if (binary_search(squares.begin(), squares.end(), y)) {
            return {sqrt(x), sqrt(y)};
        }
    }
    return {-1, -1};
}

int main() {
    long long S;
    cin >> S;

    vector<long long> squares = generatePerfectSquares();
    pair<long long, long long> coordinates = findCoordinates(S, squares);

    if (coordinates.first != -1) {
        cout << coordinates.first << " 0\n";
        cout << "0 " << coordinates.second << "\n";
        cout << coordinates.second << " " << (coordinates.second + coordinates.first) << "\n";
        cout << (coordinates.second + coordinates.first) << " " << coordinates.first << "\n";

    } else {
        cout << "Impossible\n";
    }

    return 0;
}
