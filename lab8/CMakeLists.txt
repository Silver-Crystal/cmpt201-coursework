cmake_minimum_required(VERSION 3.22)

project(
  Lab8
  VERSION 1.0
  DESCRIPTION "This is an example for the lab."
  LANGUAGES C)

set(CMAKE_BUILD_TYPE Debug)

# Note: ASan and TSan are incompatible

# Address sanitization:

# add_compile_options(-fsanitize=address)

# add_link_options(-fsanitize=address)

# --------- Task 3 ---------

# Enable the thread sanitizer

# TODO

# add_compile_options(-pthread -fsanitize=thread -g -O1)
add_compile_options(-pthread)
# add_compile_options(-fsanitize=thread -g -O1)

# add_link_options(-pthread -fsanitize=thread -g -O1)
add_link_options(-pthread)

# add_link_options(-fsanitize=thread -g -O1)

# -fsanitize=thread -g -O1)

# add_link_options(-fsanitize=thread -g -O1)

add_executable(main src/lab8.c)
add_executable(main_normal src/lab8.c)
add_executable(dumb src/lab8.c)
add_executable(asan src/lab8.c)
add_executable(msan src/lab8.c)

target_include_directories(main PRIVATE include)
target_include_directories(main_normal PRIVATE include)
target_include_directories(dumb PRIVATE include)
target_include_directories(asan PRIVATE include)
target_include_directories(msan PRIVATE include)

target_compile_options(main PRIVATE -fsanitize=thread -g -O1)
target_link_options(main PRIVATE -fsanitize=thread -g -O1)

target_compile_options(main_normal PRIVATE -fsanitize=thread -g)
target_link_options(main_normal PRIVATE -fsanitize=thread -g)

target_compile_options(dumb PRIVATE -g)
target_link_options(dumb PRIVATE -g)

target_compile_options(asan PRIVATE -fsanitize=address -g)
target_link_options(asan PRIVATE -fsanitize=address -g)

target_compile_options(msan PRIVATE -fsanitize=address -g)
target_link_options(msan PRIVATE -fsanitize=address -g)
