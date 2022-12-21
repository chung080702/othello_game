<h1>Othello AI</h1>

Yêu cầu: Cần phiên bản c++ ít nhất là `c++17`, phiên bản python ít nhất là `python3.6` và để chạy giao diện cần cài đặt `tkinkter` tương ứng với hệ điều hành


Để thực hiện dịch một file

```
g++ -std=c++17 <path-to-file>.cpp
```

Để thực thi file sau khi dịch

`./a.out` hoặc `./a.exe` tuỳ vào hệ điều hành

---

<h2> Cấu trúc thư mục </h2>

Thư mục samples lưu một số dữ liệu bảng mẫu

Thư mục benchmark để chạy benchmark thuật toán

- `./benchmark/time-space.cpp` benchmark thời gian và không gian thực hiện
- `./benchmark/vs-heuristic.cpp` benchmark kết quả giữa 2 thuật toán AI

Thư mục test chứa các file test kết quả các hàm hỗ trợ và tham số các hàm đánh giá

Thư mục src chứa toàn bộ file mã nguồn

- `server.cpp` server ai giao tiếp với giao diện
- `ui.py` giao diện của chương trình
- `demo.cpp` để chạy thử nước đi sử dụng dữ liệu 1 bảng từ dữ liệu của người dùng nhập
- thư mục `othello` chứa mã nguồn của thuật toán AI

`openbook.txt` chứa danh sách các nước đi ban đầu phổ biến

`time.log` và `vs-heuristic.log` là kết quả của quá trình benchmark

---

<h2>Chạy chương trình</h2>

Trước khi chạy giao diện cần dịch và chạy `src/server.cpp` để khởi tạo server AI ở cổng 6666.

Chạy giao diện

```
python3 src/ui.py <game_mode> <ai_mode1> <ai_mode2>
```

`game_mode`

- 0 Người vs người
- 1 Người vs AI
- 2 AI vs người
- 3 AI vs AI

`ai_mode1`, `ai_mode2` giá trị từ 1 đến 6 tương ứng với 6 hàm heuristic

Ví dụ để chạy AI chơi với AI với AI 1 dùng hàm F1, AI 2 dùng hàm F6

```
python3 src/ui.py 3 1 6
```
