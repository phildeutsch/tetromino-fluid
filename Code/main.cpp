#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>

using namespace std;

#include "defs.h"
#include "fit.h"
#include "random.h"
#include "moves.h"
#include "print.h"
#include "vec.h"

int main(){
    int lattice[SIZE*SIZE];
    string tetro[SIZE*SIZE];
    vector<double> vecDensity;
    double lastMean;
    ofstream dataFile;

/*  Possible tetromino types: T, O, I, L, Z, J, S */    
    string type = "I";
    dataFile.open("tetromino.txt");

    srand(time(0));

    double pot = 10.0;
    dataFile << "Block, Mean, DeltaM" << endl;
    
/*  Initialize everything */
    int steps = 0;
    int blocks = 0;
    for (int i=0; i<SIZE*SIZE; i++){
        lattice[i] = 0;
        tetro[i] = "";
    }

/*  Do the first 3000 steps no matter what */
    vecDensity.clear();
    for (steps = 0; steps < 3000; steps++) {
        performStep(lattice, tetro, pot, type);
        vecDensity.push_back(density(lattice));
    }    

/*  Continue until the density converges */
    do {
        lastMean = vecMean(vecDensity);
        vecDensity.clear();
        for (steps = 0; steps < 3000; steps++) {
            performStep(lattice, tetro, pot, type);
            vecDensity.push_back(density(lattice));
        }
        blocks++;
    //  Display some information and write to file           
        cout << blocks << " " << vecMean(vecDensity) << endl;
        dataFile << blocks << ", ";
        dataFile << vecMean(vecDensity) << ", ";
        dataFile << abs(vecMean(vecDensity)/lastMean);
        dataFile << endl;
            
        } while (log(abs(vecMean(vecDensity)/lastMean)) > 0.001);

    dataFile.close();
    
/*  Print lattice and tetrominos in the terminal and write to file */    
    cout << endl;
    printLattice(lattice);
    printTetros(tetro);
    printToFile("tetromino.tex",lattice,tetro);

    cout << "Final density: " << vecMean(vecDensity) << endl;

    return 0;
}
