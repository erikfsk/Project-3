#include "planet.h"
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

planet::planet()
{
    mass = 1.;

    position[0] = 0.;
    position[1] = 0.;
    position[2] = 0.;
    velocity[0] = 0.;
    velocity[1] = 0.;
    velocity[2] = 0.;
    potential = 0.;
    kinetic = 0.;
}

planet::planet(double M, double x, double y, double z, double vx, double vy, double vz)
{
    mass = M;
    position[0] = x;
    position[1] = y;
    position[2] = z;
    velocity[0] = vx;
    velocity[1] = vy;
    velocity[2] = vz;
    potential = 0.;
    kinetic = 0.;
}


double planet::distance(planet otherPlanet)
{
    double x1,y1,z1,x2,y2,z2,xx,yy,zz;

    x1 = this->position[0];
    y1 = this->position[1];
    z1 = this->position[2];

    x2 = otherPlanet.position[0];
    y2 = otherPlanet.position[1];
    z2 = otherPlanet.position[2];

    xx = x1-x2;
    yy = y1-y2;
    zz = z1-z2;

    return sqrt(xx*xx + yy*yy + zz*zz);
 }

double planet::GravitationalForce(planet otherPlanet,double Gconst)
{
    double r = this->distance(otherPlanet);
    if(r!=0) return Gconst*this->mass*otherPlanet.mass/(r*r);
    else return 0;
}

double planet::Acceleration(planet otherPlanet, double Gconst)
{
    double r = this->distance(otherPlanet);
    if(r!=0) return this->GravitationalForce(otherPlanet,Gconst)/(this->mass*r);
    else return 0;
}


void planet::eulers_step(planet otherPlanet){
    ofstream outFile;
    outFile.open("object_ori_euler.txt", std::ios::out);
    if (! outFile.is_open()) {
        cout << "Problem opening file." << endl;
        exit(1);
    }
    outFile << "x y" << endl;
    double t_start = 0; double t_end = 5; int n = 100000;
    double h = (t_end-t_start)/(n-1);

    int counter = 0;
    for(int i = 1; i < n; i++){
        /*if(counter == 9){
            counter = 0;
            outFile << position[0] << " " << position[1] << " " << position[2] << endl;
        } else {
            counter++;
        }*/
        outFile << position[0] << " " << position[1] << endl;
        double a = -1*Acceleration(otherPlanet,1);
        cout << a << endl;
        double old_x = this->position[0]; double old_y = this->position[1];
        this->position[0] = old_x + h*this->velocity[0];
        this->position[1] = old_y + h*this->velocity[1];
        this->velocity[0] = this->velocity[0] + (h*a*(old_x));
        this->velocity[1] = this->velocity[1] + (h*a*(old_y));
        
    }
}

void planet::verlet_step(planet otherPlanet){
    ofstream outFile;
    outFile.open("object_ori_verlet.txt", std::ios::out);
    if (! outFile.is_open()) {
        cout << "Problem opening file." << endl;
        exit(1);
    }
    outFile << "x y" << endl;
    double t_start = 0; double t_end = 5; int n = 100000;
    double h = (t_end-t_start)/(n-1);

    int counter = 0;
    for(int i = 1; i < n; i++){
        /*if(counter == 9){
            counter = 0;
            outFile << position[0] << " " << position[1] << " " << position[2] << endl;
        } else {
            counter++;
        }*/
        outFile << position[0] << " " << position[1] << endl;
        double a = -1*Acceleration(otherPlanet,1);
        cout << a << endl;
        double old_x = this->position[0]; double old_y = this->position[1];

        //y[i] = y[i-1] + h*Vy[i-1] + (0.5*h*h*a*(y[i-1]));
        //x[i] = x[i-1] + h*Vx[i-1] + (0.5*h*h*a*(x[i-1]));

        this->position[0] = old_x + h*this->velocity[0] + (0.5*h*h*a*(old_x));
        this->position[1] = old_y + h*this->velocity[1] + (0.5*h*h*a*(old_y));

        //Vy[i] = Vy[i-1] + 0.5*h*(a*(y[i-1] + y[i]));
        //Vx[i] = Vx[i-1] + 0.5*h*(a*(x[i-1] + x[i]));

        this->velocity[0] = this->velocity[0] + (0.5*h*a*(old_x+this->position[0]));
        this->velocity[1] = this->velocity[1] + (0.5*h*a*(old_y+this->position[1]));
        
    }
}


double planet::KineticEnergy()
{
    double velocity2 = (this->velocity[0]*this->velocity[0]) + (this->velocity[1]*this->velocity[1]) + (this->velocity[2]*this->velocity[2]);
    return 0.5*this->mass*velocity2;
}

double planet::PotentialEnergy(planet &otherPlanet, double Gconst, double epsilon)
{
    if(epsilon==0.0) return -Gconst*this->mass*otherPlanet.mass/this->distance(otherPlanet);
    else return (Gconst*this->mass*otherPlanet.mass/epsilon)*(atan(this->distance(otherPlanet)/epsilon) - (0.5*M_PI));
}


double planet::get_x()
{
    return this->position[0];
}


double planet::get_y()
{
    return this->position[1];
}


double planet::get_z()
{
    return this->position[2];
}

double planet::get_Vx()
{
    return this->velocity[0];
}


double planet::get_Vy()
{
    return this->velocity[1];
}


double planet::get_Vz()
{
    return this->velocity[2];
}


