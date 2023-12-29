#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void readData(string filein, int &num, vector<int> &arr) {
    ifstream inp(filein.c_str());

    inp >> num;
    arr.resize(num + 1);
    for (int i = 1; i <= num; i++) {
        inp >> arr[i];
    }
    
    inp.close();
}

int main() {
    string filein = "bai04.inp";
    string fileout = "bai04.out";

    int num;
    vector<int> arr;

    readData(filein, num, arr);
    return 0;
}