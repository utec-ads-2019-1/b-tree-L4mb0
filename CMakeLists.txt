cmake_minimum_required(VERSION 3.14)
project(b_tree_L4mb0)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(b_tree_L4mb0
        btree.h
        main.cpp
        node.h)
