set(PIXMAN_BUILD_STATIC ON)
set(PIXMAN_BUILD_SHARED OFF)
add_subdirectory("${CMAKE_SOURCE_DIR}/libsrc/pixman")

add_library(pixman-interface INTERFACE)
target_link_libraries(pixman-interface INTERFACE pixman-1_static)

add_library(Pixman::Pixman  ALIAS pixman-interface)
target_include_directories(pixman-interface INTERFACE
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_BINARY_DIR}/libsrc"
        "${PROJECT_BINARY_DIR}/libsrc/pixman/pixman"
        "${PROJECT_SOURCE_DIR}/libsrc/pixman/pixman"
        )