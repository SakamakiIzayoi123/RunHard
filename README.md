# RunHard
1.Cách cài đặt:
    Tại trang https://github.com/SakamakiIzayoi123/RunHard, chọn Code -> Download ZIP;
    Sau khi tải -> giải nén;
    cài môi trường SFML;
    Mở thư mục vừa giải nén = Visual Studio Code rồi chạy Makefile được file main.exe;
2.Mô tả trò chơi:
    Trò chơi điều khiển nhân vật di chuyển tránh quái vật và đòn tấn công của kẻ thù.
    Dùng các phím A, S, D, W hoặc Numpad1, C, Numpad3, Z để di chuyển và tấn công.
    Khi đang trên không có thể nhảy thêm lần nữa và không thể thay đổi hướng(trừ khi nhảy).
    Có 4 loại quái vật gồm:
        - 1 con cóc đuổi theo nhân vật ở phía sau, có thể bắn chất độc để tấn công, bất tủ nhưng vẫn sẽ kêu đau nwsu bị tấn công.
        - tê giác chỉ chạy thẳng.
        - dơi bay thẳng.
        - 1 con creep sẽ đuổi theo, tấn công nhân vật nếu ở gần, có khả năng chặn đòn tấn công của người chơi.
    Điểm được tính theo thời gian, sống sót càng lâu điểm càng cao.
3.Mô tả chức năng cài đặt:
    https://youtu.be/FAV9kosR61I;
    FPS được đặt ở mức 60;
    Âm thanh đa dạng có thể bật tắt tại menu;
    Hiển thị điểm khi đang chơi và khi chết, điểm cao sẽ được lưu lại ở High Score(hình cái cúp trong Menu);
    Hình nền nhiều lớp được tạo thành từ 12 file png tạo cảm giác chân thực, sống động khi di chuyển;
    Quái vật ra là ngẫu nhiền (vận tốc và vị trí xuất hiện) nhưng có giưới hạn tối đa xuất hiện cùng lúc;
4.Các kĩ thuật sử dụng:
    Mảng tĩnh, Vector, Con trỏ, ...;
    Class: nhiều đối tượng được tạo;
    Sinh số ngẫu nhiên;
    Thư viện hình ảnh Graphics.hpp, âm thanh Audio.hpp;
    Quản lí dữ liệu(file dataManager.h) tránh lỗi load 1 hình ảnh, âm thanh nhiều lần;
    Thao tác với file: Mở file, đọc dữ liệu, lưu dữ liệu, ...;
    ....
5.Kết luận, hướng phát triển và các điều tâm đắc rút ra được sau khi hoàn thiện chương trình
    Hướng phát triển cho game: 
        - Tạo ra thêm các item(tăng điểm nhận được trong 1 khoảng thời gian, item cho khả năng bất tử, ...).
        - Thêm chức năng thông báo và lưu tên người chơi khi được điểm cao.
        - Cập nhật thêm nhân vật lựa chọn;
    Kết luận:
