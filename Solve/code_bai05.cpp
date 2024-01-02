#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define BASE 256
#define MOD (int)(1e9 + 7)

using namespace std;

void readData(string filein, string &para, string &word) {
    ifstream inp(filein.c_str());

    getline(inp, para);
    getline(inp, word);

    inp.close();
}

void solve(string para, string word, vector<int> &ans) {
    // find positions of word in para

    // calculate POW
    vector<long long> POW(para.size());
    POW[0] = 1;
    for (int i = 1; i < para.size(); i++)
        POW[i] = POW[i-1] * BASE % MOD;

    // hash of word
    long long hashWord = 0;
    for (int i = 0; i < word.size(); i++)
    {
        hashWord = ((hashWord * BASE)  % MOD + word[i]) % MOD;
    }
    

    // hash of para
    vector<long long> hashPara(para.size());
    hashPara[0] = para[0];
    for (int i = 1; i < para.size(); i++)
    {   
        hashPara[i] = ((hashPara[i-1] * BASE) % MOD + para[i]) % MOD;
    }

    // find positions
    for (int i = 0; i <= para.size() - word.size(); i++) {
        long long hashSub = hashPara[i + word.size() - 1];
        if (i > 0)
            hashSub = (hashSub - ((hashPara[i-1] * POW[word.size()]) % MOD) + MOD) % MOD;

        if (hashSub == hashWord) {
            bool ok = true;
            for (int j = 0; j < word.size(); j++)
                if (para[i+j] != word[j]) {
                    ok = false;
                    break;
                }
            
            if (ok) {
                // ans with id from 1
                ans.push_back(i + 1);
            }
        }
    }

}

void printAns(string fileout, vector<int> &ans) {
    ofstream out(fileout.c_str());

    for (int i = 0; i < ans.size(); i++)
        out << ans[i] << " ";

    out.close();
}

int main() {
    string filein = "bai05.inp";
    string fileout = "bai05.out";

    string para, word;

    readData(filein, para, word);
    vector<int> ans;
    solve(para, word, ans);
    printAns(fileout, ans);

    return 0;
}

/*
Ý TƯỞNG HASH:

chỉ số:         0 1 2 3 4 
đoạn văn:       b a a a a
từ cần tìm:     a a

giả sử xâu chỉ gồm các kí tự thường 'a' -> 'z'

so sánh xâu: phải so sánh từng kí tự -> O(n)
so sánh số: chỉ cần so sánh 1 lần -> O(1)

ý tưởng: chuyển xâu thành 1 số -> 
dù có duyệt hết từ vị trí trong xâu thì chi phí vẫm là O(n)

làm sao để chuyển 1 xâu thành 1 số?
'a' -> 1
'b' -> 2
'c' -> 3
...
'z' -> 26

2363 = 2*10^3 + 3*10^2 + 6*10^1 + 3*10^0
BASE = 10 - số chữ số khác nhau (0-9)

'a' -> 'z' -> 26 kí tự khác nhau
-> chuyển xâu thành 1 số có base = 26

vấn đề khi chuyển xâu thành số: giá trị của số có thể quá lớn
-> dùng MOD = 10^9 + 7 (hoặc 1 số nguyên tố lớn)

đoạn văn: baaa -> 2*26^3 + 1*26^2 + 1*26^1 + 1*26^0 // mod 10^9 + 7
từ cần tìm: aa -> 1*26^1 + 1*26^0 // mod 10^9 + 7

làm sao để lấy hash của 1 đoạn con trong đoạn văn dựa vào Hash của đoạn văn?
[i..j] -> hash[i..j] = hash[j] - hash[i-1]*26^(j-i+1)
sau khi thêm MOD:
[i..j] -> hash[i..j] = (hash[j] - hash[i-1]*26^(j-i+1) + MOD) % MOD

Đảm bảo chính xác, cần kiểm tra lại xâu có thực sự khớp tại vị trí tìm được hay không bằng so sánh xâu

Độ phức tạp: 
    + thời gian: O(n)
    + không gian: O(n)
*/


