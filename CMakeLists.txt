cmake_minimum_required(VERSION 3.2)
project(Adaptive_Huffman)

include_directories(inc)
include_directories(src)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp inc/model.h inc/encoder.h inc/decoder.h src/model.cpp src/encoder.cpp src/decoder.cpp inc/ahencode.h src/ahencode.cpp)
add_executable(Adaptive_Huffman ${SOURCE_FILES} inc/ahdecode.h src/ahdecode.cpp)