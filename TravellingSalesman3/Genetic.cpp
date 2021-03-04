#include "Genetic.h"
#include <random>
#include <queue>
#include <cmath>
#include <chrono>
#include <algorithm>


using namespace std;

Genetic::Genetic(Matrix *matrix, int populationSize, int mutationType, double mutationRate, double crossoverRate, double time, int timeRate) {
    this->matrix = matrix;
    matrixSize = matrix->getSize();
    this->populationSize = populationSize;
    this->mutationRate = mutationRate;
    this->crossoverRate = crossoverRate;
    this->time = time;
    this->numberOfMutations = 0;
    this->mutationType = mutationType;
    this->timeRate = timeRate;
}

Genetic::Genetic(Matrix *matrix, int populationSize, int mutationType, double mutationRate, double crossoverRate, double time) {
    this->matrix = matrix;
    matrixSize = matrix->getSize();
    this->populationSize = populationSize;
    this->mutationRate = mutationRate;
    this->crossoverRate = crossoverRate;
    this->time = time;
    this->numberOfMutations = 0;
    this->mutationType = mutationType;
}

int Genetic::run() {

    auto startTime =  chrono::steady_clock::now();

    generateRandomPopulation();

    //int timeCounter = timeRate;

    while(true) {

        vector<vector<int>> selectedParentsPopulation;
        vector<vector<int>> newPopulation;

        random_device rd;
        mt19937 g(rd());

        while (selectedParentsPopulation.size() < populationSize) {
            uniform_real_distribution<double> distSelection(0, populationSize-1);

            vector<int> parentA = population[distSelection(g)];
            vector<int> parentB = population[distSelection(g)];
            vector<int> winner;

            if (calculatePathCost(parentA) < calculatePathCost(parentB))
                winner = parentA;
            else
                winner = parentB;

            selectedParentsPopulation.push_back(winner);
        }

        for (int i = 0; i < populationSize - 1; i = i + 2) {

            vector<int> parentA = selectedParentsPopulation[i];
            vector<int> parentB = selectedParentsPopulation[i+1];

            uniform_real_distribution<double> distCrossover(0, matrixSize/2);
            int start = distCrossover(g);
            int end = start + matrixSize/2;


            uniform_real_distribution<double> distMutation(0, 1);
            double p = distMutation(g);
            if (p < crossoverRate) {
                vector<int> child1 = partiallyMatchedCrossover(parentA, parentB, start, end);
                vector<int> child2 = partiallyMatchedCrossover(parentB, parentA, start, end);
                if (mutationType == 1) {
                    newPopulation.push_back(swapMutate(child1));
                    newPopulation.push_back(swapMutate(child2));
                }
                else if (mutationType == 2) {
                    newPopulation.push_back(inversionMutate(child1));
                    newPopulation.push_back(inversionMutate(child2));
                }
                else {
                    break;
                }
;
            }
            else {
                newPopulation.push_back(parentA);
                newPopulation.push_back(parentB);
            }

        }
        population = newPopulation;
        calcFitness();

        auto endTime = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = endTime-startTime;

//        if ((int) elapsed_seconds.count() >= timeCounter) {
//            cout << calculatePathCost(population[0]) << endl;
//            timeCounter += timeRate;
//        }

        if( elapsed_seconds.count() >= time) {
            break;
        }
    }

    calcFitness();


    return calculatePathCost(population[0]);
}

vector<int> Genetic::swapMutate(vector<int> child) {
    random_device rd;
    mt19937 g(rd());

    uniform_real_distribution<double> dist(0, 1);
    double p = dist(g);

    if (p < mutationRate) {
        uniform_real_distribution<double> dist2(0, matrixSize-1);
        int swap1 = dist2(g);
        int swap2 = dist2(g);
        swap(child[swap1], child[swap2]);
    }

    return child;
}

vector<int> Genetic::inversionMutate(vector<int> child) {
    random_device rd;
    mt19937 g(rd());

    uniform_real_distribution<double> dist(0, 1);
    double p = dist(g);

    if (p < mutationRate) {
        numberOfMutations++;
        uniform_real_distribution<double> dist2(0, matrixSize/2 + 1);
        int swap1 = dist2(g);
        int swap2 = dist2(g);

        reverse(child.begin() + swap1, child.begin() + swap1 + swap2);

    }

    return child;
}




vector<int> Genetic::partiallyMatchedCrossover(vector<int> parentA, vector<int> parentB, int start, int end) {


    vector<int> child;
    child.resize(matrixSize); //matrix size
    fill(child.begin(), child.end(), -1);

    vector<int> subParentA(parentA.begin() + start, parentA.begin() + end + 1);

    //copy random part of parentA
    for (int i = start; i <= end; i++) {
        child[i] = parentA[i];
    }

    for (int i = start; i <= end; i++) {
        int index = findIndex(parentB, parentA[i]);
        if (findIndex(subParentA, parentB[i]) == -1) { //jeśli element nie został już skopiowany
            if (child[index] == -1) { // jeśli miejsce jest wolne
                child[index] = parentB[i];
            }
            else {
                int temp = i;

                while(true) {

                    temp = findIndex(parentB, parentA[temp]);
                    if (child[temp] == -1) {
                        child[temp] = parentB[i];
                        break;
                    }
                }
            }
        }
    }

    // uzupełnienie wolnych miejsc w child przez parentB
    for (int i = 0; i < child.size(); i++) {
        if (child[i] == -1) {
            child[i] = parentB[i];
        }
    }

    return child;
}

int Genetic::findIndex(vector<int> vector, int value) {
    for (int i = 0; i < vector.size(); i++) {
        if (vector[i] == value) return i;
    }
    return -1;
}


void Genetic::print() {
    for (int i = 0; i < populationSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            cout << population[i][j] << " ";
        }
        cout << calculatePathCost(population[i]);
        cout << endl;
    }
}

void Genetic::printVector(vector<int> vector) {
        cout << endl;
        for (int j = 0; j < vector.size(); j++) {
            cout << vector[j] << " ";
        }
        cout << endl;
}

void Genetic::calcFitness() {
    sort(population.begin(), population.end(), [this](const vector<int> & a, const vector<int> & b){ return calculatePathCost(a) < calculatePathCost(b); });
}


void Genetic::generateRandomPopulation() {
    population.clear();

    for ( int  p = 0; p < populationSize; p++) {
        vector<int> randomPath;
        randomPath.reserve(matrixSize);
        for (int i = 0; i < matrixSize; i++) {
            randomPath.push_back(i);
        }

        random_device rd;
        mt19937 g(rd());

        shuffle(randomPath.begin(), randomPath.end(), g);

        population.push_back(randomPath);
    }

}

int Genetic::calculatePathCost(vector<int> path) {
    int sum = 0;
    for (int i = 0; i < matrixSize-1; i++) {
        int p = matrix->getCell(path[i], path[i+1]);
        sum += p;
    }
    sum += matrix ->getCell(path[matrixSize-1], path[0]);

    return sum;
}