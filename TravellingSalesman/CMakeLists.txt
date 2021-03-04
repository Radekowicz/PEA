cmake_minimum_required(VERSION 3.12)
project(TravellingSalesman)

set(CMAKE_CXX_STANDARD 14)

add_executable(TravellingSalesman main.cpp Matrix.cpp Matrix.h BruteForce.cpp BruteForce.h FileConverter.cpp FileConverter.h DynamicProgramming.cpp DynamicProgramming.h BnB.cpp BnB.h Menu.cpp Menu.h)