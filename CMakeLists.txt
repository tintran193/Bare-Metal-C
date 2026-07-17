cmake_minimum_required(VERSION 3.10)


#------------------------------------------
# Toolchain
#------------------------------------------
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_SIZE arm-none-eabi-size)

#------------------------------------------
# Project
#------------------------------------------
project(BareMetalC C ASM)
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

#------------------------------------------
# Compiler flags
#------------------------------------------
set (MCPU cortex-m4)
set (MFPU fpv4-sp-d16)
set (MFLOAT_ABI hard)

set (MCU_FLAGS "-mcpu=${MCPU} -mthumb -mfloat-abi=${MFLOAT_ABI} -mfpu=${MFPU}")

set (CMAKE_C_FLAGS "${MCU_FLAGS} -Wall -O0 -g3 -ffunction-sections -fdata-sections")
set (CMAKE_ASM_FLAGS "${MCU_FLAGS} -x assembler-with-cpp -Wall -O0 -g3 -ffunction-sections -fdata-sections")

set(LINKER_SCRIPT ${PROJECT_DIR}/STM32F401RETX_FLASH.ld)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MCU_FLAGS} -T ${LINKER_SCRIPT} -Wl,--gc-sections --specs=nosys.specs --specs=nano.specs -Wl,-Map=${PROJECT_NAME}.map")

#------------------------------------------
# Source files
#------------------------------------------
file(GLOB_RECURSE APP_SRC ${PROJECT_DIR}/App/*.c)
file(GLOB_RECURSE BSP_SRC ${PROJECT_DIR}/BSP/Src/*.c)
file(GLOB_RECURSE DRIVER_SRC ${PROJECT_DIR}/Driver/Src/*.c)
file(GLOB_RECURSE STARTUP_SRC ${PROJECT_DIR}/Startup/*.s ${PROJECT_DIR}/Startup/*.S)

set(SOURCES ${APP_SRC} ${BSP_SRC} ${DRIVER_SRC} ${STARTUP_SRC})

#------------------------------------------
# Executable
#------------------------------------------
add_executable(${PROJECT_NAME}.elf ${SOURCES})

#------------------------------------------
# Header files
#------------------------------------------
target_include_directories(${PROJECT_NAME}.elf PRIVATE
    ${PROJECT_DIR}/Driver/Inc
    ${PROJECT_DIR}/BSP/Inc
    ${PROJECT_DIR}/App
)

#------------------------------------------
# Linker script
#------------------------------------------



#------------------------------------------
# Post-build commands
#------------------------------------------
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
    COMMAND ${CMAKE_OBJDUMP} -h -S ${PROJECT_NAME}.elf > ${PROJECT_NAME}.lst
)