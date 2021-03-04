#include "Matrix.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <random>


using namespace std;

Matrix::Matrix(){
}


Matrix::Matrix(int size) {
    matrix.reserve(size);

    random_device rd;
    mt19937 mt(rd());
    uniform_real_distribution<double> dist(1, 100);

    for (int i = 0; i < size; i++) {
        vector<int> temp;
        temp.reserve(size);
        for (int j = 0; j < size; j++) {
            temp.push_back((int)dist(mt));
        }
        temp[i] = -1;
        this->matrix.push_back(temp);
    }
}


Matrix::Matrix(Matrix *matrix) {
    this->matrix = matrix->matrix;
}


Matrix::Matrix(string filePath) {
    fstream file;
    file.open(filePath);

    if (file.is_open()) {

        string line;

        getline(file, line); // taking first line
        int size = stoi(line);

        matrix.reserve(size); // setting size of matrix

        while (getline(file, line)) {
            istringstream iss(line.c_str());
            string item;

            vector<int> row;
            row.reserve(size); // setting size of row

            for(string item; iss >> item; ) {
                row.push_back(stoi(item));
            }
            matrix.push_back(row);
        }
        file.close();

        setDiagonalToInf();
    }
    else {
        exit(EXIT_FAILURE);
    }
}


void Matrix::setCell(int x, int y, int value) {
    matrix[x][y] = value;
}


int Matrix::getCell(int x, int y) {
    return matrix[x][y];
}


void Matrix::print() {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            printf("%4d", matrix[i][j]);
        }
        cout << endl;
    }
}


int Matrix::getSize() {
    return matrix.size();
}


void Matrix::copyMatrix(Matrix* oldMatrix) {
    this->matrix = oldMatrix->matrix;
}


void Matrix::loadMatrix(vector<vector<int>> matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        vector<int> temp;
        for (int j = 0; j < matrix[i].size(); j++) {
            temp.push_back(matrix[i][j]);
        }
        this->matrix.push_back(temp);
    }
}

void Matrix::setDiagonalToInf() {
    for (int i = 0; i < matrix.size(); i++) {
        matrix[i][i] = -1;
    }
}


