cmake_minimum_required(VERSION 3.8)
project(ghostinthecell)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(external/googletest)


include_directories(
        ${PROJECT_SOURCE_DIR}/src
)
set(SOURCE_FILES
        src/Factory.cpp
        src/Factory.h
        src/Troop.cpp
        src/Troop.h
        src/Entity.cpp
        src/Entity.h)

add_library(
        ghostinthecell
        ${SOURCE_FILES})

add_executable(
        unit_tests
        src/main.cpp
        test/FactoryTest.cpp)

target_link_libraries(
        unit_tests
        gtest_main
        ghostinthecell
)
