#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void readData(string filein, int &num, vector<int> &height) {
    ifstream inp(filein.c_str());

    inp >> num;

    height.resize(num + 1);
    for (int i = 1; i <= num; i++) {
        inp >> height[i];
    }
    
    inp.close();
}

void findPrefixMax(int num, vector<int> &height, vector<int> &prefixMax) {
    prefixMax.resize(num + 1);

    prefixMax[0] = 0;
    for (int i = 1; i <= num; i++) {
        prefixMax[i] = max(prefixMax[i - 1], height[i]);
    }
}

void findSuffixMax(int num, vector<int> &height, vector<int> &suffixMax) {
    suffixMax.resize(num + 1);

    suffixMax[num] = height[num];
    for (int i = num - 1; i >= 1; i--) {
        suffixMax[i] = max(suffixMax[i + 1], height[i]);
    }
}

int calculateWaterLimit(int num, vector<int> &height, vector<int> &prefixMax, vector<int> &suffixMax) {
    int ans = 0;

    for (int i = 1; i <= num; i++) {
        ans += min(prefixMax[i], suffixMax[i]) - height[i];
    }

    return ans;
}

void printAns(string fileout, int ans) {
    ofstream out(fileout.c_str());

    out << ans;

    out.close();
}

int main() {
    string filein = "bai07.inp";
    string fileout = "bai07.out";

    int num;
    vector<int> height;
    vector<int> prefixMax;
    vector<int> suffixMax;

    readData(filein, num, height);
    findPrefixMax(num, height, prefixMax);
    findSuffixMax(num, height, suffixMax);
    int ans = calculateWaterLimit(num, height, prefixMax, suffixMax);
    printAns(fileout, ans);

    return 0;
}