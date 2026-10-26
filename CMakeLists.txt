cmake_minimum_required(VERSION 3.20)
project(minikv LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)   # helps VS Code / clangd

add_executable(minikv src/main.cpp src/kv_store.cpp)
target_compile_options(minikv PRIVATE -Wall -Wextra -Wpedantic)

option(ENABLE_ASAN "Build with Address/UB sanitizers" OFF)
if(ENABLE_ASAN)
  target_compile_options(minikv PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(minikv PRIVATE -fsanitize=address,undefined)
endif()