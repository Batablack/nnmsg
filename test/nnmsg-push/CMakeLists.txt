cmake_minimum_required(VERSION 3.10)
project(nnmsg_push)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/nanomsg)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(nnmsg_push main.cpp)
target_link_libraries(nnmsg_push nanomsg pthread)
