cmake_minimum_required(VERSION 3.27)
project(C_plusspluss_Projekt)

set(CMAKE_CXX_STANDARD 20)

include_directories(include lib)

add_executable(C_plusspluss_Projekt src/main.cpp
        src/kasutaja.cpp
        src/treeningkava.cpp
        include/kasutaja.h
        include/treeningkava.h)
