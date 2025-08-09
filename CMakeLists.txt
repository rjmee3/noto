cmake_minimum_required(VERSION 3.16)
project(myvcs VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add src and tests
add_subdirectory(src)
add_subdirectory(tests)
