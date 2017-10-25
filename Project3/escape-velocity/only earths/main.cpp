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
    double mass_sun = 2*pow(10,32);
    double mass_mercury = 3.3*pow(10,23);
    double mass_venus = 4.9*pow(10,24);
    double mass_earth = 6*pow(10,24);
    double mass_mars = 6.6*pow(10,23);
    double mass_jupitur = 1.9*pow(10,27);
    double mass_saturn = 5.5*pow(10,26);
    double mass_uranus = 8.8*pow(10,25);
    double mass_neptun = 1.03*pow(10,26);
    double mass_pluto = 1.31*pow(10,22);




    double t_start = 0; double t_end = 10; int n = atoi(argv[1]);
    double h = (t_end-t_start)/(n-1);


    //cout << argv[1] << endl;
    int nr_planets = 9;
    planet system_of_planets[nr_planets];

    if(1 <= nr_planets){
        system_of_planets[0] = planet("sun.txt",4*M_PI*M_PI,0,0,0,0,0,0);
    }

    if(2 <= nr_planets){
        system_of_planets[1] = planet("earth14.txt"                           //filename
                                        ,4*M_PI*M_PI*mass_earth/mass_sun    //Mass_ratio to sun
                                        ,1                                  //Position x
                                        ,0                                  //Position y
                                        ,0                                  //Position z
                                        ,0                                  //Velocity x
                                        ,1.4*M_PI                             //Velocity y
                                        ,0                                  //Velocity z
                                        );
    }

    if(3 <= nr_planets){
        system_of_planets[2] = planet("earth88.txt"                           //filename
                                        ,4*M_PI*M_PI*mass_earth/mass_sun    //Mass_ratio to sun
                                        ,1                                  //Position x
                                        ,0                                  //Position y
                                        ,0                                  //Position z
                                        ,0                                  //Velocity x
                                        ,8.8                                //Velocity y
                                        ,0                                  //Velocity z
                                        );
    }

    if(4 <= nr_planets){
        system_of_planets[3] = planet("earth18.txt"                           //filename
                                        ,4*M_PI*M_PI*mass_earth/mass_sun    //Mass_ratio to sun
                                        ,1                                  //Position x
                                        ,0                                  //Position y
                                        ,0                                  //Position z
                                        ,0                                  //Velocity x
                                        ,1.8*M_PI                             //Velocity y
                                        ,0                                  //Velocity z
                                        );
    }


    if(5 <= nr_planets){
        system_of_planets[4] = planet("earth2.txt"                           //filename
                                        ,4*M_PI*M_PI*mass_earth/mass_sun    //Mass_ratio to sun
                                        ,1                                  //Position x
                                        ,0                                  //Position y
                                        ,0                                  //Position z
                                        ,0                                  //Velocity x
                                        ,2*M_PI                             //Velocity y
                                        ,0                                  //Velocity z
                                        );
    }


    if(6 <= nr_planets){
        system_of_planets[5] = planet("earth89.txt"                           //filename
                                        ,4*M_PI*M_PI*mass_earth/mass_sun    //Mass_ratio to sun
                                        ,1                                  //Position x
                                        ,0                                  //Position y
                                        ,0                                  //Position z
                                        ,0                                  //Velocity x
                                        ,8.9                                //Velocity y
                                        ,0                                  //Velocity z
                                        );
    }


    if(7 <= nr_planets){
        system_of_planets[6] = planet("earth24.txt"                           //filename
                                        ,4*M_PI*M_PI*mass_earth/mass_sun    //Mass_ratio to sun
                                        ,1                                  //Position x
                                        ,0                                  //Position y
                                        ,0                                  //Position z
                                        ,0                                  //Velocity x
                                        ,2.4*M_PI                             //Velocity y
                                        ,0                                  //Velocity z
                                        );
    }


    if(8 <= nr_planets){
        system_of_planets[7] = planet("earth26.txt"                           //filename
                                        ,4*M_PI*M_PI*mass_earth/mass_sun    //Mass_ratio to sun
                                        ,1                                  //Position x
                                        ,0                                  //Position y
                                        ,0                                  //Position z
                                        ,0                                  //Velocity x
                                        ,2.6*M_PI                             //Velocity y
                                        ,0                                  //Velocity z
                                        );
    }



    if(9 <= nr_planets){
        system_of_planets[8] = planet("earth93.txt"                           //filename
                                        ,4*M_PI*M_PI*mass_earth/mass_sun    //Mass_ratio to sun
                                        ,1                                  //Position x
                                        ,0                                  //Position y
                                        ,0                                  //Position z
                                        ,0                                  //Velocity x
                                        ,3*M_PI                             //Velocity y
                                        ,0                                  //Velocity z
                                        );
    }

    solarsystem first_try = solarsystem(system_of_planets,nr_planets);
    first_try.solve_verlet_only_from_sun(n,h);
}
