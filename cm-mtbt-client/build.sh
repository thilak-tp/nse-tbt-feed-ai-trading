#!/bin/bash

# Exit immediately on error
set -e

# Create and enter the build directory
mkdir -p build
cd build

# Run CMake configuration
cmake ..

# Build the project
cmake --build .

# Notify user
echo "✅ Build completed. Binary is at: ./bin/nse_client"

