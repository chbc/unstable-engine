#!/bin/bash

BUILD_DIR="build"
BIN_DIR="bin"

echo "--- Limpando ambiente ---"
rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR

rm -rf $BIN_DIR
mkdir -p $BIN_DIR

echo "--- Iniciando configuração com CMake ---"
cd $BUILD_DIR
cmake -DCMAKE_BUILD_TYPE=Debug ..

echo "--- Iniciando compilação ---"
make -j$(nproc)
