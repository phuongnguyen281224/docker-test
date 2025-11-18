# Hướng Dẫn Chỉnh Sửa Môi Trường Dự Án

Tài liệu này hướng dẫn cách chỉnh sửa môi trường phát triển Docker cho dự án STM32F103C8T6. Bạn có thể cần thêm các công cụ mới hoặc thay đổi cấu hình container để phù hợp với nhu- cầu phát triển của mình.

---

## 1. Thêm Các Gói Phụ Thuộc Mới

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
        build-essential \
        cmake \
        git \
        wget \
        unzip \
        gcc-arm-none-eabi \
        binutils-arm-none-eabi \
        libnewlib-arm-none-eabi \
        gdb-multiarch # Gói mới được thêm vào đây
    # ... các dòng dưới ...
    ```

---

## 2. Thay Đổi Cấu Hình Docker Compose

File `docker-compose.yml` định nghĩa cách Docker sẽ khởi chạy và quản lý container của bạn. Bạn có thể chỉnh sửa file này để thay đổi các thiết lập như ánh xạ cổng (port mapping) hoặc thêm biến môi trường.

Ví dụ, nếu bạn cần ánh xạ cổng `3333` từ container ra máy host để sử dụng cho GDB server:

1.  **Mở file `docker-compose.yml`:**

2.  **Thêm cấu hình `ports`:**
    Thêm mục `ports` vào dưới `stm32_dev` service:

    ```yaml
    services:
      stm32_dev:
        build:
          context: .
          dockerfile: Dockerfile
          args:
            - USERNAME=${USERNAME:-vscode}
            - USER_UID=${USER_UID:-1000}
            - USER_GID=${USER_GID:-1000}
        volumes:
          - ..:/workspace:cached
        ports:
          - "3333:3333" # Ánh xạ cổng 3333
        command: tail -f /dev/null
    ```

---

## 3. Build Lại Môi Trường

Sau khi bạn đã chỉnh sửa `Dockerfile` hoặc `docker-compose.yml`, bạn cần build lại Docker image để các thay đổi có hiệu lực.

Chạy lệnh sau từ thư mục gốc của dự án:

```bash
docker-compose up -d --build
```

Lệnh này sẽ:
*   `--build`: Buộc Docker phải build lại image dựa trên các file cấu hình mới nhất.
*   `-d`: Chạy container ở chế độ nền (detached mode).

Sau khi quá trình build hoàn tất, môi trường phát triển của bạn đã được cập nhật với các công cụ và cấu hình mới. Bạn có thể truy cập vào container như bình thường:

```bash
docker-compose exec stm32_dev /bin/bash
```
