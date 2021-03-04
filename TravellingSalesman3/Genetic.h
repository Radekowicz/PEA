#ifndef TRAVELLINGSALESMAN3_GENETIC_H
#define TRAVELLINGSALESMAN3_GENETIC_H

#include "Matrix.h"
#include <iostream>
#include <vector>
#include <random>
#include <queue>

class Genetic {

private:
    Matrix* matrix;
    int matrixSize;
    vector<vector<int>> population;
    int populationSize;
    double mutationRate;
    double crossoverRate;
    double time;
    int numberOfMutations;
    int mutationType;
    int timeRate;


public:
    Genetic(Matrix *matrix, int populationSize, int mutationType, double mutationRate, double crossoverRate, double time, int timeRate);
    Genetic(Matrix *matrix, int populationSize, int mutationType, double mutationRate, double crossoverRate, double time);
    int run();
    void calcFitness();
    void generateRandomPopulation();
    int calculatePathCost(vector<int> path);
    void print();
    vector<int> partiallyMatchedCrossover(vector<int> parentA, vector<int> parentB, int start, int end);
    void printVector(vector<int> vector);
    int findIndex(vector<int> vector, int value);
    vector<int> swapMutate(vector<int> child);
    vector<int> inversionMutate(vector<int> child);

    };


#endif //TRAVELLINGSALESMAN3_GENETIC_H
