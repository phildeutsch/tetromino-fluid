#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

#include "defs.h"
#include "fit.h"
#include "random.h"
#include "moves.h"

int print_rectangle(ofstream &tetrofile, string shade, double x, double y, 
    int l, int r, int u, int d){
/*  print a rectangle at the specified point (x,y), using a color given in shade
    Left, right, upper and lower Borders are drawn only when l,r,u or d equal 1,
    respectively. */

    tetrofile << "\\path[fill=" << shade << "](" << x << "," << y <<")";
    tetrofile << " rectangle (" << x + 0.1 << "," << y + 0.1 << ");\n";
    if (l==1) {
        tetrofile << "\\draw (" << x << "," << y << ") -- ("
        << x << "," << y + 0.1 << ");\n";
    }
    else {
        tetrofile << "\\draw[color=" << shade << "] (" << x << ","
        << y + 0.01 << ") -- (" << x << "," << y + 0.09 << ");\n";
    }
    if (r==1) {
        tetrofile << "\\draw (" << x + 0.1 << "," << y << ") -- ("
        << x + 0.1 << "," << y + 0.1 << ");\n";
    }
    else {
        tetrofile << "\\draw[color=" << shade << "] ("  << x + 0.1 << ","
        << y + 0.01 << ") -- (" << x + 0.1 << "," << y + 0.09 << ");\n";
    }    
    if (u==1) {
        tetrofile << "\\draw (" << x << "," << y + 0.1 << ") -- ("
        << x + 0.1 << "," << y + 0.1 << ");\n";
    }
    else {
        tetrofile << "\\draw[color=" << shade << "] (" << x + 0.01 << ","
        << y + 0.1 << ") -- (" << x + 0.09 << "," << y + 0.1 << ");\n";
    }
    if (d==1) {
        tetrofile << "\\draw (" << x << "," << y << ") -- ("
        << x + 0.1 << "," << y << ");\n";
    }
    else {
        tetrofile << "\\draw[color=" << shade << "] (" << x + 0.01 << ","
        << y << ") -- (" << x + 0.09 << "," << y << ");\n";
    }          
    return 0;
}


int print_tetro(ofstream &tetrofile, int lattice[], int position, 
    string type){
/*    Prints the tetromino at the specified position and orientation
*/
    double x,y;
    double x1, y1, x2, y2, x3, y3;
    string color;
    stringstream shade;
    
    int orientation = lattice[position];

/*  The lattice points are stored in a vector */    
    vector<int> vec_points = points(position, orientation, type);

/*  The points in the vector a transformed into cartesian coordinates for
    plotting */
    x = position%SIZE / 10.;
    y = (SIZE - position/SIZE - 1) / 10.;
    
    x1 = vec_points[1]%SIZE / 10.;
    y1 = (SIZE - vec_points[1]/SIZE - 1) / 10.;
    x2 = vec_points[2]%SIZE / 10.;
    y2 = (SIZE - vec_points[2]/SIZE - 1) / 10.;
    x3 = vec_points[3]%SIZE / 10.;
    y3 = (SIZE - vec_points[3]/SIZE - 1) / 10.;

/*  Print some debugging information in case something goes wrong */    
    if (x1 < 0 || y1 < 0 ){
            cout << "This should not have happened" << endl;
            cout << position << ", " << orientation << endl;
    }
/*  Print the four rectangles for each tetromino */
    if (type == "T"){ color = "pink";
        if (orientation == 1) {
            shade << color;
            print_rectangle(tetrofile, shade.str(), x, y, 0, 0, 0, 1);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 1, 1, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 1, 1, 0);
        }
        else if (orientation == 2) {
            shade << color << "!90!white";
            print_rectangle(tetrofile, shade.str(), x, y, 1, 0, 0, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 1, 1, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 1, 0, 1);
        }
        else if (orientation == 3) {
            shade << color << "!70!black";
            print_rectangle(tetrofile, shade.str(), x, y, 0, 0, 1, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 1, 1, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 1, 0, 1);
        }
        else if (orientation == 4) {
            shade << color << "!50!black";
            print_rectangle(tetrofile, shade.str(), x, y, 0, 1, 0, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 1, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 0, 1, 1);
        }
    }
    else if (type == "S"){
        color = "green";
        if (orientation == 1) {
            shade << color << "!70!black";
            print_rectangle(tetrofile, shade.str(), x, y, 0, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x1, y1, 1, 0, 1, 0);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 0, 1, 1, 1);
        }
        else if (orientation == 2) {
            shade << color << "!50!black";
            print_rectangle(tetrofile, shade.str(), x, y, 1, 0, 0, 1);
            print_rectangle(tetrofile, shade.str(), x1, y1, 1, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x2, y2, 0, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 1, 0, 1);
        }
        else if (orientation == 3) { 
            shade << color << "!70!black";
            print_rectangle(tetrofile, shade.str(), x, y, 1, 0, 1, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 1, 1, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 0, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 0, 1, 1);
        }
        else if (orientation == 4) {
            shade << color << "!50!black";
            print_rectangle(tetrofile, shade.str(), x, y, 0, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 1, 0, 0, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 1, 1, 0);
        }
    }
    else if (type == "L"){ color = "red";
        if (orientation == 1) {
            shade << color;
            print_rectangle(tetrofile, shade.str(), x, y, 1, 1, 0, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 1, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 0, 0, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 0, 1, 1, 1);
        }
        else if (orientation == 2) {
            shade << color << "!90!black";
            print_rectangle(tetrofile, shade.str(), x, y, 0, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 1, 1, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 0, 1, 0);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 1, 0, 1);
        }
        else if (orientation == 3) {
            shade << color << "!70!black";
            print_rectangle(tetrofile, shade.str(), x, y, 1, 1, 0, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 0, 1, 1);
        }
        else if (orientation == 4) {
            shade << color << "!50!black";
            print_rectangle(tetrofile, shade.str(), x, y, 0, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 1, 1, 0);
        }
    }
    else if (type == "I") {
        color = "blue";
        if (orientation == 1) {
            shade << color << "!25!white";
            print_rectangle(tetrofile, shade.str(), x, y, 0, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 0, 1, 1, 1);
        }
        else if (orientation == 2) {
            shade << color << "!50!white";
            print_rectangle(tetrofile, shade.str(), x, y, 1, 1, 0, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 1, 1, 0, 0);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 1, 0, 1);
        }
        else if (orientation == 3) {
            shade << color << "!25!white";
            print_rectangle(tetrofile, shade.str(), x, y, 0, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 0, 1, 1, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 0, 1, 1);
        }
        else if (orientation == 4) {
            shade << color << "!50!white";
            print_rectangle(tetrofile, shade.str(), x, y, 1, 1, 0, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 1, 1, 0, 0);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 1, 1, 0);
        }
    }
    else if (type == "J") {
        color = "violet";
        if (orientation == 1) {
            shade << color;
            print_rectangle(tetrofile, shade.str(), x, y, 1, 1, 0, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 1, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x2, y2, 0, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 0, 1, 1);
        }
        else if (orientation == 2) {
            shade << color << "!90!black";
            print_rectangle(tetrofile, shade.str(), x, y, 0, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 1, 1, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 0, 0, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 1, 1, 0);
        }
        else if (orientation == 3) {
            shade << color << "!50!white";
            print_rectangle(tetrofile, shade.str(), x, y, 1, 1, 0, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 1, 0, 1, 0);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 0, 1, 1, 1);
        }
        else if (orientation == 4) {
            shade << color << "!20!white";
            print_rectangle(tetrofile, shade.str(), x, y, 0, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 1, 0, 1);
        }
    }
    else if (type == "Z") {
        color = "orange";
        if (orientation == 1) {
            shade << color;
            print_rectangle(tetrofile, shade.str(), x, y, 1, 0, 0, 1);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 1, 1, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 0, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 0, 1, 1);
        }
        else if (orientation == 2) {
            shade << color << "!70!black";
            print_rectangle(tetrofile, shade.str(), x, y, 1, 0, 1, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 1, 1, 0);
        }
        else if (orientation == 3) {
            shade << color;
            print_rectangle(tetrofile, shade.str(), x, y, 0, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 1, 0, 1, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 0, 0, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 0, 1, 1, 1);
        }
        else if (orientation == 4) {
            shade << color << "!70!black";
            print_rectangle(tetrofile, shade.str(), x, y, 0, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x1, y1, 1, 0, 1, 0);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 1, 0, 1);
        }
    }
    else if (type == "O"){ color = "yellow";
        shade << color;
        if (orientation == 1) {
            print_rectangle(tetrofile, shade.str(), x, y, 1, 0, 0, 1);
            print_rectangle(tetrofile, shade.str(), x1, y1, 1, 0, 1, 0);
            print_rectangle(tetrofile, shade.str(), x2, y2, 0, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 0, 1, 1, 0);
        }
        if (orientation == 2) {
            print_rectangle(tetrofile, shade.str(), x, y, 1, 0, 1, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 1, 0, 0, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 0, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x3, y3, 0, 1, 0, 1);
        }
        if (orientation == 3) {
            print_rectangle(tetrofile, shade.str(), x, y, 0, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 0, 1, 0);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 0, 0, 1);
        }
        if (orientation == 4) {
            print_rectangle(tetrofile, shade.str(), x, y, 0, 1, 0, 1);
            print_rectangle(tetrofile, shade.str(), x1, y1, 0, 1, 1, 0);
            print_rectangle(tetrofile, shade.str(), x2, y2, 1, 0, 0, 1);
            print_rectangle(tetrofile, shade.str(), x3, y3, 1, 0, 1, 0);
        }
    }
    
    return 0;
}

/*  Print the whole lattice to the terminal */
int printLattice(int lattice[]) {
    for (int i=0;i<SIZE*SIZE;i++) {
        if (lattice[i] == 0) cout << ".";
        else cout << lattice[i];
        if ((i+1)%SIZE ==  0) cout << endl;
    }
    cout << endl;
    return 0;
}

/*  Print tetromino pieces and their orientation to the terminal */
int printTetros(string tetro[]) {
    for (int i=0;i<SIZE*SIZE;i++) {
        if (tetro[i] == "") cout << ".";
        else cout << tetro[i];
        if ((i+1)%SIZE == 0) cout << endl;
    }
    cout << endl;
    return 0;
}

/*  Print the configuration to a file.
    Can be shown in latex using \usepackage{tikz} in the preamble and then 
    just \input{filename} in the document body.
*/
int printToFile(string filename, int lattice[], string tetro[]){

    ofstream tetrofile;
    tetrofile.open(filename.c_str());   
    tetrofile << "\\begin{tikzpicture}\n";

    for (int i=0; i<SIZE*SIZE; i++) {
        if (tetro[i] != "") {
            print_tetro(tetrofile, lattice, i, tetro[i]);
        }
    }
    tetrofile << "\\draw(0,0) rectangle(" << SIZE/10. << "," 
        << SIZE/10. << ");\n";
    tetrofile << "\\end{tikzpicture}";
    tetrofile.close();

    return 0;
}
