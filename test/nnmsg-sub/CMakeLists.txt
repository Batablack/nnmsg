cmake_minimum_required(VERSION 3.10)
project(nnmsg_sub)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/nanomsg)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(nnmsg_sub main.cpp src/nnmsg.h)
target_link_libraries(nnmsg_sub nanomsg pthread)
