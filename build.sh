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
echo " Build Done!"
echo "========================================"

echo "ELF: ${BUILD_DIR}/${PROJECT}.elf"
