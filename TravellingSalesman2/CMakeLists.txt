cmake_minimum_required(VERSION 3.12)
project(TravellingSalesman2)

set(CMAKE_CXX_STANDARD 14)

add_executable(TravellingSalesman2 main.cpp Matrix.cpp Matrix.h FileConverter.cpp FileConverter.h SimulatedAnnealing.cpp SimulatedAnnealing.h TabuSearch.cpp TabuSearch.h Menu.cpp Menu.h Genetic.cpp Genetic.h)