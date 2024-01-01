## Giải thích code bài 2

### 1. Đề
Gọi g(n) là số lượng các cặp p,q khác nhau sao cho p+q=2×n và p,q là nguyên tố. Hai cặp được gọi là khác nhau nếu 1 trong 2 số tham gia vào cặp này và không tham gia vào cặp còn lại. Cho số nguyên n. Hãy tính giá trị biểu thức: f(n)=g(2)+g(3)+…+g(n).
- Dữ liệu vào: 
    - Chứa số nguyên n 3≤n≤10^3.
- Kết quả: 
    - Gồm một số nguyên duy nhất là giá trị fn.

## 2. Giải thích
- Duyệt trâu :")
- Đặt m = 2 * n. Sàng nguyên tố từ 2 -> m
- Tạo mảng g[2 -> n]
- Xét p, q là số nguyên tố. Nếu (p + q) % 2 == 0 thì g[(p + q) / 2]+=1

## 3. Độ phức tạp
- Thời gian: O(m)
- Không gian: O(m) (Vì tạo mảng để sàng nguyên tố)