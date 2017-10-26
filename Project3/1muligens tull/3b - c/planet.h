#ifndef PLANET_H
#define PLANET_H
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
using std::vector;


class planet
{
public:
    // Properties
    double mass;
    double position[3];
    double velocity[3];
    double potential;
    double kinetic;

    // Initializers
    planet();
    planet(double M,double x,double y,double z,double vx, double vy,double vz);

    // Functions
    double get_x();
    double get_y();
    double get_z();
    double get_Vx();
    double get_Vy();
    double get_Vz();
    double distance(planet otherPlanet);
    double GravitationalForce(planet otherPlanet, double Gconst);
    double Acceleration(planet otherPlanet, double Gconst);
    void eulers_step(planet otherPlanet);
    void verlet_step(planet otherPlanet);
    double KineticEnergy();
    double PotentialEnergy(planet &otherPlanet, double Gconst, double epsilon);

};

#endif // PLANET_H
