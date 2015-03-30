cmake_minimum_required(VERSION 2.8)
project(glut_teapot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp)
add_executable(glut_teapot ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

target_link_libraries(glut_teapot ${OPENGL_LIBRARIES})
target_link_libraries(glut_teapot ${GLUT_LIBRARY})
