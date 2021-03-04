#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <string>
#include <curses.h>

#include "Matrix.h"
#include "BruteForce.h"
#include "FileConverter.h"
#include "DynamicProgramming.h"
#include "BnB.h"

#include "Menu.h"

using namespace std;


void Menu::displayMenu(std::string info)
{
    cout << endl;
    cout << info << endl;
    cout << "1.Wczytaj z pliku (.txt)" << endl;
    cout << "2.Generuj losowo" << endl;
    cout << "3.Wybierz algorytm" << endl;
    cout << "0.Zakoncz program" << endl;
    cout << "Podaj opcje: ";
}

void Menu::menu() {
    do {
        displayMenu("--- MENU ---");
        cin >> opt;
        //opt = getch(); //na MacOS to nie działa dlatego uzywam std::cin
        cout << endl;
        switch (opt) {
            case '1':
                cout << "Podaj lokalizację pliku z danymi wejsciowymi: ";
                cin >> fileName;
                matrix = new Matrix(fileName);
                cout << endl;
                matrix->print();
                cout << endl;

                break;

            case '2':
                cout << "Podaj ilosc miast: ";
                cin >> n;
                matrix = new Matrix(n);
                cout << endl;
                matrix->print();
                cout << endl;

                break;

            case '3':
                if(matrix != nullptr)
                    choose();
                else
                    cout << "Pusta macierz" << endl;
                break;
        }

    } while (opt != '0');
}

void Menu::choose() {
    do {
        cout << "Wybierz algorytm rozwiazania TSP: " << endl;
        cout << "1.Brute Force" << endl;
        cout << "2.Branch & Bound" << endl;
        cout << "3.Dynamic Programming" << endl;
        cout << "0.Powrot" << endl;
        cout << "Podaj opcje: ";


        cin >> opt2;
        cout << endl;
        switch (opt2) {
            case '1':
                cout << endl;
                matrix->print();
                cout << endl;

                BruteForce::findPermutations(matrix);
                cout << endl;

                break;

            case '3':
                cout << endl;
                matrix->print();
                cout << endl;

                DynamicProgramming::run(matrix);
                cout << endl;

                break;

            case '2':
                cout << endl;
                matrix->print();
                cout << endl;

                BnB* bnb = new BnB();
                bnb->run(matrix);
                cout << endl;

                break;

        }

    } while (opt2 != '0');
}