cmake_minimum_required(VERSION 3.16)
project(learningPixman)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
set(CMAKE_CXX_STANDARD 11)

add_executable(learningPixman main.cpp bmp.cpp bmp.h)

include_directories(libsrc/stb/)

set(USE_INCLUDED_PIXMAN OFF)

if(USE_INCLUDED_PIXMAN)
    include(FindLocalPixman)
    target_link_libraries(learningPixman PRIVATE Pixman::Pixman)
else()
    find_package(Pixman REQUIRED)
    if(PIXMAN_FOUND)
        include_directories(${PIXMAN_INCLUDE_DIRS})
        target_link_libraries(learningPixman ${PIXMAN_LIBRARIES})
    endif(PIXMAN_FOUND)
endif(USE_INCLUDED_PIXMAN)

file(COPY data/tiny_blue_cup.png DESTINATION "${CMAKE_BINARY_DIR}")

