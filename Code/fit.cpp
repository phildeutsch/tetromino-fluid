#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>

#include "defs.h"

using namespace std;

int move_one(int position, int x, int y){
/*  Return the position when translated one step into direction x or y */
    int newpos;
    if (x == 1 && y == 0){
        newpos = position + 1;
        if (newpos%SIZE == 0) newpos = newpos - SIZE;
        return newpos;
    }
    else if (x == -1 && y == 0){
        newpos = position - 1;
        if (newpos%SIZE == SIZE-1 || newpos < 0) newpos = newpos + SIZE;
        return newpos;
    }
    else if (x == 0 && y == 1){
        newpos = position - SIZE;
        if (newpos < 0) newpos = newpos + SIZE*SIZE;
        return newpos;
    }
    else if (x == 0 && y == -1){
        newpos = position + SIZE;
        if (newpos > SIZE*SIZE-1) newpos = newpos - SIZE*SIZE;
        return newpos;
    }
    return -1;
}

vector<int> points(int position, int orientation, string type){
/*  Return the points on the lattice occupied by a tetromino of a given type
    at a given position */
    vector<int> output;
    stringstream type_or;
    type_or << type << orientation;
    
    int a, b, c;
    
    if (type_or.str() == "T1") {
        a = move_one(position, 1, 0);
        b = move_one(position, -1, 0);
        c = move_one(position, 0, 1);
    }
    else if  (type_or.str() == "T2") {
        a = move_one(position, 1, 0);
        b = move_one(position, 0, 1);
        c = move_one(position, 0, -1);
    }
    else if  (type_or.str() == "T3") {
        a = move_one(position, 1, 0);
        b = move_one(position, -1, 0);
        c = move_one(position, 0, -1);
    }
    else if  (type_or.str() == "T4") {
        a = move_one(position, 0, 1);
        b = move_one(position, 0, -1);
        c = move_one(position, -1, 0);
    }
    else if  (type_or.str() == "O1") {
        a = move_one(position, 0, 1);
        b = move_one(position, 1, 0);
        c = move_one(move_one(position,0,1), 1, 0);    
    }
    else if  (type_or.str() == "O2") {
        a = move_one(position, 0, -1);
        b = move_one(position, 1, 0);
        c = move_one(move_one(position,0,-1), 1, 0);    
    }
    else if  (type_or.str() == "O3") {
        a = move_one(position, 0, -1);
        b = move_one(position, -1, 0);
        c = move_one(move_one(position,0,-1), -1, 0);    
    }
    else if  (type_or.str() == "O4") {
        a = move_one(position, 0, 1);
        b = move_one(position, -1, 0);
        c = move_one(move_one(position,0,1), -1, 0);    
    }
    else if  (type_or.str() == "L1") {
        a = move_one(position, 0, 1);
        b = move_one(position, 0, -1);
        c = move_one(move_one(position,0,-1), 1, 0);    
    }
    else if  (type_or.str() == "L2") {
        a = move_one(position, 1, 0);
        b = move_one(position, -1, 0);
        c = move_one(move_one(position,0,-1), -1, 0);    
    }
    else if  (type_or.str() == "L3") {
        a = move_one(position, 0, 1);
        b = move_one(position, 0, -1);
        c = move_one(move_one(position,0,1), -1, 0);    
    }
    else if  (type_or.str() == "L4") {
        a = move_one(position, 1, 0);
        b = move_one(position, -1, 0);
        c = move_one(move_one(position,0,1), 1, 0);    
    }
    else if  (type_or.str() == "I1") {
        a = move_one(position, 1, 0);
        b = move_one(position, -1, 0);
        c = move_one(move_one(position,1,0), 1, 0);    
    }
    else if  (type_or.str() == "I2") {
        a = move_one(position, 0, -1);
        b = move_one(position, 0, 1);
        c = move_one(move_one(position,0,-1), 0, -1);    
    }
    else if  (type_or.str() == "I3") {
        a = move_one(position, -1, 0);
        b = move_one(position, 1, 0);
        c = move_one(move_one(position,-1,0), -1, 0);    
    }
    else if  (type_or.str() == "I4") {
        a = move_one(position, 0, 1);
        b = move_one(position, 0, -1);
        c = move_one(move_one(position,0,1), 0, 1);    
    }
    else if  (type_or.str() == "S1") {
        a = move_one(position, 0, 1);
        b = move_one(position, -1, 0);
        c = move_one(move_one(position,0,1), 1, 0);    
    }
    else if  (type_or.str() == "S2") {
        a = move_one(position, 0, 1);
        b = move_one(position, 1, 0);
        c = move_one(move_one(position,0,-1), 1, 0);    
    }
    else if  (type_or.str() == "S3") {
        a = move_one(position, 1, 0);
        b = move_one(position, 0, -1);
        c = move_one(move_one(position,0,-1), -1, 0);    
    }
    else if  (type_or.str() == "S4") {
        a = move_one(position, -1, 0);
        b = move_one(position, 0, -1);
        c = move_one(move_one(position,0,1), -1, 0);    
    }
    else if  (type_or.str() == "Z1") {
        a = move_one(position, 1, 0);
        b = move_one(position, 0, 1);
        c = move_one(move_one(position,0,1), -1, 0);    
    }
    else if  (type_or.str() == "Z2") {
        a = move_one(position, 1, 0);
        b = move_one(position, 0, -1);
        c = move_one(move_one(position,0,1), 1, 0);    
    }
    else if  (type_or.str() == "Z3") {
        a = move_one(position, -1, 0);
        b = move_one(position, 0, -1);
        c = move_one(move_one(position,0,-1), 1, 0);    
    }
    else if  (type_or.str() == "Z4") {
        a = move_one(position, -1, 0);
        b = move_one(position, 0, 1);
        c = move_one(move_one(position,-1,0), 0, -1);    
    }
    else if  (type_or.str() == "J1") {
        a = move_one(position, 0, 1);
        b = move_one(position, 0, -1);
        c = move_one(move_one(position,0,-1), -1, 0);    
    }
    else if  (type_or.str() == "J2") {
        a = move_one(position, 1, 0);
        b = move_one(position, -1, 0);
        c = move_one(move_one(position,0,1), -1, 0);    
    }
    else if  (type_or.str() == "J3") {
        a = move_one(position, 0, 1);
        b = move_one(position, 0, -1);
        c = move_one(move_one(position,0,1), 1, 0);    
    }
    else if  (type_or.str() == "J4") {
        a = move_one(position, 1, 0);
        b = move_one(position, -1, 0);
        c = move_one(move_one(position,0,-1), 1, 0);    
    }
    
    output.push_back(position);
    output.push_back(a);
    output.push_back(b);
    output.push_back(c);       
    return output;
}

int checkFit(int lattice[], int position, int orientation, string type){
/*  Return 0 if the lattice has space for a tetromino of a certain type
    at given position and orientation otherwise return 1 */
    int sum = 0;
    vector<int> vec_points = points(position, orientation, type);
    for(int i=0; i<4; i++){
        sum += lattice[vec_points[i]];
    }
    if (sum == 0) return 0;
    else return 1;
}

double density(int lattice[]){
/*  Calculate the density of the tetrominoes in the lattice */
    double sum = 0.;
    for (int i=0;i<SIZE*SIZE;i++){
        if (lattice[i] != 0) sum += 1.;
    }
    return sum/(SIZE*SIZE);
}

int freePoints(int lattice[]) {
/*  Calculate the number of free points in the lattice */
    int sum = 0;
    for (int i=0; i<SIZE*SIZE; i++) {
        if (lattice[i] == 0) sum +=1;
    }
    return sum;
}

int count(string tetro[], string type) {
/*  Count the number of tetrominoes of a given type in the lattice */
    int sum = 0;
    for (int i=0; i<SIZE*SIZE; i++) {
        if (tetro[i] == type) sum += 1;
    }
    return sum;
}

