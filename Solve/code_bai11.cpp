#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

#define INF 1e9

using namespace std;

void readData(string filein, int &num, int &numGroupA, int &numGroupB, vector<pair<int, int>> &cluster) {
    ifstream inp(filein);

    inp >> num >> numGroupA >> numGroupB;

    cluster.resize(num + 1);

    int x, y;
    for (int i = 1; i <= num; i++) {
        inp >> x >> y;
        cluster[i] = make_pair(x, y);
    }

    inp.close();
}

int divideClusters(int num, int numGroupA, int numGroupB, vector<pair<int, int>> cluster) {
    // f[i][j][k]: with i first clusters, j groups A, k groups B
    // 0 <= i <= num
    // 0 <= j <= numGroupA
    // 0 <= k <= numGroupB
    vector<vector<vector<int>>> f(num + 1, vector<vector<int>>(numGroupA + 1, vector<int>(numGroupB + 1, -INF)));

    f[0][0][0] = 0;

    for (int i = 1; i <= num; i++) {
        for (int j = 0; j <= numGroupA; j++) {
            for (int k = 0; k <= numGroupB; k++) {
                f[i][j][k] = f[i - 1][j][k]; // not choose cluster i
                if (j > 0) {
                    // choose cluster i to group A
                    f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][k] + cluster[i].first); 
                }
                if (k > 0) {
                    // choose cluster i to group B
                    f[i][j][k] = max(f[i][j][k], f[i - 1][j][k - 1] + cluster[i].second);
                }
            }
        }
    }

    return f[num][numGroupA][numGroupB];    
}

void printAns(string fileout, int ans) {
    ofstream out(fileout);

    out << ans;

    out.close();
}

int main() {
    string filein = "bai11.inp";
    string fileout = "bai11.out";

    int numGroupA, numGroupB;
    int num;
    vector<pair<int, int>> cluster;

    readData(filein, num, numGroupA, numGroupB, cluster);
    int ans = divideClusters(num, numGroupA, numGroupB, cluster);
    printAns(fileout, ans);

    return 0;
}

/*
GIẢI THÍCH CODE Ở ĐÂY NÈ

Tóm tắt đề:
K cụm dữ liệu, mỗi cụm có 2 giá trị (a, b) 
    tương ứng khi nó thuộc về nhóm A thì giá trị a tăng, thuộc nhóm B thì giá trị b tăng
2 nhóm A, B
nhóm A có tối đa N cụm dữ liệu
nhóm B có tối đa M cụm dữ liệu

Hướng giải quyết
F[i][j][k]: với i cụm dữ liệu đầu tiên, j nhóm A, k nhóm B
    + 0 <= i <= k
    + 0 <= j <= n
    + 0 <= k <= m

Cơ sở:
F[0][0][0] = 0

Công thức đệ quy:
F[i][j][k]:
    + không chọn cụm dữ liệu i
        F[i][j][k] = F[i-1][j][k]
    + chọn cụm dữ liệu i cho nhóm A
        F[i][j][k] = F[i-1][j-1][k] + cluster[i].a
    + chọn cụm dữ liệu i cho nhóm B
        F[i][j][k] = F[i-1][j][k-1] + cluster[i].b
=> F[i][j][k] = max(F[i-1][j][k], 
                    F[i-1][j-1][k] + cluster[i].a, 
                    F[i-1][j][k-1] + cluster[i].b)

Kết quả cần tìm: F[K][N][M]

Độ phức tạp:
    + Time complexity: O(KNM)
    + Space complexity: O(KNM)
*/