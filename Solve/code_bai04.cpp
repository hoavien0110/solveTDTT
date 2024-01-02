#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>
#include <algorithm>

#define MAX 1000000

using namespace std;

void readData(string filein, int &num, vector<int> &a)
{
    ifstream inp(filein.c_str());
     
    inp >> num;

    a.resize(num);
    for (int i = 0; i < num; i++)
        inp >> a[i];

    inp.close();
}

void normalize(int &num, vector<int> &a)
{
    // make a[i] in [1..num]
    vector<pair<int, int> > b(num);

    for (int i = 0; i < num; i++)
        b[i] = make_pair(a[i], i);

    sort(b.begin(), b.end());

    int cnt = 1;

    a[b[0].second] = cnt;

    for (int i = 1; i < num; i++)
    {
        if (b[i].first != b[i - 1].first)
            cnt++;

        a[b[i].second] = cnt;
    }

    // for (int i = 0; i < num; i++)
    //    cout << a[i] << " ";
    // cout << endl;
}

void build(vector<int> &ST, int num)
{
    // at first, ST has 0 elements
    // so every node of ST has value 0
    ST.resize(4 * num + 1, 0);
}

int query(vector<int> &ST, int id, int l, int r, int u, int v)
{
    // count number of elements in [u..v]
    // ST[id] is the number of elements in [l..r]

    // node id is out of range
    // [u..v] is out of [l..r]
    if (v < l || r < u)
        return 0;

    // [u..v] is in node id
    if (u <= l && r <= v)
        return ST[id];

    // [u..v] is in [l..r]
    int mid = (l + r) / 2;
    int left = query(ST, id * 2, l, mid, u, v);
    int right = query(ST, id * 2 + 1, mid + 1, r, u, v);
    
    return left + right;
}

void update(vector<int> &ST, int id, int l, int r, int val)
{
    // add val to ST
    // ST[id] is the number of elements in [l..r]

    // node id does not contain val
    if (val < l || r < val)
        return; 

    // node id contains val
    ST[id]++;

    // node id is a leaf
    if (l == r)
        return;

    // update left and right child
    int mid = (l + r) / 2;
    update(ST, id * 2, l, mid, val);
    update(ST, id * 2 + 1, mid + 1, r, val);
}

long long solve(vector<int> &ST, int num, vector<int> &a)
{
    long long ans = 0;

    for (int i = 0; i < num; i++)
    {
        // count number of elements > a[i]
        ans += (long long)query(ST, 1, 1, num, a[i] + 1, num);

        // add a[i] to ST
        update(ST, 1, 1, num, a[i]);
    }

    return ans;
}

void printAns(string fileout, long long ans)
{
    ofstream out(fileout.c_str());

    out << ans;

    out.close();
}

int main()
{
    string filein = "bai04.inp";
    string fileout = "bai04.out";

    vector<int> ST;
    int num;
    vector<int> a;

    readData(filein, num, a);
    normalize(num, a);
    build(ST, num);
    long long ans = solve(ST, num, a);
    printAns(fileout, ans);
    
    return 0;
}

/*
GIẢI THÍCH CODE Ở ĐÂY NÈ

Tập đã xét = rỗng

Xét các phần tử của mảng từ trái sang phải:
+ Đếm số phần tử lớn hơn phần tử đang xét trong tập đã xét
    (đảm bảo tính chất của đề bài).
+ Thêm phần tử đang xét vào tập đã xét.

Các thao tác trên có thể thực hiện bằng Segment Tree:
+ Tại mỗi thứ id quản lý đoạn [l,r] là số lượng phần tử trong đoạn đó.
+ Để đếm số phần tử lớn hơn phần tử đang xét:
    Ta cần đếm số phần tử trong đoạn [a[i]+1, n].
    -> Query với u = a[i] + 1, v = n.
+ Để thêm phần tử đang xét vào tập đã xét:
    Ta cần tăng số lượng phần tử trong đoạn [a[i], a[i]] lên 1.
    -> Update với val = a[i].

Độ phức tạp: O(nlogn), với n = MAX - MIN + 1.

Vấn đề:
+ ST lưu số lượng phần tử trong đoạn [l,r], tức là [MIN,MAX] trong mảng
    Tuy nhiên, giá trị các phần tử trong mảng rất lớn
    -> Cần chuẩn hóa lại mảng về [1,n].
+ Chuẩn hóa:
    Sắp xếp lại mảng theo thứ tự tăng dần.
    Gán a[i] dựa vào vị trí của a[i] trong mảng đã sắp xếp.
Ví dụ:
Ban đầu: -1000000000 2 4 3 1000000000 -1000000000
Gắn phần tử với id: (-1000000000,0) (2,1) (4,2) (3,3) (1000000000,4) (-1000000000,5)
Sắp xếp: (-1000000000,0) (-1000000000,5) (2,1) (3,3) (4,2) (1000000000,4)
Chuẩn hóa:
+ cnt = 1; a[0] = 1
+ cnt = 1; a[5] = 1
+ cnt = 2; a[1] = 2
+ cnt = 3; a[3] = 3
+ cnt = 4; a[2] = 4
+ cnt = 5; a[4] = 5
Kết quả: 1 2 4 3 5 1

Độ phức tạp: O(nlogn), với n là số lượng phần tử trong mảng.

Tóm lại:
+ Chuẩn hóa mảng về [1,n].
+ Xây dựng Segment Tree.
+ Tính kết quả.

Độ phức tạp, với n là số lượng phần tử trong mảng.
+ Không gian: O(n)
+ Thời gian: O(nlogn)
*/