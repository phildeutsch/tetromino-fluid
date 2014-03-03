#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

#include "defs.h"
#include "fit.h"
#include "random.h"

int insert_tetro(int lattice[], string tetro[], int position, 
    int orientation, string type){
/*  Insert a piece at the given position and orientation */
	if(checkFit(lattice, position, orientation, type)==1) return 1;
	else {
	    vector<int> vec_points = points(position, orientation, type);
	    lattice[position] = orientation;
	    for(int i=1; i<4; i++){
	        lattice[vec_points[i]] = 8;
	    }
	    tetro[position] = type;
	    return position;
	}
}

/*  Delete a piece at the given position */
int delete_tetro(int lattice[], string tetro[], int position, string type){
    int orientation = lattice[position];
	vector<int> vec_points = points(position, orientation, type);
	for(int i=0; i<4; i++){
	        lattice[vec_points[i]] = 0;
	}
	tetro[position] = "";
	return position;
}

int translate_tetro(int lattice[], string tetro[], string type){
/*  Translate a pice */
	int position = randomTetro(tetro, type);
	if(position < 0) return 1;
	int orientation = lattice[position];
	int direction = randomDirection();
	int newposition;
	delete_tetro(lattice, tetro, position, type);
	
	switch (direction) {
	case 1:
		newposition = position + 1;
		break;
	case 2:
		newposition = position + SIZE;
		break;
	case 3:
		newposition = position - 1;
		break;
	case 4:
		newposition = position - SIZE;
		break;
	}
	if(newposition > SIZE*SIZE-1) newposition = newposition - SIZE*SIZE;
	if(newposition < 0) newposition = newposition + SIZE*SIZE;

/*  Check if the piece fits at the new position */
	if (checkFit(lattice, newposition, orientation, type) == 0) {
		insert_tetro(lattice, tetro, newposition, orientation, type);
	}
/*  If not, insert it at the original spot */
	else {
		insert_tetro(lattice, tetro, position, orientation, type);
	}
	return 0;
}

int rotate_tetro(int lattice[], string tetro[], string type) {
/*  Rotate a tetromino at the given position */
	int position = randomTetro(tetro, type);
	if (position < 0 ) return 1;
	int orientation = lattice[position];
	delete_tetro(lattice, tetro, position, type);

	int neworientation = randomDirection();
/*  Check if the piece fits at the new orientation */
	if (checkFit(lattice, position, neworientation, type) == 0) {
		insert_tetro(lattice, tetro, position, neworientation, type);
	}
/*  If not, insert it at the original spot */
	else {
		insert_tetro(lattice, tetro, position, orientation, type);
	}
	return 0;
}

int performStep(int lattice[], string tetro[], double pot, string type) {
/*  Perform a step at the ratios 3:3:6:2 */
	int step = randomStep();
	int occupied = randomTetro(tetro, type);
	int free = randomFree(lattice);
	int orientation = randomDirection();
	double probability;

	switch(step) {
	case 1:
	case 2:
	case 3:
      probability = exp(pot) * (SIZE*SIZE) / (count(tetro,type) + 1);
	  if (randomUni() < probability) {
		    insert_tetro(lattice, tetro, free, orientation, type);
		}
		break;
	case 4:
	case 5:
	case 6:
		if (occupied != -1) {
            probability = exp(-pot) * count(tetro, type) / (SIZE*SIZE);
	      if (randomUni() < probability) {
			    delete_tetro(lattice, tetro, occupied, type);
		    }
		}

		break;
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		translate_tetro(lattice, tetro, type);
		break;
	case 16:
	case 17:
		rotate_tetro(lattice, tetro, type);
		break;
	}
	return 0;
}
