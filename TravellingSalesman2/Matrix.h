#ifndef TRAVELLINGSALESMAN2_MATRIX_H
#define TRAVELLINGSALESMAN2_MATRIX_H

#include <iostream>
#include <vector>

using namespace std;

class Matrix {

private:
    vector<vector<int>> matrix;

public:
    Matrix();
    Matrix(int size);
    Matrix(Matrix* matrix);
    Matrix(string filePath);
    void loadMatrix(vector<vector<int>> matrix);
    void setCell(int x, int y, int value);
    int getCell(int x, int y);
    void print();
    int getSize();
    void pushBack(vector<int> row);
    void copyMatrix(Matrix* matrix);
    void setDiagonalToInf();

};


#endif //TRAVELLINGSALESMAN2_MATRIX_H
