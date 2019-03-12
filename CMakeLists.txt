cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 20)

# For profiling.
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O0 -g -mno-omit-leaf-frame-pointer -fno-omit-frame-pointer")

add_executable(pool-allocator allocators/pool-allocator.cpp)
add_executable(linked-pool-allocator allocators/linked-pool-allocator.cpp)
add_executable(any-pool-allocator allocators/any-pool-allocator.cpp)
add_executable(testing testing.cpp)
add_executable(memory memory.cpp)
add_executable(vtable examples/vtable.cpp)
add_executable(jump-table examples/jump-table.cpp)