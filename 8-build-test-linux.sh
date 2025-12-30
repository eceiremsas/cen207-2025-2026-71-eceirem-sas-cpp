#!/bin/bash
# chmod +x 8-build-test-linux.sh
# ./8-build-test-linux.sh

# Get the current directory path
currentDir=$(dirname "$(readlink -f "$0")")

echo "Delete and Create the 'release' folder and its contents"
rm -rf "release_linux"
rm -rf "publish_linux"
rm -rf "build_linux"
mkdir publish_linux
mkdir release_linux
mkdir build_linux

echo "Folders are Recreated successfully."

echo "Testing Application with Coverage"
echo "Configure CMAKE"
cmake -B build_linux -DCMAKE_BUILD_TYPE=Debug -G "Ninja" -DCMAKE_INSTALL_PREFIX:PATH=publish_linux
echo "Build CMAKE Debug"
cmake --build build_linux --config Debug -j4
echo "Build CMAKE Release"
cmake --build build_linux --config Release -j4
echo "Install CMAKE"
cmake --install build_linux --strip
echo "Test CMAKE"
cd build_linux
ctest -C Debug --output-on-failure
cd ..

echo "Running Test Executable"

if [ -f "./publish_linux/bin/recipe_tests" ]; then
    ./publish_linux/bin/recipe_tests
else
    echo "Warning: recipe_tests not found in publish_linux/bin"
    echo "Trying build_linux/build/Debug/recipe_tests"
    if [ -f "./build_linux/build/Debug/recipe_tests" ]; then
        ./build_linux/build/Debug/recipe_tests
    else
        echo "Error: recipe_tests executable not found"
    fi
fi

if [ -f "./publish_linux/bin/recipeapp" ]; then
    echo "Running recipeapp..."
    echo "0" | timeout 5 ./publish_linux/bin/recipeapp || true
fi

echo "Files and folders copied successfully."

echo "Package Publish Linux Binaries"
tar -czvf release_linux/linux-publish-binaries.tar.gz -C publish_linux .

echo "Package Publish Linux Binaries"
if [ -d "include" ]; then
    mkdir -p build_linux/build/Release
    cp -R include build_linux/build/Release
    tar -czvf release_linux/linux-release-binaries.tar.gz -C build_linux/build/Release .
fi

echo "Package Publish Debug Linux Binaries"
if [ -d "include" ]; then
    mkdir -p build_linux/build/Debug
    cp -R include build_linux/build/Debug
    tar -czvf release_linux/linux-debug-binaries.tar.gz -C build_linux/build/Debug .
fi

echo "...................."
echo "Operation Completed!"

