#ifndef PLANET_H
#define PLANET_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>
#include <cstdio>
#include <armadillo>
#include <fstream>
#include <stdlib.h>
using namespace std;

class planet
{
public:
    // Properties
    double mass;
    double position[3];
    double velocity[3];
    double acceleration[3];
    double oldacceleration[3];
    double potential;
    double kinetic;

    // Initializers
    planet();
    planet(char* name, double M,double x,double y,double z,double vx, double vy,double vz);

    // Functions

    double get_Vx();
    double get_Vy();
    double get_Vz();

    double get_x();
    double get_y();
    double get_z();
    double distance(planet otherPlanet);
    
    void Acceleration_reset();
    void Acceleration(planet otherPlanet, double Gconst);
    double GravitationalForce(planet otherPlanet, double Gconst);

    void verlet_velocity(double t_step);
    void verlet_position(double t_step);

    bool clear_file();
    bool write_to_file();
    double KineticEnergy();
    double PotentialEnergy(planet &otherPlanet, double Gconst, double epsilon);

protected:
    char* name;
};

#endif // PLANET_H
