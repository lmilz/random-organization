#!/bin/bash

BUILD_DIR="build"

echo "Start build process..."
if [ ! -d "$BUILD_DIR" ]; then
  mkdir "$BUILD_DIR"
fi
cd "$BUILD_DIR" || exit 1

cmake ..
if [ $? -ne 0 ]; then
  echo "Error: CMake"
  exit 1
fi

make -j$(nproc)
if [ $? -ne 0 ]; then
  echo "Error: Build."
  exit 1
fi
echo "Build was successfully!"


echo "Start tests process..."

ctest --output-on-failure
if [ $? -ne 0 ]; then
  echo "Error: Tests"
  exit 1
fi
echo "Tests were successfully!"
cd - || exit 1
