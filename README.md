# STM32F103C8T6 Dockerized Development Environment

This project provides a complete Dockerized environment for developing applications on the STM32F103C8T6 microcontroller, commonly found on "Blue Pill" boards. It uses the ARM GNU Toolchain, CMake, and Make for a streamlined build process.

The current example code blinks the onboard LED connected to pin PC13.

---

## English Instructions

### Prerequisites

*   [Docker](https://docs.docker.com/get-docker/) installed on your system.

### Setup and Build

1.  **Clone the Repository:**
    ```bash
    git clone <repository_url>
    cd <repository_name>
    ```

2.  **Build and Run the Docker Container:**
    Open a terminal in the project's root directory and run the following command. This will build the Docker image and start a container in the background.
    ```bash
    docker-compose up -d --build
    ```

3.  **Access the Container's Shell:**
    ```bash
    docker-compose exec stm32_dev /bin/bash
    ```

4.  **Build the Project:**
    Inside the container's shell, create a build directory and run CMake and Make.
    ```bash
    mkdir build
    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake
    make
    ```

5.  **Find the Output Files:**
    The compiled firmware files (`.hex`, `.bin`, `.elf`) will be located in the `build` directory. You can now use a tool like OpenOCD or ST-Link to flash the `.bin` or `.hex` file to your STM32F103C8T6 board.

---

## Hướng Dẫn Tiếng Việt

### Yêu Cầu

*   Đã cài đặt [Docker](https://docs.docker.com/get-docker/) trên máy tính của bạn.

### Cài Đặt và Biên Dịch

1.  **Clone Repository:**
    ```bash
    git clone <repository_url>
    cd <repository_name>
    ```

2.  **Build và Chạy Docker Container:**
    Mở một terminal trong thư mục gốc của dự án và chạy lệnh sau. Lệnh này sẽ build Docker image và khởi chạy một container ở chế độ nền.
    ```bash
    docker-compose up -d --build
    ```

3.  **Truy Cập Shell của Container:**
    ```bash
    docker-compose exec stm32_dev /bin/bash
    ```

4.  **Biên Dịch Dự Án:**
    Bên trong shell của container, tạo một thư mục `build` và chạy CMake và Make.
    ```bash
    mkdir build
    cd build
    cmake .. -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake
    make
    ```

5.  **Tìm Các File Output:**
    Các file firmware đã được biên dịch (`.hex`, `.bin`, `.elf`) sẽ nằm trong thư mục `build`. Bây giờ bạn có thể sử dụng một công cụ như OpenOCD hoặc ST-Link để nạp file `.bin` hoặc `.hex` vào board STM32F103C8T6 của bạn.
