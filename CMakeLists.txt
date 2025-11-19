cmake_minimum_required(VERSION 3.16)

# Project name and language
project(stm32_project C ASM)

# Enable CMAKE_TOOLCHAIN_FILE
# enable_language(C) # project() already does this

# Define source files
file(GLOB_RECURSE SOURCES "src/*.c" "drivers/src/*.c")
file(GLOB STARTUP_SOURCES "startup/*.S")

# Include directories
include_directories(
    src
    drivers/inc
)

# Executable
add_executable(${CMAKE_PROJECT_NAME}.elf ${SOURCES} ${STARTUP_SOURCES})

# Post-build steps
add_custom_command(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.hex
    COMMENT "Generating .hex file"
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin
    COMMENT "Generating .bin file"
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJDUMP} -d -S ${CMAKE_PROJECT_NAME}.elf > ${CMAKE_PROJECT_NAME}.list
    COMMENT "Generating .list file"
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_SIZE} ${CMAKE_PROJECT_NAME}.elf
    COMMENT "Printing size information"
)
