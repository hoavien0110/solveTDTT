#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#define MAX_HEIGHT 1e9
#define MAX_COST 1e18

using namespace std;

void readData(string filein, int &num, long long &times, vector<int> &height) {
    ifstream inp(filein.c_str());

    inp >> num >> times;

    height.resize(num + 1);
    for (int i = 1; i <= num; i++) {
        inp >> height[i];
    }    

    inp.close();
}

void calculatePrefixSum(int num, vector<int> &height, vector<long long> &prefixSum) {
    prefixSum.resize(num + 1);

    prefixSum[0] = 0;
    for (int i = 1; i <= num; i++) {
        prefixSum[i] = prefixSum[i - 1] + height[i];
    }
}

int findMin(int num, vector<int> &height) {
    int minHeight = height[1];
    
    for (int i = 2; i <= num; i++) {
        if (height[i] < minHeight) {
            minHeight = height[i];
        }
    }

    return minHeight;
}

long long newHeight(int targetId, int curId, long long targetMinHeight) {
    return targetMinHeight + abs(targetId - curId);
}

long long sumDelta(int l, int r) {
    // 0 + 1 + 2 + ... (r - l)
    return (long long) (r - l + 1) * (r - l) / 2;
}

bool checkHeight(int num, vector<int> &height, long long targetMinHeight, long long times, vector<long long> &prefixSum) {
    long long minCost = MAX_COST;
    int l = 1, r = 1; // the range need to be decreased

    for (int i = 1; i <= num; i++) {
        // let the height of the ith element be targetMinHeight
        r = (r < i) ? i : r;
        while (l < i && (long long) height[l] <= newHeight(i, l, targetMinHeight)) {
            l++;
        }
        while (r < num && (long long) height[r + 1] > newHeight(i, r + 1, targetMinHeight)) {
            r++;
        }
        long long curSumHeight = prefixSum[r] - prefixSum[l - 1];
        long long newSumHeight = (long long) (r - l + 1) * targetMinHeight + sumDelta(l,i) + sumDelta(i,r);
        long long cost = curSumHeight - newSumHeight;

        if (cost < minCost) {
            minCost = cost;
        }
    }

    return minCost <= times;
}

long long findLowestHeight(int num, vector<int> &height, long long times, vector<long long> &prefixSum) {
    long long minHeight = MAX_HEIGHT;

    long long r = (long long) findMin(num, height);
    long long l = r - times;

    while (l <= r) {
        long long mid = (l + r) / 2;

        if (checkHeight(num, height, mid, times, prefixSum)) {
            minHeight = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    
    return minHeight;
}

void printAns(string fileout, long long ans) {
    ofstream out(fileout.c_str());

    out << ans;

    out.close();
}

int main() {
    string filein = "bai19.inp";
    string fileout = "bai19.out";

    int num;
    long long times;
    vector<int> height;
    vector<long long> prefixSum;

    readData(filein, num, times, height);
    calculatePrefixSum(num, height, prefixSum);
    long long ans = findLowestHeight(num, height, times, prefixSum);
    printAns(fileout, ans);

    return 0;
}