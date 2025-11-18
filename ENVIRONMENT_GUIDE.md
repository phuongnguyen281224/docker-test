# Hướng Dẫn Chỉnh Sửa Môi Trường Dự Án

Tài liệu này hướng dẫn cách chỉnh sửa môi trường phát triển Docker và cấu hình build cho dự án STM32F103C8T6.

---

## Phần 1: Chỉnh Sửa Môi Trường Docker

### 1.1. Thêm Các Gói Phụ Thuộc Mới

Tất cả các gói phụ thuộc và công cụ cần thiết cho môi trường build được định nghĩa trong file `Dockerfile`. Để thêm một công cụ mới (ví dụ: `gdb-multiarch` để debug), bạn cần chỉnh sửa file này.

1.  **Mở file `Dockerfile`:**
    Tìm đến dòng `apt-get install -y --no-install-recommends \`.

2.  **Thêm gói mới:**
    Thêm tên gói mới vào danh sách. Ví dụ, để thêm `gdb-multiarch`, bạn sửa lại như sau:

    ```dockerfile
    # ... các dòng trên ...
    RUN apt-get update && \
        export DEBIAN_FRONTEND=noninteractive && \
        apt-get install -y --no-install-recommends \
        # ... các gói khác ...
        gdb-multiarch # Gói mới được thêm vào đây
    # ... các dòng dưới ...
    ```

### 1.2. Thay Đổi Cấu Hình Docker Compose

File `docker-compose.yml` định nghĩa cách Docker sẽ khởi chạy và quản lý container. Bạn có thể chỉnh sửa file này để thay đổi các thiết lập như ánh xạ cổng (port mapping).

Ví dụ, để ánh xạ cổng `3333` từ container ra máy host cho GDB server:

1.  **Mở file `docker-compose.yml`**.
2.  **Thêm cấu hình `ports`**:

    ```yaml
    services:
      stm32_dev:
        # ...
        ports:
          - "3333:3333" # Ánh xạ cổng 3333
        command: tail -f /dev/null
    ```

### 1.3. Build Lại Môi Trường Docker

Sau khi bạn đã chỉnh sửa `Dockerfile` hoặc `docker-compose.yml`, bạn cần build lại Docker image để các thay đổi có hiệu lực.

```bash
docker-compose up -d --build
```

---

## Phần 2: Chỉnh Sửa Cấu Hình Build (CMake)

Hệ thống build của dự án sử dụng `CMake`. File `CMakeLists.txt` ở thư mục gốc định nghĩa cách dự án được biên dịch.

### 2.1. Thêm File Nguồn Mới

`CMakeLists.txt` hiện tại sử dụng `file(GLOB_RECURSE ...)` để tự động tìm tất cả các file `.c` trong `src/` và `drivers/src/`.

Nếu bạn đặt các file nguồn của mình đúng trong các thư mục này, `CMake` sẽ tự động tìm thấy chúng. Nếu bạn tạo một thư mục mới cho file nguồn (ví dụ: `libs/`), bạn cần thêm đường dẫn đó vào lệnh `file()`:

```cmake
file(GLOB_RECURSE SOURCES "src/*.c" "drivers/src/*.c" "libs/*.c")
```

### 2.2. Thêm Thư Mục Include

Nếu bạn thêm một thư viện mới có các file header (`.h`), bạn cần cho `CMake` biết nơi để tìm chúng bằng cách sử dụng `include_directories()`:

```cmake
include_directories(
    src
    drivers/inc
    libs/inc  # Thêm thư mục include mới
)
```

### 2.3. Thay Đổi Cờ Biên Dịch (Compiler Flags)

Các cờ biên dịch (compiler flags) được định nghĩa trong file `toolchain.cmake`. Nếu bạn muốn thay đổi các tùy chọn tối ưu hóa (`-O`), thêm định nghĩa (`-D`), hoặc cờ cảnh báo (`-W`), bạn nên sửa file này.

Ví dụ, để thay đổi mức tối ưu hóa từ `-O0` thành `-O2`:

1.  **Mở file `toolchain.cmake`**.
2.  Tìm đến dòng `set(COMMON_FLAGS ...)`
3.  Thay đổi `-O0` thành `-O2`.

### 2.4. Quy Trình Build Sau Khi Thay Đổi

Sau khi chỉnh sửa `CMakeLists.txt` hoặc `toolchain.cmake`, bạn cần **chạy lại từ đầu** để áp dụng thay đổi.

1.  **Truy cập vào container**:
    ```bash
    docker-compose exec stm32_dev /bin/bash
    ```
2.  **Xóa thư mục `build` cũ (quan trọng)**:
    ```bash
    rm -rf build
    ```

3.  **Tạo lại và build**:
    ```bash
    mkdir build
    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake
    make
    ```
