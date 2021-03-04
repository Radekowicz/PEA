#include <iostream>
#include <vector>
#include <chrono>
#include <random>

#include "Matrix.h"
#include "BruteForce.h"
#include "FileConverter.h"
#include "DynamicProgramming.h"
#include "BnB.h"
#include "Menu.h"

using namespace std;

void test(int n) {
    int timeSum = 0;

    for (int i = 0; i < 100; i++) {

        Matrix* matrix = new Matrix(n);
        //matrix->print();
        //BnB* bnb = new BnB();

        auto start = chrono::high_resolution_clock::now();


        //BruteForce::findPermutations(matrix);
        //bnb->run(matrix);
        //DynamicProgramming::run(matrix);


        auto stop = chrono::high_resolution_clock::now();

        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        timeSum += duration.count();
    }

    cout << "average time to solve TSP for " << n << " cities is: " << (timeSum/10) << "μs" << endl;
}

int main() {

    //FileConverter::convert();

    Menu menu = Menu();
    menu.menu();


    return 0;
}