#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void readData(string filein, string &destination, string &source)
{
    ifstream inp(filein.c_str());

    inp >> destination >> source;

    inp.close();
}

void normalize(string &source, string &destination, vector<int> &mask)
{
    // make index from 1
    // source only contains 'a' -> 'z' and '.'
    // mark[j] = 1 if source[j] can occur 0 or more times
    source = " " + source;
    destination = " " + destination;

    int n = source.length();
    string tmp = "";

    for (int i = 0; i < n; i++)
    {
        if (source[i] == '*')
        {
            mask[mask.size() - 1] = 1;
        }
        else
        {
            tmp += source[i];
            mask.push_back(0);
        }
    }

    source = tmp;
}

bool check(string source, string destination, vector<int> mask)
{
    // check if can change source to destination
    // source and destination are normalized

    int desLen = destination.length() - 1;
    int srcLen = source.length() - 1;

    // dp[i][j] = true if can change source[1..i] to destination[1..j]
    // i: index of source
    // j: index of destination
    vector<vector<bool>> dp(srcLen + 1, vector<bool>(desLen + 1, false));

    // base case
    dp[0][0] = true;
    for (int i = 1; i <= srcLen; i++)
    {
        if (mask[i])
        {
            dp[i][0] = dp[i - 1][0];
        }
    }

    // recursive case
    for (int i = 1; i <= srcLen; i++)
    { // source
        for (int j = 1; j <= desLen; j++)
        { // destination
            if (source[i] == '.')
            {
                // source[i]  = '.'
                dp[i][j] = dp[i - 1][j - 1];
            }
            else if (mask[i] == 0)
            {
                // source[i] in 'a' -> 'z'
                dp[i][j] = ((dp[i - 1][j - 1]) && (source[i] == destination[j]));
            }
            else if (mask[i] == 1)
            {
                // source[i] can occur 0 or more times
                dp[i][j] = dp[i - 1][j]; // do not use source[i]
                if (source[i] == destination[j])
                {
                    dp[i][j] = (dp[i][j]) || (dp[i][j - 1]); // use source[i]
                }
            }
        }
    }

    // cout << "destination: ." << destination << endl;
    // cout << "source: ." << source << endl;
    // for (int i = 0; i < mask.size(); i++)
    // {
    //     cout << mask[i] << " ";
    // }
    // cout << endl;
    // for (int i = 0; i <= srcLen; i++)
    // {
    //     for (int j = 0; j <= desLen; j++)
    //     {
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return dp[srcLen][desLen];
}

void printAns(string fileout, bool ans)
{
    ofstream out(fileout.c_str());

    if (ans)
    {
        out << "true";
    }
    else
    {
        out << "false";
    }

    out.close();
}

int main()
{
    string filein = "bai09.inp";
    string fileout = "bai09.out";

    // check if can change source to destination
    string destination;
    vector<int> mask;
    string source;

    readData(filein, destination, source);
    normalize(source, destination, mask);
    bool ans = check(source, destination, mask);
    printAns(fileout, ans);

    return 0;
}