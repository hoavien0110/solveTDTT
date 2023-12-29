#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

void readData(string filename, int &numCol, int &numRow, vector<vector<int>> &matrix) {
    ifstream inp(filename);

    inp >> numCol >> numRow;

    matrix.resize(numRow + 1);
    for (int i = 0; i <= numRow; i++) {
        matrix[i].resize(numCol + 1, 0);

        if (i > 0) {
            for (int j = 0; j < numCol; j++) {
                inp >> matrix[i][j + 1];
            }
        }
    }

    inp.close();
}

int findMaxSquare(int numCol, int numRow, vector<vector<int>> &matrix, int target) {
    int ans = 0;
    vector<vector<int>> dp(numRow + 1, vector<int>(numCol + 1, 0));

    for (int i = 1; i <= numRow; i++) {
        for (int j = 1; j <= numCol; j++) {
            if (matrix[i][j] != target) {
                continue;
            }

            dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1]))
                            + 1;
            ans = max(ans, dp[i][j]);
        }
    }

    return ans;
}

void printAns(string filename, int ans) {
    ofstream out(filename);

    out << ans;

    out.close();
}

int main() {
    int numCol, numRow;
    vector<vector<int>> matrix;

    string filein = "bai10.inp";
    string fileout = "bai10.out";

    readData(filein, numCol, numRow, matrix);
    int zero = findMaxSquare(numCol, numRow, matrix, 0);
    int one = findMaxSquare(numCol, numRow, matrix, 1);
    int ans = max(zero, one);
    printAns(fileout, ans);

    return 0;
}