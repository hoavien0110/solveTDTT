## Giải thích code Bài 3

### 1. Đề
Cho hai dãy số nguyên 𝐴 = a1,a2,…, am và 𝐵 = (b1,b2,…, bn) hãy tìm một phần tử ai trong dãy 𝐴 và một phần tử bj trong dãy 𝐵 có |ai+bj| là nhỏ nhất có thể (1 ≤ 𝑖 ≤ 𝑚; 1 ≤ 𝑗 ≤ 𝑛). 
- Dữ liệu vào: 
    - Dòng 1 chứa hai số nguyên dương 𝑚, 𝑛 ≤ 105 
    - Dòng 2 chứa 𝑚 số nguyên a1,a2,…, am (∀𝑖: |ai| < 2 ×109 ) 
    - Dòng 3 chứa 𝑛 số nguyên b1,b2,…, bn (∀𝑗: |bj| < 2 ×109) 
- Kết quả: Ghi ra hai chỉ số 𝑖 và 𝑗 của hai phần tử tương ứng tìm được. 

### 2. Giải thích
- Ta cần tìm |ai + bj| nhỏ nhất, có nghĩa là với mỗi ai thì ta cần tìm bj sao cho bj gần với -ai nhất
- Thực hiện sort lại và chặt nhị phân tìm 2 số bj sao cho gần ai nhất. Dùng cấu trúc dữ liệu pair để lưu vết lại chỉ số cũ
- Sau khi tìm được 2 số bj, thực hiện so sánh.

### 3. Độ phức tạp 
- Thời gian:
    - Sort: $O(max(m \log{m}, n \log{n}))$ 
    - Search min: $O(m \log{n})$
- Không gian: 
    - Xây dựng vector: $O(\max (m, n))$
