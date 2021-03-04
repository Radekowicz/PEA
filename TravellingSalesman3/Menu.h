#ifndef TRAVELLINGSALESMAN3_MENU_H
#define TRAVELLINGSALESMAN3_MENU_H


#include <string>
#include "Matrix.h"

using namespace std;

class Menu {
    char opt;
    string fileName;
    int time = -1;
    Matrix* matrix;
    double mutationRate = 0.01;
    double crossoverRate = 0.8;
    int populationSize = 200;

public:

    void displayMenu(std::string info);

    void menu();

};


#endif //TRAVELLINGSALESMAN3_MENU_H
