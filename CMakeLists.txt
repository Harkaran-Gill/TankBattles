cmake_minimum_required(VERSION 3.31)
project(TankWars C)

set(CMAKE_C_STANDARD 11)
set(SDL2_DIR "C:/SDL2-2.0.12/x86_64-w64-mingw32")
include_directories(${SDL2_DIR}/include/SDL2)
link_directories(${SDL2_DIR}/lib)

add_executable(TankWars main.c game.c tank.c projectile.c)

target_link_libraries(TankWars SDL2)
