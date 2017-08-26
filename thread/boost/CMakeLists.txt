cmake_minimum_required(VERSION 2.8)

project(helloWorld CXX)

find_package(Boost COMPONENTS thread REQUIRED)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  add_executable(${PROJECT_NAME} helloworld.cpp)
  target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()
