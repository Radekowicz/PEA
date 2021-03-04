#include "BruteForce.h"


int BruteForce::calculatePath(int cities[], int size, Matrix* matrix) {
    int sum = 0;
    for (int i = 0; i < size-1; i++) {
        int p = matrix->getCell(cities[i], cities[i+1]);
        sum += p;
    }
    sum += matrix ->getCell(cities[size-1], cities[0]);

    return sum;
}

void BruteForce::findPermutations(Matrix* matrix) {

    int size = matrix->getSize();

    int cities[size];
    for (int i = 0; i < matrix->getSize(); i++) {
        cities[i] = i;
    }

    int shortestPath = INT_MAX;

    int shortestPathCities[size];

    sort(cities, cities + size);

    do {
        int path = calculatePath(cities, size, matrix);
        if (path < shortestPath) {
            shortestPath = path;

            for (int i = 0; i < size; i++) {
                shortestPathCities[i] = cities[i];
            }
        }

    } while (next_permutation(cities, cities + size));

    cout << "BF:" << endl;
    cout << "shortest path: " << shortestPath << endl;

    for (int i = 0; i < size; i++) {
        cout << shortestPathCities[i] << "->";
    }
    cout << shortestPathCities[0] << endl;

}
