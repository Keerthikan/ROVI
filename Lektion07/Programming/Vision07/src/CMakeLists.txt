cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Vision07)

find_package(OpenCV REQUIRED)

add_executable(ROVI07 ROVI07.cpp)

target_link_libraries(ROVI07 ${OpenCV_LIBS})

