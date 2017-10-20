#include <iostream>
#include <cstdio>
#include <cmath>
#include <armadillo>
#include <fstream>
#include <stdlib.h>
#include <boost/timer.hpp>
#include "planet.h"

using namespace std;
using namespace arma;



int main (int argc, char *argv[])
{
	/*
	ofstream outFile;
    outFile.open("object_ori_euler.txt", std::ios::out);
    if (! outFile.is_open()) {
        cout << "Problem opening file." << endl;
        exit(1);
    }
    outFile << "x y" << endl;
    */
    double t_start = 0; double t_end = 5; int n = 100000;
    double h = (t_end-t_start)/(n-1);

    int nr_planets = 2;
    
    planet solarsystem[nr_planets];
    
    /*
    ofstream outFiles[nr_planets];
    for(int i = 0;i < n; i++){
    	ofstream outFile;
    	outFiles[i] = ofstream;	
    }
   	*/


    solarsystem[0] = planet(4*M_PI*M_PI,0,0,0,0,0,0);


    solarsystem[1] = planet(1,1,0,0,0,2*M_PI,0);
    

    cout << solarsystem[1].distance(solarsystem[0]) <<endl;
    solarsystem[1].verlet_step(solarsystem[0],1);
}


