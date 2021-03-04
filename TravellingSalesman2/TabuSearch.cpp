#include "TabuSearch.h"
#include <random>
#include <queue>
#include <cmath>
#include <chrono>
using namespace std;

TabuSearch::TabuSearch(Matrix *matrix, double time) {
    this->matrix = matrix;
    matrixSize = matrix->getSize();
    this->time = time;
}


int TabuSearch::run() {

    auto startTime =  chrono::steady_clock::now();

    vector<int> bestPath;
    vector<int> currentPath;
    vector<int> nextPath;

    int bestCost = INT_MAX;
    int currentCost;
    int nextCost;

    // create tabu matrix
    vector<vector<int>> tabuMatrix;
    tabuMatrix.resize(matrixSize);
    for (int i = 0; i < matrixSize; i++) {
        tabuMatrix[i].resize(matrixSize, 0);
    }

    int swap_i, swap_j;

    int iterations = 10*matrixSize;

    while(true) {
        currentPath = generateRandomPath();
        nextPath = currentPath;

        for (int iteration = 0; iteration < iterations; iteration++) {
            nextCost = INT_MAX;
            swap_i = 0;
            swap_j = 0;

            for (int i = 0; i < matrixSize; i++) {
                for (int j = i + 1; j < matrixSize; j++) {
                    swap(currentPath[i], currentPath[j]);
                    currentCost = calculatePathCost(currentPath);

                    if (currentCost < bestCost && tabuMatrix[i][j] == 0) {
                        bestPath = currentPath;
                        bestCost = currentCost;
                    }

                    if (currentCost < nextCost && tabuMatrix[i][j] < iteration) {
                        nextCost = currentCost;
                        nextPath = currentPath;
                        swap_i = i;
                        swap_j = j;
                    }
                }
            }
            currentPath = nextPath;
            tabuMatrix[swap_i][swap_j] += matrixSize; //update tabu

            for (int a = 0; a < matrixSize; a++) {
                for (int b = 0; b < matrixSize; b++) {
                    if (tabuMatrix[a][b] > 0)
                    tabuMatrix[a][b] -= 1;
                    //cout << tabuMatrix[a][b] << " ";
                }
                //cout << endl;
            }

            auto endTime = chrono::steady_clock::now();
            chrono::duration<double> elapsed_seconds = endTime-startTime;
            if(elapsed_seconds.count() >= time) {
                //cout << calculatePathCost(bestPath) << endl;
                return calculatePathCost(bestPath);
            }
        }
    }
}

vector<int> TabuSearch::generateRandomPath() {
    vector<int> randomPath;
    randomPath.reserve(matrixSize);
    for (int i = 0; i < matrixSize; i++) {
        randomPath.push_back(i);
    }

    random_device rd;
    mt19937 g(rd());

    shuffle(randomPath.begin(), randomPath.end(), g);

    return randomPath;
}



int TabuSearch::calculatePathCost(vector<int> path) {
    int sum = 0;
    for (int i = 0; i < matrixSize - 1; i++) {
        int p = matrix->getCell(path[i], path[i + 1]);
        sum += p;
    }
    sum += matrix->getCell(path[matrixSize - 1], path[0]);

    return sum;
}