cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 17)

add_executable(pool-allocator allocators/pool-allocator.cpp)
add_executable(linked-pool-allocator allocators/linked-pool-allocator.cpp)