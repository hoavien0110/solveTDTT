/*
Find all possible ways to place n queens on an n×n chessboard such that no two queens can attack each other. 
- The input consists of the size of the chessboard (n) and the number of queens. 
- The output should include the total number of distinct ways and the representations 
of the chessboards for each solution.

Input:

An integer n (1 ≤ n ≤ 9) representing the size of the chessboard.
An integer representing the number of queens.
Output:

The first line contains an integer m, which is the total number of distinct ways to place the queens.
The following lines contain the representations of the chessboards for each solution, separated by a blank line.
Each chessboard is represented by n lines, where each line contains n characters.
'.' represents an empty square.
'Q' represents a square with a queen.
*/

#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<vector<int>> board;
vector<vector<bool>> visited;
vector<vector<int>> solutions;

bool isValid(int row, int col) {
    // Check row
    for (int j = 0; j < n; j++) {
        if (board[row][j] == 1) {
            return false;
        }
    }

    // Check column
    for (int i = 0; i < n; i++) {
        if (board[i][col] == 1) {
            return false;
        }
    }

    // Check diagonal
    int i = row, j = col;
    while (i >= 0 && j >= 0) {
        if (board[i][j] == 1) {
            return false;
        }
        i--;
        j--;
    }

    i = row, j = col;
    while (i < n && j < n) {
        if (board[i][j] == 1) {
            return false;
        }
        i++;
        j++;
    }

    i = row, j = col;
    while (i >= 0 && j < n) {
        if (board[i][j] == 1) {
            return false;
        }
        i--;
        j++;
    }

    i = row, j = col;
    while (i < n && j >= 0) {
        if (board[i][j] == 1) {
            return false;
        }
        i++;
        j--;
    }

    return true;
}

void solve(int row, int col, int count) {
    if (count == m) {
        vector<int> solution;
        for (int i = 0; i < n; i++) {
            int j = 0;
            while (j < n && board[i][j] != 1) {
                j++;
            }
            solution.push_back(j);
        }
        solutions.push_back(solution);
        return;
    }

    for (int i = row; i < n; i++) {
        for (int j = col; j < n; j++) {
            if (!visited[i][j] && isValid(i, j)) {
                visited[i][j] = true;
                board[i][j] = 1;
                solve(i, j, count + 1);
                board[i][j] = 0;
                visited[i][j] = false;
            }
        }
        col = 0;
    }
}

int main() {
    cin >> n >> m;

    board.resize(n);
    visited.resize(n);
    for (int i = 0; i < n; i++) {
        board[i].resize(n);
        visited[i].resize(n);
    }

    solve(0, 0, 0);

    cout << solutions.size() << endl;
    for (int i = 0; i < solutions.size(); i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < solutions[i][j]; k++) {
                cout << ". ";
            }
            cout << "Q ";
            for (int k = solutions[i][j] + 1; k < n; k++) {
                cout << ". ";
            }
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}