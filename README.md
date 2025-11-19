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
