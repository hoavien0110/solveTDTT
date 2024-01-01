## Giải thích code Bài 8

### 1. Đề
Cho bàn cờ kích thước n×n. Hãy tìm tất cả các cách đặt n quân hậu lên bàn cờ này sao cho không có 2 quân hậu nào có thể tấn công lẫn nhau. Biết rằng các quân hậu có thể di chuyển theo hàng dọc, hàng ngang và đường chéo.
- Dữ liệu vào
    - Gồm số n là kích thước cạnh của bàn cờ và số lượng quân hậu. (1≤n≤9)
- Kết quả
    - Dòng đầu tiên chứa số m là số cách đặt các quân hậu khác nhau có thể có.
    - Các dòng bên dưới chứa các ma trận đại diện cho bàn cờ kết quả. Các ma trận cách nhau bởi một dòng trống.
    - Mỗi ma trận gồm n dòng. Mỗi dòng chứa n ký tự:
        - Ký tự ‘.’ biểu diễn tại vị trí ô trống 
        - Ký tự ‘Q’ biểu diễn vị trí đó chứa quân hậu

### 2. Giải thích 
- Đệ quy đơn giản, kiểm tra điều kiện xem có thỏa không. Nếu thỏa thì đặt, không thì quay lui

### 3. Độ phức tạp
- Thời gian:
    - isValid: $O(n)$
    - solve: $O(n^n)$ vì duyệt tất cả -> xấu nhất là 9^9 ~ 2^29
- Không gian:
    - $O(n^2)$