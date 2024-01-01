/*
Gọi gn là số lượng các cặp p,q khác nhau sao cho p+q=2×n và p,q là nguyên tố. Hai cặp được gọi là khác nhau nếu 1 trong 2 số tham gia vào cặp này và không tham gia vào cặp còn lại. Cho số nguyên n. Hãy tính giá trị biểu thức: fn=g2+g3+…+gn.
Dữ liệu vào: 
    Chứa số nguyên n 3≤n≤10^3.
Kết quả: 
    Gồm một số nguyên duy nhất là giá trị fn
*/

#include <iostream>
#include <vector>

using namespace std;

// Hàm sàng Eratosthenes để tìm số nguyên tố
void sieve(vector<bool>& isPrime, int m) {
    isPrime.resize(m + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= m; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= m; j += i) {
                isPrime[j] = false;
            }
        }
    }
}

// Hàm tính giá trị fn
int calculateFn(int n) {
    vector<bool> isPrime;
    int m = 2 * n;
    sieve(isPrime, 2 * n);
    vector<int> primes;

    // Tìm các số nguyên tố nhỏ hơn hoặc bằng 2n
    for (int i = 2; i <= m; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    int len = primes.size();

    // Tính g
    vector<int> g(n + 1, 0);
    for (int p = 0; p < len; ++p) {
        for (int q = p; q < len; ++q) {
            int sum = primes[p] + primes[q];
            if (sum <= m && !(sum % 2)) {
                g[sum / 2]++;
            }
        }
    }

    int f = 0;
    // Tính f
    for (int i = 2; i <= n; ++i) {
        f += g[i];
    }

    return f;
}

int main() {
    int n;
    cin >> n;
    cout << calculateFn(n) << endl;
    return 0;
}
