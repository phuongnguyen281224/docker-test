# STM32F103C8T6 Dockerized Development Environment

This project provides a complete Dockerized environment for developing applications on the STM32F103C8T6 microcontroller, commonly found on "Blue Pill" boards. It uses the ARM GNU Toolchain, CMake, and Make for a streamlined build process.

The current example code blinks the onboard LED connected to pin PC13.

---

## English Instructions

### Prerequisites

*   [Docker Desktop](https://docs.docker.com/get-docker/) installed and running on your system.

### Project Structure

*   `drivers/inc/stm32f1xx.h`: Main header file with register definitions.
*   `drivers/src/`: Source files for peripheral drivers (RCC, GPIO, etc.).
*   `src/`: Main application source code.

### Quick Build

This project includes convenient scripts to automate the entire build process for different operating systems.

#### Windows

1.  **Run the Build Script:**
    Double-click on `run_build.bat` or run it from Command Prompt/PowerShell.
    ```cmd
    run_build.bat
    ```

#### macOS / Linux

1.  **Run the Build Script:**
    Open a terminal in the project's root directory and execute the `run_build.sh` script.
    ```bash
    chmod +x run_build.sh
    ./run_build.sh
    ```

### Output

The compiled firmware files (`.hex`, `.bin`, `.elf`) will be located in the `build/` directory. You can use tools like OpenOCD or ST-Link Utility to flash the firmware.

---

## Hướng Dẫn Tiếng Việt

### Yêu Cầu

*   Đã cài đặt và bật [Docker Desktop](https://docs.docker.com/get-docker/) trên máy tính của bạn.

### Cấu Trúc Dự Án

*   `drivers/inc/stm32f1xx.h`: File header chính chứa định nghĩa các thanh ghi.
*   `drivers/src/`: Mã nguồn các driver ngoại vi (RCC, GPIO,...).
*   `src/`: Mã nguồn chính của ứng dụng.

### Xây Dựng Nhanh (Quick Build)

Dự án cung cấp các script để tự động hóa quá trình build trên các hệ điều hành khác nhau.

#### Windows

1.  **Chạy Script:**
    Nhấn đúp chuột vào file `run_build.bat` hoặc chạy từ Command Prompt.
    ```cmd
    run_build.bat
    ```

#### macOS / Linux (Ubuntu)

1.  **Chạy Script:**
    Mở terminal tại thư mục dự án và chạy lệnh:
    ```bash
    chmod +x run_build.sh
    ./run_build.sh
    ```

### Kết Quả

Các file firmware đã biên dịch (`.hex`, `.bin`, `.elf`) sẽ nằm trong thư mục `build/`. Bạn có thể dùng OpenOCD hoặc ST-Link Utility để nạp code.
