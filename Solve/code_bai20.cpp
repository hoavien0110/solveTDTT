#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void readDate(string filename, int &n, vector<int> &permutation, unsigned long long &index) {
    ifstream inp(filename);

    inp >> n;

    permutation.resize(n);
    for (int i = 0; i < n; i++) {
        inp >> permutation[i];
    }

    inp >> index;

    inp.close();
}

void calculateFactorial(int n, vector<unsigned long long> &factorials) {
    factorials.resize(n + 1);
    factorials[0] = 1;

    for (int i = 1; i <= n; i++) {
        factorials[i] = factorials[i - 1] * i;
    }
}

int binarySearch(vector<int> &numbers, int x) {
    int left = 0;
    int right = numbers.size() - 1;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (numbers[mid] == x) {
            return mid;
        }

        if (numbers[mid] < x) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}

int findIndex(int n, vector<int> &permutation, vector<unsigned long long> &factorials) {
    int index = 0;

    vector<int> numbers;
    for (int i = 1; i <= n; i++) {
        numbers.push_back(i);
    }

    for (int i = 0; i < n; i++) {
        int pos = binarySearch(numbers, permutation[i]);
        index += pos * factorials[n - i - 1];
        numbers.erase(numbers.begin() + pos);
    }

    // the first permutation id is 1
    return index + 1;
}

void findPermutation(int n, unsigned long long index, vector<int> &permutation, vector<unsigned long long> &factorials) {
    permutation.resize(n);

    vector<int> numbers;
    for (int i = 1; i <= n; i++) {
        numbers.push_back(i);
    }

    // the first permutation id is 1
    index--;

    for (int i = 0; i < n; i++) {
        int pos = index / factorials[n - i - 1];
        permutation[i] = numbers[pos];
        numbers.erase(numbers.begin() + pos);
        index %= factorials[n - i - 1];
    }
}

void printAns(string filename, int index, vector<int> permutation) {
    ofstream out(filename);

    out << index << endl;

    for (int i = 0; i < permutation.size(); i++) {
        out << permutation[i] << " ";
    }

    out.close();
}

int main() {
    string filein = "bai20.inp";
    string fileout = "bai20.out";

    int n;
    vector<int> permutation;
    unsigned long long index;

    vector<unsigned long long> factorials;

    unsigned long long solveIndex;
    vector<int> solvePermutation;

    readDate(filein, n, permutation, index);
    calculateFactorial(n, factorials);

    solveIndex = findIndex(n, permutation, factorials);
    findPermutation(n, index, solvePermutation, factorials);

    printAns(fileout, solveIndex, solvePermutation);

    return 0;
}