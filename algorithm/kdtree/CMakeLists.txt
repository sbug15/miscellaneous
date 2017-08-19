cmake_minimum_required(VERSION 2.8)
project(knn CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenCV REQUIRED)
include_directories(${OpenCv_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/testOpenCV.cpp)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})