cmake_minimum_required(VERSION 3.8)
project(ghostinthecell)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Factory.cpp src/Factory.h src/Troop.cpp src/Troop.h src/Entity.cpp src/Entity.h)
add_executable(ghostinthecell ${SOURCE_FILES})
