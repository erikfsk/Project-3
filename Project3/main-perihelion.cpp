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


int main (int argc, char *argv[])
{
    double mass_sun = 2*pow(10,30);
    double mass_mercury = 3.3*pow(10,23);
    double mass_venus = 4.9*pow(10,24);
    double mass_earth = 6*pow(10,24);
    double mass_mars = 6.6*pow(10,23);
    double mass_jupitur = 1.9*pow(10,27);
    double mass_saturn = 5.5*pow(10,26);
    double mass_uranus = 8.8*pow(10,25);
    double mass_neptun = 1.03*pow(10,26);
    double mass_pluto = 1.31*pow(10,22);


    double t_start = 0; int t_end = 100; int n = 5e7;
    double h = (t_end-t_start)/(n-1);


    int nr_planets = 2;
    planet system_of_planets[nr_planets];

    if(1 <= nr_planets){
        system_of_planets[0] = planet("sun.txt"
                                        ,4*M_PI*M_PI                        //Mass_ratio to sun
                                        ,0                                  //Position x
                                        ,0                                  //Position y
                                        ,0                                  //Position z
                                        ,0         //Velocity x
                                        ,0          //Velocity y
                                        ,0          //Velocity z
                                        );
    }

//$2458045.500000000 = A.D. 2017-Oct-19 00:00:00.0000 TDB  SUN 
//X = 2.213296131976958E-03 Y = 5.740795718142255E-03 Z =-1.300333836064062E-04
//VX=-5.236918819978495E-06 VY= 5.487345385589584E-06 VZ= 1.229796132639033E-07$

    if(2 <= nr_planets){
        system_of_planets[1] = planet("mercury.txt"                         //filename
                                        ,4*M_PI*M_PI*mass_mercury/mass_sun  //Mass_ratio to sun
                                        ,0             //Position x
                                        ,0.3075            //Position y
                                        ,0              //Position z
                                        ,12.44          //Velocity x
                                        ,0         //Velocity y
                                        ,0         //Velocity z
                                        ); 
    }



    solarsystem first_try = solarsystem(system_of_planets,nr_planets);
    first_try.solve_verlet_fixed_sun_perihelion(n,h);    
}