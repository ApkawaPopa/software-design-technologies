cmake_minimum_required(VERSION 3.30)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1 main.cpp
        Patient.cpp
        Patient.h
        Assignment.cpp
        Assignment.h
        Medic.cpp
        Medic.h
        Nurse.cpp
        Nurse.h
        Doctor.cpp
        Doctor.h
        log.cpp
        log.cpp
        log.h)
