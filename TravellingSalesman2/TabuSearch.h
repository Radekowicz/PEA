#ifndef TRAVELLINGSALESMAN2_TABUSEARCH_H
#define TRAVELLINGSALESMAN2_TABUSEARCH_H

#include "Matrix.h"
#include <iostream>
#include <vector>
#include <random>
#include <queue>

class TabuSearch {
private:
    Matrix* matrix;
    int matrixSize;
    double time;

public:
    TabuSearch(Matrix* matrix, double time);
    int run();
    vector<int> generateRandomPath();
    int calculatePathCost(vector<int> path);
};


#endif //TRAVELLINGSALESMAN2_TABUSEARCH_H
