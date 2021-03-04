#ifndef TRAVELLINGSALESMAN2_MENU_H
#define TRAVELLINGSALESMAN2_MENU_H


#include <string>
#include "Matrix.h"

using namespace std;

class Menu {
    char opt;
    int opt2;
    string fileName;
    int n;
    int time = -1;
    Matrix* matrix;

public:

    void displayMenu(std::string info);

    void menu();

    void choose();
};


#endif //TRAVELLINGSALESMAN2_MENU_H
