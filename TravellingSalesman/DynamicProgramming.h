#ifndef TRAVELLINGSALESMAN_DYNAMICPROGRAMMING_H
#define TRAVELLINGSALESMAN_DYNAMICPROGRAMMING_H

#include "Matrix.h"


class DynamicProgramming {

/*    static int size;
    static int visitedAll;
    static vector<vector<int>> savedPaths;
    static vector<vector<string>> shortestPath;*/


public:


    static int recursionTSP(int visitedCities, int currentPos, Matrix *matrix);
    static void run(Matrix* matrix);


    };


#endif //TRAVELLINGSALESMAN_DYNAMICPROGRAMMING_H
