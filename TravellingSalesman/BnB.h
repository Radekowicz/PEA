#ifndef TRAVELLINGSALESMAN_BNB_H
#define TRAVELLINGSALESMAN_BNB_H


#include "Matrix.h"

class BnB {

private:
    int size;
    int visitedAll;
    vector<vector<int>> savedPaths;
    vector<vector<string>> shortestPath;
    int upper;

public:
    BnB();
    int recursionTSP(int visitedCities, int currentPos, Matrix *matrix, int currentPathLen);
    void run(Matrix* matrix);
    int calcLower(int visitedCities, int currentPos, Matrix *matrix, int currentPathLen);
    };


#endif //TRAVELLINGSALESMAN_BNB_H
