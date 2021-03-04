#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <string>
#include <curses.h>

#include "Matrix.h"

#include "Menu.h"
#include "Genetic.h"

using namespace std;


void Menu::displayMenu(std::string info)
{
    cout << endl;
    cout << info << endl;
    cout << "1.Wczytaj z pliku (.txt)" << endl;
    cout << "2.Wybierz kryterium stopu (" << time << "s)" <<  endl;
    cout << "3.Wybierz współczynnik mutacji (" << mutationRate << ")" << endl;
    cout << "4.Wybierz współczynnik krzyżowania (" << crossoverRate << ")" << endl;
    cout << "5.Wybierz wielkość populacji (" << populationSize << ")" << endl;
    cout << "6.Uruchom algorytm genetyczny" << endl;
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
                cout << "Podaj czas wykonywania algorytmu w sekundach: ";
                cin >> time;
                if (time <= 0) {
                    time = -1;
                    cout << "Czas trwania algorytmu musi być większy od 0" << endl;
                }
                cout << endl;

                break;

            case '3':
                cout << "Podaj współczynnik mutacji (domyślnie 0.01): ";
                cin >> mutationRate;
                if (mutationRate <= 0 || mutationRate > 1) {
                    mutationRate = 0.01;
                    cout << "Współczynnik mutacji zawierać się w przedziale od 0 do 1" << endl;
                }
                cout << endl;

                break;

            case '4':
                cout << "Podaj współczynnik krzyżowania (domyślnie 0.8): ";
                cin >> crossoverRate;
                if (crossoverRate <= 0 || crossoverRate > 1) {
                    crossoverRate = 0.8;
                    cout << "Współczynnik krzyżowania zawierać się w przedziale od 0 do 1" << endl;
                }
                cout << endl;

                break;

            case '5':
                cout << "Podaj wielkość populacji (domyślnie 200): ";
                cin >> populationSize;
                if (populationSize <= 0 ) {
                    populationSize = 200;
                    cout << "Wielkośc populacji musi być większa od 0" << endl;
                }
                cout << endl;

                break;


            case '6':
                if(time == -1) {
                    cout << "Podaj czas wykonywania algorytmu" << endl;
                    break;
                }

                if(matrix != nullptr) {
                    cout << endl;
                    matrix->print();
                    cout << endl;

                    Genetic* genetic = new Genetic(matrix, populationSize, 1, mutationRate, crossoverRate, time);
                    cout << "Koszt najkrótszej znalezionej ścieżki: " << genetic->run() <<  endl;
                    cout << "Czas: " << time << "s" << endl;

                    cout << endl;
                    break;
                }
                else
                    cout << "Pusta macierz" << endl;
                break;
        }

    } while (opt != '0');
}