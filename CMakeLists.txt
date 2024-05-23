cmake_minimum_required(VERSION 3.27)
project(C_plusspluss_Projekt)

set(CMAKE_CXX_STANDARD 20)

include_directories(include lib)

add_executable(C_plusspluss_Projekt src/main.cpp
        src/kasutaja.cpp
        include/kasutaja.h
        include/jsonHaldaja.h
        src/jsonHaldaja.cpp
        include/trenniGeneraator.h
        src/trenniGeneraator.cpp
        include/infoKuvaja.h
        src/infoKuvaja.cpp)
