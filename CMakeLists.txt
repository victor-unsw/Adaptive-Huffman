cmake_minimum_required(VERSION 3.2)
project(Adaptive_Huffman)

include_directories(inc)
include_directories(src)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES inc/model.h src/model.cpp)
add_executable(Encoder ${SOURCE_FILES} inc/encoder.h src/encoder.cpp)
add_executable(Decoder ${SOURCE_FILES} inc/decoder.h src/decoder.cpp)