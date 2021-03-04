#include "FileConverter.h"
#include "Matrix.h"
#include "SimulatedAnnealing.h"
#include "TabuSearch.h"
#include "Menu.h"

#include <iostream>
#include <vector>

void test(int time) {
    int result = 0;
    int iterations = 5;

    Matrix* matrix = new Matrix("/Users/radoslawlodzinski/CLionProjects/TravellingSalesman2/convertedTSPFiles/tsp_17.txt");
    //SimulatedAnnealing* SM = new SimulatedAnnealing(matrix, 0.999, 10, time);
    TabuSearch* TS = new TabuSearch(matrix, time);

    for (int i = 0; i < iterations; i++) {

            //result += SM->run();
            result += TS->run();
    }

    cout << result/iterations << endl;
 }

int main() {

        Menu menu = Menu();
        menu.menu();

    //    Matrix* matrix = new Matrix("/Users/radoslawlodzinski/CLionProjects/TravellingSalesman2/convertedTSPFiles/tsp_56.txt");
    //    TabuSearch* TS = new TabuSearch(matrix, 5);
    //    cout << TS->run() << endl;

    //FileConverter::convert();

    return 0;
}