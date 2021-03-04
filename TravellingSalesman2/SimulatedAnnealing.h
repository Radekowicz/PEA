#ifndef TRAVELLINGSALESMAN2_SIMULATEDANNEALING_H
#define TRAVELLINGSALESMAN2_SIMULATEDANNEALING_H

#include "Matrix.h"
#include <iostream>
#include <vector>
#include <random>
#include <queue>

class SimulatedAnnealing {

private:
    Matrix* matrix;
    int matrixSize;
    double coolingRate;
    int L;
    double time;


public:
    SimulatedAnnealing(Matrix *matrix, double coolingRate, int L, double time);
    int run();
    vector<int> generateRandomPath();
    double calculateTemperature();
    int calculatePathCost(vector<int> path);
};


#endif //TRAVELLINGSALESMAN2_SIMULATEDANNEALING_H
