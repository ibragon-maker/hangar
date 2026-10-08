cmake_minimum_required(VERSION 3.10)
project(Hangar CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra)
endif()

# Absolute path to the data/ folder, so the program works no matter
# which directory you run it from.
set(hangar_data_dir "${CMAKE_SOURCE_DIR}/data")

add_library(hangar_core STATIC
    src/mech.cpp
    src/battle_sim.cpp
    src/roster_io.cpp
)
target_include_directories(hangar_core PUBLIC include)

add_executable(hangar app/main.cpp)
target_link_libraries(hangar PRIVATE hangar_core)
target_compile_definitions(hangar PRIVATE HANGAR_DATA_DIR="${hangar_data_dir}")

# Self-check: run ./build/check_io to test your roster_io functions.
add_executable(check_io tests/check_io.cpp)
target_link_libraries(check_io PRIVATE hangar_core)
target_compile_definitions(check_io PRIVATE HANGAR_DATA_DIR="${hangar_data_dir}")

enable_testing()
add_test(NAME check_io COMMAND check_io)
