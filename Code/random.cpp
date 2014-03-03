#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

#include "defs.h"
#include "fit.h"

double randomUni() {
/* Return a uniform random number in the unit interval */
    return rand() / double(RAND_MAX);
}


int randomStep() {
/* Return a random integer between 1 and 17 */
    return rand() % 17 + 1;
}

int randomDirection() {
/* Return a random integer between 1 and 4 */
    return rand() % 4 + 1;
}

int randomPoint() {
/* Return a random integer between 0 and SIZE*SIZE */
    return rand() % (SIZE*SIZE);
}

int randomFree(int lattice[]) {
/* Return a random free lattice point, chosen uniformly at random */
    int test = randomPoint();
    if (lattice[test] == 0) return test;
    else return randomFree(lattice);
}

int randomTetro(string tetro[], string type) {
/* Return the position of a random Tetromino of a given type. 
    If the lattice is empty return -1 */
    int num_tetro = count(tetro, type);
    int rand_tetro = 0;
    if (num_tetro == 0) return -1;
    else {
        rand_tetro = rand() % num_tetro + 1;
        int count_tetro = 0;
        for (int i=0; i<SIZE*SIZE; i++) {
            if (tetro[i] != "") count_tetro++;
            if (count_tetro == rand_tetro) {
               return i;
            }
        }
    }
    return -1;
}
    
