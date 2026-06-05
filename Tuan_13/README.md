**Bài Tập Tuần 13 - Cấu trúc dữ liệu và Giải thuật**  
**Cài đặt Cây Nhị Phân Tìm Kiếm (Binary Search Tree - BST) và phân tích độ phức tạ** **p thuật toán.**  
1. **Yêu cầu bài toán**  
Cài đặt cấu trúc Cây nhị phân tìm kiếm (BST) bằng C++.  
   
 Thêm dãy số năm sinh vào cây: 2001, 2002, 2006, 2007, 2003, 2004, 2005, 2001, 1999, 2004.  
   
 Thực hiện thuật toán tìm kiếm giá trị 2004 và in ra trình tự các nút duyệt qua.  
**2. ** **Phân tích độ phức tạp thuật toán tìm kiếm trên B** **ST**  
Quá trình tìm kiếm trên Cây nhị phân tìm kiếm phụ thuộc trực tiếp vào chiều cao của cây ( h ). Tại mỗi bước duyệt, thuật toán so sánh giá trị cần tìm với nút hiện tại và quyết định rẽ nhánh trái hoặc phải. Độ phức tạp cụ thể như sau:  
Trường hợp tốt nhất (Best Case): O ( 1 ) - Xảy ra khi phần tử cần tìm nằm ngay tại nút gốc (Root) của cây. Thuật toán chỉ cần thực hiện 1 phép so sánh duy nhất và kết thúc ngay.  
   
 Trường hợp trung bình (Average Case): O ( log ⁡ n ) - Xảy ra khi dữ liệu đầu vào ngẫu nhiên, giúp cây phát triển tương đối cân bằng. Tại mỗi bước rẽ nhánh, thuật toán loại bỏ được khoảng một nửa số lượng nút.  
   
 Trường hợp xấu nhất (Worst Case): O ( n ) - Xảy ra khi mảng dữ liệu đầu vào đã được sắp xếp sẵn (tăng dần hoặc giảm dần). Lúc này, cây BST bị "suy biến" thành một danh sách liên kết đơn (lệch hoàn toàn về nhánh trái hoặc phải). Thuật toán sẽ phải duyệt qua tuần tự từng nút.  
1. **Kết quả thực thi**  
Khi tìm kiếm năm sinh 2004 trong cây, chương trình in ra kết quả: Trinh tu duyet cay: 2001 -> 2002 -> 2006 -> 2003 -> 2004 (Da tim thay gtri can tim)  
