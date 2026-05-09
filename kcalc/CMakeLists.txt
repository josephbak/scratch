cmake_minimum_required(VERSION 3.15)
project(kcalc VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable sanitizers to catch memory leaks/UB immediately
add_compile_options(-fsanitize=address,undefined -g -Wall -Wextra)
add_link_options(-fsanitize=address,undefined)

add_executable(kcalc
    src/main.cpp
    src/lexer.cpp
    src/parser.cpp
)

target_include_directories(kcalc PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)