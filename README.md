# STM32F103C8T6 Dockerized Development Environment

This project provides a complete Dockerized environment for developing applications on the STM32F103C8T6 microcontroller, commonly found on "Blue Pill" boards. It uses the ARM GNU Toolchain, CMake, and Make for a streamlined build process.

The current example code blinks the onboard LED connected to pin PC13.

---

## English Instructions

### Prerequisites

*   [Docker](https://docs.docker.com/get-docker/) installed on your system.

### Quick Build

This project includes a convenient script to automate the entire build process.

1.  **Clone the Repository:**
    ```bash
    git clone <repository_url>
    cd <repository_name>
    ```

2.  **Run the Build Script:**
    Open a terminal in the project's root directory and execute the `run_build.sh` script. This command will automatically start the Docker environment and compile the project.
    ```bash
    ./run_build.sh
    ```

3.  **Find the Output Files:**
    The compiled firmware files (`.hex`, `.bin`, `.elf`) will be located in the `build/` directory. You can now use a tool like OpenOCD or ST-Link to flash the firmware to your STM32F103C8T6 board.

---

## Hướng Dẫn Tiếng Việt

### Yêu Cầu

*   Đã cài đặt [Docker](https://docs.docker.com/get-docker/) trên máy tính của bạn.

### Xây Dựng Nhanh

Dự án này bao gồm một script tiện lợi để tự động hóa toàn bộ quá trình xây dựng.

1.  **Clone Repository:**
    ```bash
    git clone <repository_url>
    cd <repository_name>
    ```

2.  **Chạy Script Xây Dựng:**
    Mở một terminal trong thư mục gốc của dự án và thực thi script `run_build.sh`. Lệnh này sẽ tự động khởi chạy môi trường Docker và biên dịch dự án.
    ```bash
    ./run_build.sh
    ```

3.  **Tìm Các File Output:**
    Các file firmware đã được biên dịch (`.hex`, `.bin`, `.elf`) sẽ nằm trong thư mục `build/`. Bây giờ bạn có thể sử dụng một công cụ như OpenOCD hoặc ST-Link để nạp firmware vào board STM32F103C8T6 của bạn.
