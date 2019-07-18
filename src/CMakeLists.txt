cmake_minimum_required (VERSION 2.6)
project(CPU-Emulator)
set(CPU-Emulator_VERSION_MAJOR 0)
set(CPU-Emulator_VERSION_MINOR 1)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-Wall -Wextra -Wpedantic -g -o3)
file(GLOB emulator_SRC
    "*.hpp"
    "*.cpp"
)
add_executable(CpuEmulator ${emulator_SRC})
