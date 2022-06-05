cmake_minimum_required(VERSION 3.21)
project(BulletHell)

set(CMAKE_CXX_STANDARD 14)

set(SDL2_INCLUDE_DIR SDL2-2.0.10/include)
set(SDL2_LIB_DIR SDL2-2.0.10/lib/x86)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
link_libraries(${SDL_LIB_DIR})

add_executable(BulletHell main.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main.lib SDL2.lib)

