cmake_minimum_required(VERSION 3.1)
project(test1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(Main main.cpp)
target_link_libraries(Main ${OpenCV_LIBS})