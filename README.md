# Cpp_PetProject
This is a pet project for practice with c++
This include:
1. Data_Preparaiton 
    - Công dụng: Chuẩn bị tập dữ liệu train và tập dữ liệu test
    - Input: Folder chứa các hình ảnh để train và test, lưu ý là cần tự phân loại label cho các dữ liệu bằng tên thư mục, ví dụ A/A.1.jpg là sample thứ nhất của mẫu A
    - Output: Output_folder/training_set.csv + Output_folder/testing_set.csv, nội dung 2 file theo cấu trúc: path;name;label
    - Cách dùng: Chuẩn bị bộ dữ liệu, chương trình sẽ tự phân training/testing theo tỉ lệ 8/2 và ghi vào trong các file output

2. Data_Regconition 
    - Công dụng: Train model và lưu lại model
    - Input: training_set.csv ở trên
    - Output: Model.yml --> Tùy thuộc vào giải thuật chọn mà tên model sẽ khác nhau
    - Cách dùng: Kiểm tra file csv có tồn tại chưa, sau đó chạy chương trình

3. Predict_from_model
    - Công dụng: Load file model.yml đã lưu ở trên, dùng nó để dự đoán kết quả
    - Input: model.yml ở trên, testing_set.csv ở trên
    - Output: Dự đoán kết quả các file ở testing_set
    - Cách dùng: Kiểm tra file csv có tồn tại chưa, sau đó chạy chương trình

4. Data_cropping
    - Công dụng: Cắt ảnh chứa khuôn mặt (dùng để khi chụp ảnh = camera sẽ cắt ra làm tập huấn luyện)
    - Input: Ảnh chứa mặt người muốn huấn luyện
    - Output: Ảnh bị lượt bỏ phần background không chứa mặt người
    - Cách dùng: Đổi tên thư mục input thành thư mục chứa ảnh cần cắt là được

5. Face_Localization
    - Công dụng: Chạy camera/hình để predict mặt người
    - Input: hình hoặc camera
    - Output: 
    - Cách dùng:

6. Get_Lib_File_Name
    - Công dụng: Dùng khi muốn add input trong Linker khi dùng opencv, sẽ tạo ra file lib.txt chứa tên các file *.lib
    - Input: không
    - Output: lib.txt
    - Cách dùng: Đem project vào thư mục chứa các file đó và chạy

7. Real_Time_Regconize
    - Công dụng: Đoán mặt người qua camera thời gian thực
    - Input: model.yml
    - Output:
    - Cách dùng: Chạy khi đã train xong nha !

