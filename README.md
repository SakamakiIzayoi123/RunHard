# RunHard
1.Cách cài đặt:
    Tại trang https://github.com/SakamakiIzayoi123/RunHard, chọn Code -> Download ZIP;
    Sau khi tải -> giải nén;
    cài môi trường SFML;
    C1: Mở thư mục vừa giải nén = Visual Studio Code rồi chạy Makefile được file main.exe;
    c2: {
            Nhấn giữ phím Shift, kích chuột phải vào thư mục RunHard-main, chọn Open command window here;
            g++ -c main.cpp -I "C:\SFML-2.5.1\include" -> Enter;
            g++  main.o -o main -L "C:\SFML-2.5.1\lib"  -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -> Enter;
        }
2.Mô tả trò chơi:
    Một cung thủ đi lạc vào khu rừng. Anh ta bị một con cóc lớn đuổi theo và lũ quái vật cản đường, trên trời là đàn rơi.
    Bằng khả năng của mình hãy giúp anh ta sống sót lâu nhất.
3.Mô tả chức năng cài đặt:
    Bật tăt âm thanh;
    Hệ thống điểm cao: sau mỗi lượt chơi điểm sẽ được ghi lại nếu đạt điểm cao;
4.Các kĩ thuật sử dụng:
    Mảng;
    Con trỏ;
    Lớp;
5.Kết luận, hướng phát triển và các điều tâm đắc rút ra được sau khi hoàn thiện chương trình
