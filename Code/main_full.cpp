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
    string types[7] = {"T","O","I","L","Z","J","S"};
    for (int count = 0; count < 7; count++) {    
    string type = types[count];
    
    cout << "Type: " << type << endl;
    stringstream filename;
    filename << type << ".txt";
    dataFile.open(filename.str().c_str());

    srand(time(0));
    
    int tikzcounter = 0;
    dataFile << "Pot, Mean, Block" << endl;
    for (double pot = -5.; pot <= 5.; pot += 0.2){
    /*
    double pot = 10.0;
    dataFile << "Block, Mean, DeltaM" << endl;
    */
/*  Initialize everything */
    int steps = 0;
    int blocks = 0;
    for (int i=0; i<SIZE*SIZE; i++){
        lattice[i] = 0;
        tetro[i] = "";
    }

/*  Do the first block without calculating the density
    One block = 1000 steps */
    for (steps = 0; steps < 1000; steps++) {
        performStep(lattice, tetro, pot, type);
    }    

/*  Continue until the density converges */
    do {
        lastMean = vecMean(vecDensity);
        vecDensity.clear();
        for (steps = 0; steps < 1000; steps++) {
            performStep(lattice, tetro, pot, type);
            vecDensity.push_back(density(lattice));
        }
        blocks++;
        /*
    //  Display some information and write to file           
        cout << blocks << " " << vecMean(vecDensity) << endl;
        dataFile << blocks << ", ";
        dataFile << vecMean(vecDensity) << ", ";
        dataFile << abs(vecMean(vecDensity)/lastMean);
        dataFile << endl;
        */    
        } while (abs(vecMean(vecDensity)/lastMean - 1) > 0.01);
        
//    Start data collection
        vecDensity.clear();
        for (steps = 0; steps < 1000; steps++) {
            performStep(lattice, tetro, pot, type);
            vecDensity.push_back(density(lattice));
        }
        dataFile << pot << ", " << vecMean(vecDensity) << ", ";
        dataFile << blocks << endl;
        cout << pot << ":\t" << vecMean(vecDensity) << endl;
        if (tikzcounter == 5 or tikzcounter == 25 or tikzcounter == 45) {
                stringstream picname;
                picname << type << "_" << pot << ".tex";
                printToFile(picname.str(),lattice,tetro);
                cout << "Picture saved as " << picname.str() << endl;
        }
        tikzcounter++;
    }
    
    dataFile.close();
        
    }
    return 0;
}
