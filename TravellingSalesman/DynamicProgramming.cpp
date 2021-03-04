#include "DynamicProgramming.h"
#include<iostream>

using namespace std;


int size;
int visitedAll;
vector<vector<int>> savedPaths;
vector<vector<string>> shortestPath;


int DynamicProgramming::recursionTSP(int visitedCities, int currentPos, Matrix *matrix) {
    if(visitedCities == visitedAll) {
        shortestPath[visitedCities][currentPos] = to_string(currentPos);
        return matrix->getCell(currentPos, 0);
    }
    if(savedPaths[visitedCities][currentPos]!=-1){
        return savedPaths[visitedCities][currentPos];
    }

    int ans = INT_MAX;
    string currentPath = "";

    for(int city=0; city<size; city++) {
        if((visitedCities&(1<<city)) == 0) {
            int newAns = matrix->getCell(currentPos, city) + recursionTSP(visitedCities|(1<<city), city, matrix);
            if((newAns < ans)) {
                ans = newAns;
                currentPath = to_string(currentPos) + "->" + shortestPath[visitedCities|(1<<city)][city];
            }
        }
    }
    shortestPath[visitedCities][currentPos] = currentPath;
    savedPaths[visitedCities][currentPos] = ans;
    return ans;
}

void DynamicProgramming::run(Matrix* matrix) {
    size = matrix->getSize();
    visitedAll = (1<<size) - 1;
    savedPaths.reserve(1<<size);
    shortestPath.reserve(1<<size);

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

    recursionTSP(1, 0, matrix);
    cout << "DP:" << endl;
    cout << "shortest path: " << savedPaths[1][0] << endl;
    cout << shortestPath[1][0] << "->0" << endl;


    //clear
    savedPaths.clear();
    shortestPath.clear();
}