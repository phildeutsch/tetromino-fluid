#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

double vecMean(vector<double> vec){
/* Caclulate the mean of a vector */
    double sum = 0;
    int length = 0;
   
    for(vector<double>::const_iterator i = vec.begin(); i < vec.end(); i++){
        sum += *i;
        length = i - vec.begin() + 1;
    }
     
    return sum/length;
}

double vecStdDev(vector<double> vec){
/* Calculate the standart deviation of a vector */
    double mean = vecMean(vec);
    double sum = 0;
    int length = 0;
    
    for(vector<double>::const_iterator i = vec.begin(); i < vec.end(); i++){
        sum += (*i - mean) * (*i - mean);
        length = i - vec.begin() + 1;
    }
    return sqrt(sum/(length-1));
}
