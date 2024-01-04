## Giải thích code bài 1

### 1. Đề
Trong mặt phẳng cho nn≤103 điểm có tọa độ nguyên sao cho không có 2 điểm nào trùng nhau và không có 3 điểm nào thẳng hàng (n là một số chẵn). 
Yêu cầu: Hãy chọn ra 2 điểm trong số n điểm để đường thẳng qua 2 điểm này chia tập điểm thành 2 phần có số lượng điểm bằng nhau.
- Dữ liệu vào:
    - Dòng đầu tiên: n (2≤n≤10^3)
    - Dòng thứ i trong n dòng tiếp theo: xi,yixi,yi106 – tọa độ của điểm thứ i.
- Kết quả: 
    - Gồm 2 số là số thứ tự của 2 điểm được chọn.


### 2. Giải thích
- Tương tự cách thầy, chọn điểm thấp nhất sau đó đi so sánh cos của các góc.
- Công thức cos sử dụng trong bài này: 
$$cos(A) = \dfrac{b^2 + c^2 - a^2}{bc}$$
nếu ngại số thực thì có thể cân nhắc bình phương :v
### 3. Độ phức tạp
- Thời gian: $O(n \log{n})$
- Không gian: $O(n)$