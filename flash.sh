#!/bin/bash

set -e

PROJECT=BareMetalC
BUILD_DIR=build
ELF=${BUILD_DIR}/${PROJECT}.elf

echo "========================================"
echo " Flash STM32"
echo "========================================"

if [ ! -f "${ELF}" ]; then
    echo "Error: ${ELF} not found!"
    echo "Please run ./build.sh first."
    exit 1
fi

openocd \
    -f interface/stlink.cfg \
    -f target/stm32f4x.cfg \
    -c "program ${ELF} verify reset exit"

echo
echo "========================================"
echo " Flash Done!"
echo "========================================"
