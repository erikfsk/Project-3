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

    planet sun = planet(4*M_PI*M_PI,0,0,0,0,0,0);
    planet earth = planet(1,1,0,0,0,2*M_PI,0);
    cout << earth.distance(sun) <<endl;
    earth.verlet_step(sun);
}


