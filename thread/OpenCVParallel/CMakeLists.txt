cmake_minimum_required(VERSION 2.8)

project(sample CXX)

set(CMAKE_BUILD_TYPE Release)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(OpenMP)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/sample.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
