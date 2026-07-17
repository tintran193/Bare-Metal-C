#!/bin/bash

set -e

PROJECT=BareMetalC
BUILD_DIR=build

echo "========================================"
echo " Configure Project"
echo "========================================"

cmake -S . -B ${BUILD_DIR}

echo
echo "========================================"
echo " Build Project"
echo "========================================"

cmake --build ${BUILD_DIR}

echo
echo "========================================"
echo " Flash STM32"
echo "========================================"

openocd \
    -f interface/stlink.cfg \
    -f target/stm32f4x.cfg \
    -c "program ${BUILD_DIR}/${PROJECT}.elf verify reset exit"

echo
echo "========================================"
echo " Done!"
echo "========================================"