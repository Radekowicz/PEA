#ifndef TRAVELLINGSALESMAN_FILECONVERTER_H
#define TRAVELLINGSALESMAN_FILECONVERTER_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class FileConverter {
private:
    static void error_exit(const string &msg);
    static int header_get_size(ifstream &file);
    static int value_digits(int val);
public:
    static int convert();

};


#endif //TRAVELLINGSALESMAN_FILECONVERTER_H
