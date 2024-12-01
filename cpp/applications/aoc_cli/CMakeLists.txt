cmake_minimum_required(VERSION 3.16)

add_executable(aoc-2024-cli)
target_compile_features(aoc-2024-cli PUBLIC
    cxx_std_23
)

target_link_libraries(aoc-2024-cli PRIVATE
    aoc_y2024_core
)

add_subdirectory(src)

default_compile_options(aoc-2024-cli)
