## Giải thích code bài 12

### 1. Đề
Hãy chỉ ra cách xây dựng một hình vuông có diện tích là số nguyên dương S cho trước với các tọa độ nguyên trong phạm vi từ -10^9 đến 10^9.
- Input: Số nguyên dương S≤103.
- Output: Tọa độ 4 đỉnh của hình vuông được liệt kê cùng hoặc ngược chiều kim đồng hồ. Trường hợp không có lời giải thì thông báo Impossible.

### 2. Giải thích
- Thực tế ta chỉ cần tìm a, b sao cho a^2 + b^2 = S
- Khi đó, ta sẽ có 4 điểm thỏa đề bài:
    - A (a, 0)
    - B (0, b)
    - C (b, a + b)
    - D (a + b, a)

- Xây dựng mảng số chính phương và thực hiện tìm kiếm x, y sao cho x + y = S -> a = sqrt(x), b = sqrt(y)
- Vì S <= 10^3 nên chỉ vector chỉ cần length 32 là đủ

### 3. Độ phức tạp
- Thời gian:
    - Tìm kiếm: đặt n = 32 -> $O(n \log{n})$
- Không gian:
    - Xây dựng vector -> $O(n)$