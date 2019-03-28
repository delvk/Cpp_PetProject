Đây là guide hướng dẫn sử dụng thư viện opencv trên Window (cụ thể là VS Studio 15)
1. Tải CMAKE (google: cmake opencv window visual studio) 
2. Ở tag C/C++ trong property, chọn include thư mục install/include để có thêm thư viện
3. Ở linker, tag general thì add open_cv/build/lib/debug (ở đây ta cần cho nó thêm thư viện này để nó chạy các file .lib)
4. Vẫn ở linker -> Input các file .lib trong thư mục open_cv/build/lib/debug, có thể chạy Project2.exe để lấy tên từ file txt
5. Cuối cùng bạn cần install file .dll có sẵn trong thư mục open_cv/build/bin/debug, bằng cách add vào trong biến PATH của window