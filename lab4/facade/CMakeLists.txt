cmake_minimum_required(VERSION 3.30)
project(lab4-facade)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab4-facade main.cpp
        TravelFacade.cpp
        TravelFacade.h)