#!/bin/bash

BUILD_DIR="build"

echo "--- Limpando ambiente ---"
rm -rf $BUILD_DIR
mkdir -p $BUILD_DIR

echo "--- Iniciando configuração com CMake ---"
cd $BUILD_DIR
cmake -DCMAKE_BUILD_TYPE=Debug ..

echo "--- Iniciando compilação ---"
make -j$(nproc)
