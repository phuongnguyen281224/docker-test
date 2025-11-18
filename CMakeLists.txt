cmake_minimum_required(VERSION 3.16)

# Project name and language
project(stm32_project C)

# Enable CMAKE_TOOLCHAIN_FILE
enable_language(C)

# Executable
add_executable(${CMAKE_PROJECT_NAME}.elf main.c gpio.c rcc.c startup_stm32f103c8t6.S)

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
