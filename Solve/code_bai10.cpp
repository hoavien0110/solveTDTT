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

void calculateSum(int numCol, int numRow, vector<vector<int>> &matrix, vector<vector<int>> &sum) {
    sum.resize(numRow + 1);
    for (int i = 0; i <= numRow; i++) {
        sum[i].resize(numCol + 1, 0);
    }

    for (int i = 1; i <= numRow; i++) {
        for (int j = 1; j <= numCol; j++) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1]
                        + matrix[i][j];
        }
    }
}

int findMaxSquare(int numCol, int numRow, vector<vector<int>> &sum) {
    int ans = 0;

    for (int i = 1; i <= numRow; i++) {
        for (int j = 1; j <= numCol; j++) {
            for (int k = min(numRow - i + 1, numCol - j + 1); k > 0; k--) {
                int sumSquare = sum[i + k - 1][j + k - 1] - sum[i - 1][j + k - 1]
                                - sum[i + k - 1][j - 1] + sum[i - 1][j - 1];

                if (sumSquare == k * k || sumSquare == 0) {
                    ans = max(ans, sumSquare);
                    break;
                }
            }
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
    vector<vector<int>> sum;

    string filein = "bai10.inp";
    string fileout = "bai10.out";

    readData(filein, numCol, numRow, matrix);
    calculateSum(numCol, numRow, matrix, sum);
    int ans = findMaxSquare(numCol, numRow, sum);
    printAns(fileout, ans);

    return 0;
}