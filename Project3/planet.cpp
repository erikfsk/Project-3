#include "planet.h"

planet::planet()
{//intializer 
    mass = 4.*M_PI*M_PI;
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
    oldacceleration[0] = acceleration[0];
    oldacceleration[1] = acceleration[1];
    oldacceleration[2] = acceleration[2];
    potential = 0.;
    kinetic = 0.;
}

planet::planet(char* name_in, double M, double x, double y, double z, double vx, double vy, double vz)
{ //intializer for any planet
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
}


double planet::distance(planet otherPlanet)
{   //finds the distance between two planets
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
{   //gravitational force between two planets, will return 0 if they are on top each other
    double r = this->distance(otherPlanet);
    if(r!=0) return Gconst*this->mass*otherPlanet.mass/(r*r);
    else return 0;
}

void planet::Acceleration(planet otherPlanet, double Gconst)
{   //Acceleration method to add a acceleration for a planet on top of the previous acceleration
    double r = this->distance(otherPlanet);
    double a = - this->GravitationalForce(otherPlanet,Gconst)/(this->mass*r);
    acceleration[0] = acceleration[0] + a*(this->position[0]-otherPlanet.position[0]);
    acceleration[1] = acceleration[1] + a*(this->position[1]-otherPlanet.position[1]);
    acceleration[2] = acceleration[2] + a*(this->position[2]-otherPlanet.position[2]);
}






double planet::GravitationalForce_perihelion(planet otherPlanet,double Gconst)
{   //gravitational force between two planets, will return 0 if they are on top each other
    // but this time for the perihelion assignment
    double r = this->distance(otherPlanet);
    double c = 63241;  //speed of light in au/year

    //cross product between the position vector and velocity
    double l_x = position[1]*velocity[2] - position[2]*velocity[1];
    double l_y = -(position[0]*velocity[2] - position[2]*velocity[0]);
    double l_z = position[1]*velocity[0] - position[0]*velocity[1];
    
    //length of the cross product above
    double l = sqrt(l_x*l_x + l_y*l_y + l_z*l_z); 
    if(r!=0) return (Gconst*this->mass*otherPlanet.mass/(r*r))*( 1+( (3*l*l)/(r*r*c*c) ) );
    else return 0;
}

void planet::Acceleration_perihelion(planet otherPlanet, double Gconst)
{   //Acceleration method to add a acceleration for a planet on top of the previous acceleration
    //but this uses the force with the perihelion effect
    double r = this->distance(otherPlanet);
    double a = - this->GravitationalForce_perihelion(otherPlanet,Gconst)/(this->mass*r);
    acceleration[0] = acceleration[0] + a*(this->position[0]-otherPlanet.position[0]);
    acceleration[1] = acceleration[1] + a*(this->position[1]-otherPlanet.position[1]);
    acceleration[2] = acceleration[2] + a*(this->position[2]-otherPlanet.position[2]);
}







void planet::Acceleration_reset(){
    //resets the acceleration to zero
    //and keeps the old accelration
    //it is needed for verlet velocity
    oldacceleration[0] = acceleration[0];
    oldacceleration[1] = acceleration[1];
    oldacceleration[2] = acceleration[2];
    acceleration[0] = 0;
    acceleration[1] = 0;
    acceleration[2] = 0;
}


void planet::verlet_position(double t_step){
    //x[i] = x[i-1] + h*Vx[i-1] + (0.5*h*h*a*(x[i-1]));
    this->position[0] = this->position[0] + t_step*this->velocity[0] + (0.5*t_step*t_step*acceleration[0]);
    this->position[1] = this->position[1] + t_step*this->velocity[1] + (0.5*t_step*t_step*acceleration[1]);
    this->position[2] = this->position[2] + t_step*this->velocity[2] + (0.5*t_step*t_step*acceleration[2]);
}

void planet::verlet_velocity(double t_step){
    //Vx[i] = Vx[i-1] + 0.5*h*(a*(x[i-1] + x[i]));
    this->velocity[0] = this->velocity[0] + (0.5*t_step*(acceleration[0]+oldacceleration[0]));
    this->velocity[1] = this->velocity[1] + (0.5*t_step*(acceleration[1]+oldacceleration[1]));
    this->velocity[2] = this->velocity[2] + (0.5*t_step*(acceleration[2]+oldacceleration[2]));
}

void planet::euler_position(double t_step){
    //x[i] = x[i-1] + h*Vx[i-1] + (0.5*h*h*a*(x[i-1]));
    this->position[0] = this->position[0] + t_step*this->velocity[0];
    this->position[1] = this->position[1] + t_step*this->velocity[1];
    this->position[2] = this->position[2] + t_step*this->velocity[2];
}

void planet::euler_velocity(double t_step){
    //Vx[i] = Vx[i-1] + 0.5*h*(a*(x[i-1] + x[i]));
    this->velocity[0] = this->velocity[0] + t_step*acceleration[0];
    this->velocity[1] = this->velocity[1] + t_step*acceleration[1];
    this->velocity[2] = this->velocity[2] + t_step*acceleration[2];
}



bool planet::clear_file(){
    //clear the file with the name of the planet of text
    ofstream outFile;
    outFile.open(this->name, std::ios::out);
    if (! outFile.is_open()) {
        cout << "Problem opening file." << endl;
        exit(1);
    }
    //and writes x y z at the first line
    outFile << "x y z" << endl;
    outFile.close();
    return true;
}

bool planet::write_to_file(){
    //write x y z position to the file with the name of the planet
    ofstream outFile;
    outFile.open(this->name, std::ios::app);
    if (! outFile.is_open()) {
        cout << "Problem opening file." << endl;
        exit(1);
    }
    //setting precision to 16 because we need it for perihelion
    outFile << setprecision(16) << this->position[0] << " " << this->position[1] << " " << this->position[2] << endl;
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
