#include "BnB.h"
#include<iostream>
#include<algorithm>

using namespace std;


BnB::BnB() {
}

int BnB::calcLower(int visitedCities, int currentPos, Matrix *matrix, int currentPathLen) {

    int lower = 0;

    for(int city=0; city<size; city++) {
        if((((visitedCities & (1<<city)) == 0))) { //jeśli miasto jest nieodwiedzone
            int min = INT_MAX;
            for (int i = 0; i < size; i++) {
                if (matrix->getCell(i, city) < min && matrix->getCell(i, city) != -1) min = matrix->getCell(i, city);
            }
            lower += min;
        }
    }
    return lower;
}



int BnB::recursionTSP(int visitedCities, int currentPos, Matrix *matrix, int currentPathLen) {
    if(visitedCities == visitedAll) {
        shortestPath[visitedCities][currentPos] = to_string(currentPos);
        return matrix->getCell(currentPos, 0);
    }

    int lower = calcLower(visitedCities, currentPos, matrix, currentPathLen);

    if(currentPathLen + lower >= upper) {
        return 999999;
    }

    int ans = INT_MAX;
    string currentPath = "";

    for(int city=0; city<size; city++) {
        if((((visitedCities & (1<<city)) == 0))) {
            int newAns = matrix->getCell(currentPos, city) + recursionTSP(visitedCities | (1<<city), city, matrix, currentPathLen + matrix->getCell(currentPos, city));
            if((newAns < ans)) {
                ans = newAns;
                currentPath = to_string(currentPos) + "->" + shortestPath[visitedCities | (1<<city)][city];
            }
        }
    }
    shortestPath[visitedCities][currentPos] = currentPath;
    savedPaths[visitedCities][currentPos] = ans;
    if(currentPathLen + ans < upper) upper = currentPathLen + ans;
    //cout << upper << endl;

    return ans;
}

void BnB::run(Matrix* matrix) {
    size = matrix->getSize();
    visitedAll = (1<<size) - 1;
    savedPaths.reserve(1<<size);
    shortestPath.reserve(1<<size);
    upper = INT_MAX;

    for(int i=0;i<(1<<size);i++){
        vector<int> row;
        for(int j=0;j<size;j++){
            row.push_back(-1);
        }
        savedPaths.push_back(row);
    }

    for(int i=0;i<(1<<size);i++){
        vector<string> row;
        for(int j=0;j<size;j++){
            row.emplace_back("");
        }
        shortestPath.push_back(row);
    }

    recursionTSP(1, 0, matrix, 0);
    cout << "BnB:" << endl;
    cout << "shortest path: " << savedPaths[1][0] << endl;
    cout << shortestPath[1][0] << "->0" << endl;


    //clear
    savedPaths.clear();
    shortestPath.clear();
}
