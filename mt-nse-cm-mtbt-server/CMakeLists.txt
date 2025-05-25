cmake_minimum_required(VERSION 3.20)

# Project name and C++ standard
project(nse_simulator_mt VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source and include directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_SOURCE_DIR}/inc")
include_directories(${INC_DIR})

# Recursively collect all .cpp files in src/
file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")

# Create the output binary directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Define the executable
add_executable(nse_sim_mt ${SRCS})

# Add compile warnings
target_compile_options(nse_sim_mt PRIVATE -Wall -Wextra)

