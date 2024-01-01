#include <iostream>
#include <cstdio>
using namespace std;

// 0 <= a[i] < = 60000
int f[60600];

int query(int x)
{
    // tính số phần tử lớn hơn x
    int ans = 0;

    for (int i=x+1; i<=60000; i+=i&-i) ans += f[i]; // i&-i: lấy bit 1 cuối cùng

    return ans;
}

void update(int x)
{
    // cập nhật số phần tử có giá trị x
     for (int i=x; i; i-=i&-i) f[i]++;
}

int main()
{
    // n: số lượng phần tử
    // x: giá trị của phần tử
    int n,x,ans=0;
    cin >> n;
    while (n--)
    {
        scanf("%d",&x);
        ans += query(x);
        update(x);
    }
    cout << ans << endl;
}