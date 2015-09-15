cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Vision01)

find_package(OpenCV REQUIRED)

add_executable(ROVI01 ROVI01.cpp)

target_link_libraries(ROVI01 ${OpenCV_LIBS})

