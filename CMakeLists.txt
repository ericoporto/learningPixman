cmake_minimum_required(VERSION 3.16)
project(learningPixman)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
set(CMAKE_CXX_STANDARD 11)

#find_package(Pixman REQUIRED)
include(FindLocalPixman)
include_directories(libsrc/stb/)

add_executable(learningPixman main.cpp)

target_link_libraries(learningPixman PRIVATE Pixman::Pixman)



