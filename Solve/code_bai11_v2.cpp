#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

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
    // sort cluster decreasingly by first value
    sort(cluster.begin() + 1, cluster.end(), [](pair<int, int> a, pair<int, int> b) {
        return a.first > b.first;
    });

    // f[i][j]: with i first clusters, j groups B
    // 0 <= i <= num
    // 0 <= j <= numGroupB
    vector<vector<int>> f(num + 1, vector<int>(numGroupB + 1, -INF));

    f[0][0] = 0;

    for (int i = 1; i <= num; i++) {
        for (int j = 0; j <= numGroupB; j++) {
            // cluster are sorted decreasingly by first value (A)
            // so if do not choose cluster i for group B
            // it will be choosen for group A if possible (i - j <= numGroupA)
            if (i > j && i - j <= numGroupA) {
                // choose cluster i to group A
                f[i][j] = f[i - 1][j] + cluster[i].first;
            }
            else f[i][j] = f[i - 1][j]; // not choose cluster i

            if (j > 0) {
                // choose cluster i to group B
                f[i][j] = max(f[i][j], f[i - 1][j - 1] + cluster[i].second);
            }
        }
    }

    return f[num][numGroupB];
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

Nhận xét:
+ Sort các cụm dữ liệu theo giá trị a giảm dần
+ Mỗi cluster có thể có 3 trạng thái:
    + không chọn
    + chọn cho nhóm A
    + chọn cho nhóm B
+ Với cluster thứ i, nếu không chọn cho nhóm B
    và nhóm A vẫn còn slot
    -> nó chắc chắn sẽ nằm trong nhóm A 
    (vì đã sort giảm dần theo a)    

Hướng giải quyết
F[i][j]: với i cụm dữ liệu đầu tiên, j nhóm B
    + 0 <= i <= K
    + 0 <= j <= M

Cơ sở:
F[0][0] = 0

Công thức đệ quy:
F[i][j]:
    + chọn cụm dữ liệu i cho nhóm B
        F[i][j] = F[i-1][j] + cluster[i].b
    + không chọn cụm dữ liệu i cho nhóm B 
        + Nếu nhóm A còn slot (i - j <= N)
            F[i][j] = F[i-1][j] + cluster[i].a
        + Nếu nhóm A hết slot
            F[i][j] = F[i-1][j]

Kết quả cần tìm: F[K][M]

Độ phức tạp:
   + Không gian: O(n*m) // n: số lượng cụm dữ liệu, m: số lượng nhóm B
    + Thời gian: O(n*m)
*/