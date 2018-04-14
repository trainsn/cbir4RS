cmake_minimum_required(VERSION 2.8)

project(color_cbir)

FIND_PACKAGE(OpenCV REQUIRED)
LINK_DIRECTORIES(${PROJECT_BINARY_DIR}/lib)
# Add OpenCV headers location to your include paths
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(main "main.cpp")

# Link your application with OpenCV libraries
target_link_libraries(main ${OpenCV_LIBS})
