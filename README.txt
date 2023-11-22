Để chươnĐể chạy được chương trình thì cần chạy trên Visual Studio 2022 và chỉnh lại địa chỉ 2 thư viện SDL và SDL_image:
B1: Truy cập hướng dẫn ở link: https://lazyfoo.net/tutorials/SDL/01_hello_SDL/windows/msvc2019/index.php
    Chuyển đến bước 5 và bước 7 ở trong link. 
B2: Ở phần Include Directories, ta bấm mũi tên và bấm phần edit, sau đó xóa đi 2 địa chỉ:
           C:\Users\ADMIN\OneDrive\Desktop\Project\SDL2_image\include
           C:\Users\ADMIN\OneDrive\Desktop\Project\SDL2\include
    Sau đó Add lại địa chỉ của 2 thư viện SDL, SDL_image như trong link hướng dẫn (2 thư viện đã có sẵn trong file)
B3: Làm tương tự ở phần Library Directories.
