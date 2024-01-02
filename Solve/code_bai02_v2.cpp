/*
Gọi gn là số lượng các cặp p,q khác nhau sao cho p+q=2×n và p,q là nguyên tố. Hai cặp được gọi là khác nhau nếu 1 trong 2 số tham gia vào cặp này và không tham gia vào cặp còn lại. Cho số nguyên n. Hãy tính giá trị biểu thức: fn=g2+g3+…+gn.
Dữ liệu vào:
    Chứa số nguyên n 3≤n≤10^3.
Kết quả:
    Gồm một số nguyên duy nhất là giá trị fn
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Hàm sàng Eratosthenes để tìm số nguyên tố
void sieve(vector<bool> &isPrime, int m, vector<int> &primes)
{
    isPrime.resize(m + 1, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= m; ++i)
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= m; j += i)
            {
                isPrime[j] = false;
            }
        }
    }

    // Tìm các số nguyên tố nhỏ hơn hoặc bằng 2n
    for (int i = 2; i <= m; ++i)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
        }
    }
}

// Hàm tính giá trị fn
int calculateFn(int n)
{
    vector<bool> isPrime;
    vector<int> primes;
    int m = 2 * n;
    sieve(isPrime, 2 * n, primes);
    int len = primes.size();

    for (int i = 0; i < len; ++i)
    {
        cout << primes[i] << " ";
    }
    // Tính g
    int res = 1;
    // Chặt nhị phân tìm vị trí của số n trong mảng primes
    int pos = lower_bound(primes.begin(), primes.end(), n) - primes.begin();
    for (int p_i = 1; p_i <= pos; ++p_i)
    {
        int p = primes[p_i];
        // Chặt nhị phân tìm vị trí index của 2n - p trong mảng primes
        int q_high = 2 * n - p;
        cout << "p_i: " << p_i << endl;
        cout << "q_high: " << q_high << endl;

        // int q_high_index = upper_bound(primes.begin(), primes.end(), q_high) - primes.begin() - 1;
        // cout << "q_high_index: " << q_high_index << endl;

        // Tìm khoảng các phần tử có giá trị tương đương với q_high
        auto range = equal_range(primes.begin(), primes.end(), q_high);

        // Kiểm tra nếu giá trị tìm kiếm tồn tại trong danh sách primes
        int q_high_index;
        if (range.first != range.second)
        {
            q_high_index = range.first - primes.begin();
            cout << "q_high_index: " << q_high_index << endl;
        }
        else
        {
            q_high_index = range.second - primes.begin() - 1;
            cout << "q_high_index (largest element less than q_high): " << q_high_index << endl;
        }

        res += (q_high_index - p_i + 1);
        // cout << "q_high_index - p_i + 1: " << q_high_index - p_i + 1 << endl;
    }
    return res;
}

int main()
{
    int n;
    cin >> n;
    cout << calculateFn(n) << endl;
    return 0;
}
