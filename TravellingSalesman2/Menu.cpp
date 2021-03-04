#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <string>
#include <curses.h>

#include "Matrix.h"

#include "Menu.h"
#include "SimulatedAnnealing.h"
#include "TabuSearch.h"

using namespace std;


void Menu::displayMenu(std::string info)
{
    cout << endl;
    cout << info << endl;
    cout << "1.Wczytaj z pliku (.txt)" << endl;
    cout << "2.Generuj losowo" << endl;
    cout << "3.Wybierz kryterium stopu" << endl;
    cout << "4.Wybierz algorytm" << endl;
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
                cout << "Podaj czas wykonywania algorytmu w sekundach: ";
                cin >> time;
                if (time <= 0) {
                    time = -1;
                    cout << "Czas trwania algorytmu musi być większy od 0" << endl;
                }
                cout << endl;

                break;

            case '4':
                if(time == -1) {
                    cout << "Podaj czas wykonywania algorytmu" << endl;
                    break;
                }

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
        cout << "1.Simulated Annealing" << endl;
        cout << "2.Tabu Search" << endl;
        cout << "0.Powrot" << endl;
        cout << "Podaj opcje: ";


        cin >> opt2;
        cout << endl;
        switch (opt2) {
            case 1: {
                cout << endl;
                matrix->print();
                cout << endl;

                SimulatedAnnealing* SA = new SimulatedAnnealing(matrix, 0.99, 10, time);
                cout << "Simulated Annealing" << endl;
                cout << "Koszt najkrótszej znalezionej ścieżki: " << SA->run() <<  endl;
                cout << "Czas: " << time << "s" << endl;

                cout << endl;
                break;
            }

            case 2: {
                cout << endl;
                matrix->print();
                cout << endl;

                TabuSearch* TS = new TabuSearch(matrix, time);
                cout << "Tabu Search" << endl;
                cout << "Koszt najkrótszej znalezionej ścieżki: " << TS->run() << endl;
                cout << "Czas: " << time << "s" << endl;

                cout << endl;
                break;
            }
        }

    } while (opt2 != 0);
}