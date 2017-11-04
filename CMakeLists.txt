cmake_minimum_required(VERSION 3.0)
project(ghostinthecell)

set (CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")

add_subdirectory(external/googletest)


include_directories(
        ${PROJECT_SOURCE_DIR}/src
)
set(SOURCE_FILES
        src/Factory.cpp src/Factory.h
        src/Troop.cpp src/Troop.h
        src/Entity.cpp src/Entity.h
        src/Parser.cpp src/Parser.h
        src/GameState.cpp src/GameState.h
        src/Globals.cpp src/Globals.h src/Writer.cpp src/Writer.h src/Action.cpp src/Action.h src/Utils.cpp src/Utils.h src/Evaluation.cpp src/Evaluation.h src/graph.h src/graph.cpp src/Bomb.cpp src/Bomb.h)

add_library(
        ghostinthecell
        ${SOURCE_FILES})

add_executable(
        unit_tests
        test/FactoryTest.cpp test/ParserTest.cpp test/GameStateTest.cpp test/UtilsTest.cpp test/main.cpp test/WriterTest.cpp test/GraphTest.cpp)

target_link_libraries(
        unit_tests
        gtest_main
        ghostinthecell
)
