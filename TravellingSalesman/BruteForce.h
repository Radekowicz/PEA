#ifndef TRAVELLINGSALESMAN_BRUTEFORCE_H
#define TRAVELLINGSALESMAN_BRUTEFORCE_H

#include "Matrix.h"

class BruteForce {


private:
    static int calculatePath(int cities[], int size, Matrix* matrix);

        public:
    static void findPermutations(Matrix* matrix);

    };


#endif //TRAVELLINGSALESMAN_BRUTEFORCE_H
