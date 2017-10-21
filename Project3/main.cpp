#include <iostream>
#include <cstdio>
#include <cmath>
#include <armadillo>
#include <fstream>
#include <stdlib.h>
#include <boost/timer.hpp>
#include "planet.h"
#include "solarsystem.h"

using namespace std;
using namespace arma;




void solve_solarsystem(planet planets);




int main (int argc, char *argv[])
{

    double t_start = 0; double t_end = 1; int n = 10000;
    double h = (t_end-t_start)/(n-1);

    int nr_planets = 3;
    
    planet system_of_planets[nr_planets];
    system_of_planets[0] = planet("sun.txt",4*M_PI*M_PI,0,0,0,0,0,0);
    system_of_planets[1] = planet("earth.txt",1,1,0,0,0,2*M_PI,0);
    system_of_planets[2] = planet("earth2.txt",1,-1,0,0,0,-2*M_PI,0);
    
    solarsystem first_try = solarsystem(system_of_planets,nr_planets);
    first_try.solve_verlet(n,h);
    /*
    int write_counter = 1;
    for(int i  = 1; i < n; i++){
        for(int j = 0; j < nr_planets;j++){
            solarsystem[j].Acceleration_reset();
            for(int k = 0; k < nr_planets;k++){
                if(j != k){
                    solarsystem[j].Acceleration(solarsystem[k],1);
                }
            }
        }

        for(int j = 0; j < nr_planets;j++){
            solarsystem[j].verlet_position(h);
            solarsystem[j].verlet_velocity(h);
            solarsystem[j].write_to_file();
        }
        write_counter++;
    }
    */
}


void solve_solarsystem(planet planets){
    return ;
}

