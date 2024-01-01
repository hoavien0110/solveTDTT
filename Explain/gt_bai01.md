## Giải thích code bài 1

### 1. Đề
Cho dãy số nguyên a1,a2,…,an. Tìm một đoạn con có đúng k phần tử liên tiếp sao cho ước chung lớn nhất của các phần tử này là lớn nhất.
- Dữ liệu vào: 
    - Dòng đầu: n,k2≤kn103
    - Dòng tiếp theo: a1,a2,…,an1≤ai106.
- Kết quả: 
    - Giá trị lớn nhất của ước chung lớn nhất của k phần tử liên tiếp.

### 2. Giải thích
Vì $gcd(x_i, x_j) = gcd(gcd(x_i, x_k), gcd(x_k, x_j))$ nên ta có thể sử dụng segment tree hoặc sparse table

### 3. Độ phức tạp
- Sparse table:
    - Thời gian: $O(nlogn)$
    - Không gian: $O(nlogn)$
- Segment tree:
    - Thời gian: $O(n)$
    - Không gian: $O(4n)$