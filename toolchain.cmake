# Set the target system
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Specify the cross-compilers
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_SIZE arm-none-eabi-size)

# Set compiler flags
set(CPU "-mcpu=cortex-m3")
set(FPU "-mfloat-abi=soft")
set(MCU "-mthumb")
set(COMMON_FLAGS "${CPU} ${FPU} ${MCU}")

set(CMAKE_C_FLAGS "${COMMON_FLAGS} -g3 -Wall -Wextra -Wpedantic -std=gnu11" CACHE INTERNAL "C compiler flags")
set(CMAKE_ASM_FLAGS "${COMMON_FLAGS} -g3" CACHE INTERNAL "ASM compiler flags")

# Set linker flags
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/linker/linker.ld")
set(CMAKE_EXE_LINKER_FLAGS "-nostdlib --specs=nosys.specs -Wl,-Map=${PROJECT_NAME}.map -Wl,--gc-sections -T ${LINKER_SCRIPT} ${COMMON_FLAGS}" CACHE INTERNAL "Linker flags")

# Set build type defaults
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_options(-Og)
else()
  add_compile_options(-O2)
endif()
