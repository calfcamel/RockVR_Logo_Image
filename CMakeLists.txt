cmake_minimum_required(VERSION 3.8)
project(GetImageMatrix)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)


set(SOURCE_FILES main.cpp)
add_executable(GetImageMatrix ${SOURCE_FILES})
target_link_libraries(GetImageMatrix ${OpenCV_LIBS})