#ifndef TRAVELLINGSALESMAN_MENU_H
#define TRAVELLINGSALESMAN_MENU_H

#include <string>
#include "Matrix.h"

using namespace std;

class Menu {
    char opt;
    char opt2;
    string fileName;
    int n;
    Matrix* matrix;

public:

    void displayMenu(std::string info);

    void menu();

    void choose();

};


#endif //TRAVELLINGSALESMAN_MENU_H
