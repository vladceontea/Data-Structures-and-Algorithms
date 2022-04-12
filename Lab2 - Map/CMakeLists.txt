cmake_minimum_required(VERSION 3.17)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab2
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        Map.cpp
        Map.h
        MapIterator.cpp
        MapIterator.h
        ShortTest.cpp
        ShortTest.h ReplaceTest.cpp ReplaceTest.h)
