#include "planet.h"

planet::planet()
{

    mass = 1.;
    name = "SUN.txt";
    position[0] = 0.;
    position[1] = 0.;
    position[2] = 0.;
    velocity[0] = 0.;
    velocity[1] = 0.;
    velocity[2] = 0.;
    acceleration[0] = 0.;
    acceleration[1] = 0.;
    acceleration[2] = 0.;
    potential = 0.;
    kinetic = 0.;
}

planet::planet(char* name_in, double M, double x, double y, double z, double vx, double vy, double vz)
{
    mass = M;
    name = name_in;
    position[0] = x;
    position[1] = y;
    position[2] = z;
    velocity[0] = vx;
    velocity[1] = vy;
    velocity[2] = vz;
    acceleration[0] = 0.;
    acceleration[1] = 0.;
    acceleration[2] = 0.;
    oldacceleration[0] = acceleration[0];
    oldacceleration[1] = acceleration[1];
    oldacceleration[2] = acceleration[2];
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

void planet::Acceleration(planet otherPlanet, double Gconst)
{
    double r = this->distance(otherPlanet);
    double a = - this->GravitationalForce(otherPlanet,Gconst)/(this->mass*r);
    acceleration[0] = acceleration[0] + a*(this->position[0]-otherPlanet.position[0]);
    acceleration[1] = acceleration[1] + a*(this->position[1]-otherPlanet.position[1]);
    acceleration[2] = acceleration[2] + a*(this->position[2]-otherPlanet.position[2]);
}

void planet::Acceleration_reset(){
    oldacceleration[0] = acceleration[0];
    oldacceleration[1] = acceleration[1];
    oldacceleration[2] = acceleration[2];
    acceleration[0] = 0;
    acceleration[1] = 0;
    acceleration[2] = 0;
}


void planet::verlet_position(double t_step){
    //x[i] = x[i-1] + h*Vx[i-1] + (0.5*h*h*a*(x[i-1]));
    this->position[0] = position[0] + t_step*this->velocity[0] + (0.5*t_step*t_step*acceleration[0]);
    this->position[1] = position[1] + t_step*this->velocity[1] + (0.5*t_step*t_step*acceleration[1]);
    this->position[2] = position[2] + t_step*this->velocity[2] + (0.5*t_step*t_step*acceleration[2]);
}

void planet::verlet_velocity(double t_step){
    //Vx[i] = Vx[i-1] + 0.5*h*(a*(x[i-1] + x[i]));
    this->velocity[0] = this->velocity[0] + (0.5*t_step*(acceleration[0]+oldacceleration[0]));
    this->velocity[1] = this->velocity[1] + (0.5*t_step*(acceleration[1]+oldacceleration[1]));
    this->velocity[2] = this->velocity[2] + (0.5*t_step*(acceleration[2]+oldacceleration[2]));
}



bool planet::clear_file(){
    ofstream outFile;
    outFile.open(this->name, std::ios::out);
    if (! outFile.is_open()) {
        cout << "Problem opening file." << endl;
        exit(1);
    }
    outFile << "x y z" << endl;
    outFile.close();
    return true;
}

bool planet::write_to_file(){
    ofstream outFile;
    outFile.open(this->name, std::ios::app);
    if (! outFile.is_open()) {
        cout << "Problem opening file." << endl;
        exit(1);
    }
    outFile << this->position[0] << " " << this->position[1] << " " << this->position[2] << endl;
    outFile.close();
    return true;
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
