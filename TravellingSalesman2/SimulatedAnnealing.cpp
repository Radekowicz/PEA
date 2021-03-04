#include "SimulatedAnnealing.h"
#include <random>
#include <queue>
#include <cmath>
#include <chrono>

using namespace std;

SimulatedAnnealing::SimulatedAnnealing(Matrix *matrix, double coolingRate, int L, double time) {
    this->matrix = matrix;
    matrixSize = matrix->getSize();
    this->coolingRate = coolingRate;
    this->L = L;
    this->time = time;
}


int SimulatedAnnealing::run() {
    vector<int> bestPath = generateRandomPath();
    vector<int> neighbourPath;

    double temperature = calculateTemperature();

    double probability;
    double r;


    auto startTime =  chrono::steady_clock::now();

    //cout << "start temperature: " << temperature << endl;

    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, matrixSize-1);

    while (true) {

        for (int i = 0; i < L; i++) {
            neighbourPath = bestPath;
            swap(neighbourPath[distribution(generator)], neighbourPath[distribution(generator)]);

            int difference = calculatePathCost(neighbourPath) - calculatePathCost(bestPath);

            if (difference < 0) {
                bestPath = neighbourPath;
            }
            else {
                random_device rd;
                mt19937 g(rd());
                uniform_real_distribution<double> dist(0, 1);
                r = dist(g);
                probability = exp(-1 * difference / temperature);
                if (r < probability) {
                    bestPath = neighbourPath;
                }
            }
        }
        temperature = temperature * coolingRate;

        auto endTime = chrono::steady_clock::now();
        chrono::duration<double> elapsed_seconds = endTime-startTime;
        if( elapsed_seconds.count() >= time) {
            break;
        }
    }

    //cout << calculatePathCost(bestPath) << endl;

    return calculatePathCost(bestPath);
}

vector<int> SimulatedAnnealing::generateRandomPath() {
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

double SimulatedAnnealing::calculateTemperature() {
    vector<int> initialPath;
    vector<int> randomPath;
    double differenceSum = 0;
    int iterations = 1000;

    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, matrixSize-1);

    for (int i = 0; i < iterations; i++) {
        initialPath = generateRandomPath();
        randomPath = initialPath;

        swap(randomPath[distribution(generator)], randomPath[distribution(generator)]);

        differenceSum += fabs(calculatePathCost(randomPath) - calculatePathCost(initialPath));

    }
    double temperature = -1 * (differenceSum/iterations) / log(0.99);
    return temperature;
}

int SimulatedAnnealing::calculatePathCost(vector<int> path) {
    int sum = 0;
    for (int i = 0; i < matrixSize-1; i++) {
        int p = matrix->getCell(path[i], path[i+1]);
        sum += p;
    }
    sum += matrix ->getCell(path[matrixSize-1], path[0]);

    return sum;
}