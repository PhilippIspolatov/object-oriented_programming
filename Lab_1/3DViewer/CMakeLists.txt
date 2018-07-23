cmake_minimum_required(VERSION 3.9)

project(untitled)
add_executable(untitled main.cpp cmake-build-debug/cube.txt)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries( untitled ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )