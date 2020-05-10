cmake_minimum_required(VERSION 3.15)
project(Assignment_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment_3
        infectionAnalyzer.cpp
        infectionAnalyzer.h
        main.cpp
        node.h
        tree.h
        treeImplementation.h)
