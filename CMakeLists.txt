cmake_minimum_required(VERSION 3.24.2)
project(PROJET_PROGC_MIDL C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_CFLAGS "-Wall -Wextra -Werror -Wpedantic -std=c11 -fsanitize=address")

include_directories(include)

file(GLOB_RECURSE SOURCES "src/commun/*.c")
file(GLOB_RECURSE SRC_NV1 "src/niveau1/*.c")
file(GLOB_RECURSE SRC_NV2 "src/niveau2/*.c")
file(GLOB_RECURSE SRC_NV3 "src/niveau3/*.c")
file(GLOB_RECURSE HEADERS "include/*.h")

add_executable("niveau1" ${SRC_NV1} ${SOURCES} ${HEADERS})
add_executable("niveau2" ${SRC_NV2} ${SOURCES} ${HEADERS})
add_executable("niveau3" ${SRC_NV3} ${SOURCES} ${HEADERS})
target_link_libraries("niveau1" "-lm")
target_link_libraries("niveau2" "-lm")
target_link_libraries("niveau3" "-lm")