cmake_minimum_required(VERSION 3.16)
project(MUL_my_rpg_2019 C)

set(CMAKE_C_STANDARD 99)

file(GLOB SRC_DIR
        "src/*.c"
        "src/my_printf/*.c")

add_executable(MUL_my_rpg_2019 ${SRC_DIR})

target_link_libraries(MUL_my_rpg_2019 csfml-window csfml-graphics csfml-audio csfml-system m)