#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

void solve(int n)
{
    int cnt = 0;
    vector<int> trace(n, -1);
    vector<int> remainder(n, 0);

    if (n == 1)
    {
        cout << 1 << endl;
        return;
    }

    queue<int> q;
    q.push(1);
    remainder[1] = 1;
    trace[1] = 0;

    while (!q.empty())
    {
        cnt++;
        int u = q.front();
        q.pop();

        int v1, v2;
        v1 = (u * 10) % n;
        v2 = (v1 + 1) % n;

        if (trace[v1] == -1)
        {
            trace[v1] = u;
            remainder[v1] = 0;
            q.push(v1);
        }

        if (trace[v2] == -1)
        {
            trace[v2] = u;
            remainder[v2] = 1;
            q.push(v2);
        }

        if (trace[0] != -1)
        {
            break;
        }
    }
    if (trace[0] == -1)
    {
        cout << -1 << endl;
        return;
    }
    string res = "";
    int path_index = 0;

    while (path_index != 1 )
    {
        res += to_string(remainder[path_index]);
        path_index = trace[path_index];
    }

    res += "1";
    reverse(res.begin(), res.end());
    if (res.length() > 9)
    {
        cout << -1 << endl;
        // cout << cnt << endl;

        return;
    }
    cout << res << endl;
    // cout << cnt << endl;
}

int main()
{
    int n;
    cin >> n;
    solve(n);
    return 0;
}