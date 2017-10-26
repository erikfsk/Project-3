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


    double t_start = 0; int t_end = atoi(argv[2]); int n = atoi(argv[3]);
    double h = (t_end-t_start)/(n-1);


    int nr_planets = atoi(argv[1]);
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
        system_of_planets[1] = planet("earth.txt"                           //filename
                                        ,4*M_PI*M_PI*mass_earth/mass_sun    //Mass_ratio to sun
                                        ,9.008745231347060E-01              //Position x
                                        ,4.354368878037240E-01              //Position y
                                        ,-1.541802405455852E-04             //Position z
                                        ,-7.708603521431721E-03*365         //Velocity x
                                        ,1.546968939253316E-02*365          //Velocity y
                                        ,-8.760625935033381E-07*365         //Velocity z
                                        );
    }

    if(3 <= nr_planets){
        system_of_planets[2] = planet("jupitur.txt"                         //filename
                                        ,4*M_PI*M_PI*mass_jupitur/mass_sun  //Mass_ratio to sun
                                        ,-4.576765120608809E+00             //Position x
                                        ,-2.933101794720733E+00             //Position y
                                        ,1.145345160230888E-01              //Position z
                                        ,3.983653264921868E-03*365          //Velocity x
                                        ,-5.994727676715690E-03*365         //Velocity y
                                        ,-6.419350084082065E-05*365         //Velocity z
                                        ); 
    }

    if(4 <= nr_planets){
        system_of_planets[3] = planet("mercury.txt"                         //filename
                                        ,4*M_PI*M_PI*mass_mercury/mass_sun  //Mass_ratio to sun
                                        ,-3.004912369967300E-01             //Position x
                                        ,-3.291939141643662E-01             //Position y
                                        ,2.715228654907219E-04              //Position z
                                        ,1.515329129252778E-02*365          //Velocity x
                                        ,-1.756496278615964E-02*365         //Velocity y
                                        ,-2.826250874177743E-03*365         //Velocity z
                                        ); 
    }


    if(5 <= nr_planets){
        system_of_planets[4] = planet("venus.txt"                           //filename
                                        ,4*M_PI*M_PI*mass_venus/mass_sun    //Mass_ratio to sun
                                        ,-6.581496097890938E-01             //Position x
                                        ,2.867555966500064E-01              //Position y
                                        ,4.183181369002011E-02              //Position z
                                        ,-8.016961988509333E-03*365         //Velocity x
                                        ,-1.870054841427580E-02*365         //Velocity y
                                        ,2.058573306112892E-04*365          //Velocity z
                                        ); 
    }


    if(6 <= nr_planets){
        system_of_planets[5] = planet("mars.txt"                            //filename
                                        ,4*M_PI*M_PI*mass_mars/mass_sun     //Mass_ratio to sun
                                        ,-1.571535279041875E+00             //Position x
                                        ,5.485373678700209E-01              //Position y
                                        ,4.986713818681023E-02              //Position z
                                        ,-4.043755947260121E-03*365         //Velocity x
                                        ,-1.202794362189266E-02*365         //Velocity y
                                        ,-1.529311915880650E-04*365         //Velocity z
                                        ); 
    }


    if(7 <= nr_planets){
        system_of_planets[6] = planet("saturn.txt"                          //filename
                                        ,4*M_PI*M_PI*mass_saturn/mass_sun   //Mass_ratio to sun
                                        ,-3.421974997678738E-01             //Position x
                                        ,-1.004964711398301E+01             //Position y
                                        ,1.883533993066547E-01              //Position z
                                        ,5.269582020005830E-03*365          //Velocity x
                                        ,-2.084428240279003E-04*365         //Velocity y
                                        ,-2.058055841284417E-04*365         //Velocity z
                                        ); 
    }


    if(8 <= nr_planets){
        system_of_planets[7] = planet("uranus.txt"                          //filename
                                        ,4*M_PI*M_PI*mass_uranus/mass_sun   //Mass_ratio to sun
                                        ,1.785610483247027E+01              //Position x
                                        ,8.816513066524889E+00              //Position y
                                        ,-1.985838436058382E-01             //Position z
                                        ,-1.770055721315316E-03*365         //Velocity x
                                        ,3.343297659935217E-03*365          //Velocity y
                                        ,3.541938833576243E-05*365          //Velocity z
                                        ); 

    }


    if(9 <= nr_planets){
        system_of_planets[8] = planet("neptun.txt"                          //filename
                                        ,4*M_PI*M_PI*mass_neptun/mass_sun   //Mass_ratio to sun
                                        ,2.861564756730530E+01              //Position x
                                        ,-8.815304499659160E+00             //Position y
                                        ,-4.779424150910477E-01             //Position z
                                        ,9.028408345768814E-04*365          //Velocity x
                                        ,3.018504750805792E-03*365          //Velocity y
                                        ,-8.276897020654766E-05*365         //Velocity z
                                        ); 
    }

    if(10 <= nr_planets){
        system_of_planets[9] = planet("pluto.txt"                           //filename
                                        ,4*M_PI*M_PI*mass_pluto/mass_sun    //Mass_ratio to sun
                                        ,1.055312162621389E+01              //Position x
                                        ,-3.171190456877188E+01             //Position y
                                        ,3.407868079992951E-01              //Position z
                                        ,3.049404197428726E-03*365          //Velocity x
                                        ,3.449806073416288E-04*365          //Velocity y
                                        ,-9.077532832745567E-04*365         //Velocity z
                                        ); 
    }


    solarsystem first_try = solarsystem(system_of_planets,nr_planets);
    first_try.solve_verlet(n,h);    
}