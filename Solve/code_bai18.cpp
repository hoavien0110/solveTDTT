#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>
#include <map>

using namespace std;

struct Status {
    string permutation;
    int step;
};

struct cmp {
    bool operator()(const Status &a, const Status &b) {
        return a.step > b.step;
    }
};

void readData(string filein, int &n, string &permutation) {
    ifstream inp(filein.c_str());

    inp >> n;

    // read n 1-digit-numbers and convert to string
    int x;
    for (int i = 0; i < n; i++) {
        inp >> x;
        permutation += (x + '0');
    }
    
    inp.close();
}

bool isTarget(string permutation) {
    for (int i = 0; i < permutation.length() - 1; i++) {
        if (permutation[i] > permutation[i + 1]) {
            return false;
        }
    }

    return true;
}

string newPermutation(string permutation, int i) {
    string newPermutation = "";

    for (int j = i; j >= 0; j--) {
        newPermutation += permutation[j];
    }

    for (int j = i + 1; j < permutation.length(); j++) {
        newPermutation += permutation[j];
    }

    return newPermutation;
}

int bfs(int n, string permutation) {
    priority_queue<Status, vector<Status>, cmp> q;
    map<string, bool> checked;

    q.push({permutation, 0});
    checked[permutation] = true;

    while (!q.empty()) {
        Status u = q.top();
        q.pop();

        if (isTarget(u.permutation)) {
            return u.step;
        }

        for (int i = 1; i < n; i++) {
            string v = newPermutation(u.permutation, i);

            if (!checked[v]) {
                q.push({v, u.step + 1});
                checked[v] = true;
            }
        }
    }

    return -1;
}

void printAns(string fileout, int ans) {
    ofstream out(fileout.c_str());

    out << ans;
    
    out.close();
}

int main() {
    string filein = "bai18.inp";
    string fileout = "bai18.out";

    int n;
    string permutation;

    readData(filein, n, permutation);
    int ans = bfs(n, permutation);
    printAns(fileout, ans);

    return 0;
}