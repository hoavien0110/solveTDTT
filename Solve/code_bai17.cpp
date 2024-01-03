#include <iostream>
#include <queue>
#define MAX 1000000000
using namespace std;

int findSmallestMultiple(int n) {
    queue<int> q;
    q.push(1);
    int cnt = 0;
    while (!q.empty()) {
        int currentNumber = q.front();
        q.pop();
        cnt++;
        if (currentNumber < MAX && currentNumber % n == 0) {
            return currentNumber;
        }

        if (currentNumber < MAX) {
            q.push(currentNumber * 10);
            q.push(currentNumber * 10 + 1);
        }
    }
    return -1;
}

int main() {
    int n;
    cin >> n;

    int smallestMultiple = findSmallestMultiple(n);
    cout << smallestMultiple << endl;

    return 0;
}