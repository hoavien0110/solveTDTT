#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>

using namespace std;

void readData(string filein, int &num, vector<int> &arr)
{
    ifstream inp(filein.c_str());

    inp >> num;

    arr.resize(num);
    for (int i = 0; i < num; i++)
        inp >> arr[i];

    inp.close();
}

// create a class contain: step and arr
struct Node
{
    int step;
    vector<int> arr;

    Node(int step, vector<int> arr)
    {
        this->step = step;
        this->arr = arr;
    }
};

struct cmp
{
    bool operator()(Node a, Node b)
    {
        return a.step > b.step;
    }
};

bool isTarget(vector<int> arr)
{
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] != i + 1)
            return false;
    return true;
}

int bfs(int num, vector<int> arr)
{
    priority_queue<Node, vector<Node>, cmp> status;

    status.push(Node(0, arr));

    while (!status.empty())
    {
        Node node = status.top();
        status.pop();

        if (isTarget(node.arr))
            return node.step;

        for (int i = 1; i < node.arr.size(); i++)
        {
            vector<int> temp = node.arr;
            // reverse from first to i
            reverse(temp.begin(), temp.begin() + i + 1);
            status.push(Node(node.step + 1, temp));
        }
    }
    return -1;
}

void printAns(string fileout, int ans)
{
    ofstream out(fileout.c_str());

    out << ans;

    out.close();
}

int main()
{
    string filein = "bai18.inp";
    string fileout = "bai18.out";

    int num;
    vector<int> arr;

    readData(filein, num, arr);
    int ans = bfs(num, arr);
    printAns(fileout, ans);
    return 0;
}