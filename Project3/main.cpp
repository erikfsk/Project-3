#include <iostream>
#include <cstdio>
#include <cmath>
#include <armadillo>
#include <fstream>
#include <stdlib.h>
#include <boost/timer.hpp>

using namespace std;
using namespace arma;



void eulers_step(vec &x, vec &y, vec &Vx, vec &Vy,double h,int i);
double eulers_method(vec &x, vec &y, vec &Vx, vec &Vy,double h,int n);
double force_g(double distance,double mass_0, double mass_1);
int write_to_file(string datafil,mat t,mat x,mat y,int n);


int main (int argc, char *argv[])
{
    double t_start = 0; double t_end = 365; int n = 100000;
    double t_step = (t_end-t_start)/(n-1);


    vec x = ones<vec>(n); x[0] = 9.008745231347060E-01;
    vec Vx = ones<vec>(n); Vx[0] = -7.708603521431721E-03;
    vec y = ones<vec>(n); y[0] = 4.354368878037240E-01;
    vec Vy = ones<vec>(n); Vy[0] = 1.546968939253316E-02;
    vec t = ones<vec>(n);
    for(int i = 0; i < n; i++){
        t[i] = t_step*i;
    }

    cout << "Hello, project 3" << endl ;

    eulers_method(x, y, Vx, Vy,t_step,n);
    write_to_file("test.txt",t,x,y,n);
    cout << "Project 3 done" << endl;
    double mass_self = 6*pow(10,24);
    double mass_sun = 2*pow(10,32);
}



double force_g(double distance,double mass_0, double mass_1){
    double constant_g = 6.67*pow(10,-11);
    double numerator = constant_g*mass_1;
    double denominator = pow(distance,2);
    return numerator/denominator;
}

double eulers_method(vec &x, vec &y, vec &Vx, vec &Vy,double h,int n){
    for(int i = 1; i < n; i++){
        eulers_step(x,y,Vx,Vy,h,i);
    }
}

void eulers_step(vec &x, vec &y, vec &Vx, vec &Vy,double h,int i){
    double a = pow(Vx[i-1]*Vx[i-1] +Vy[i-1]*Vy[i-1],2)/pow((x[i-1]*x[i-1]) + (y[i-1]*y[i-1]),0.5);
    Vy[i] = Vy[i-1] + (h*a*(x[i-1])/pow((x[i-1]*x[i-1]) + (y[i-1]*y[i-1]),0.5));
    Vx[i] = Vx[i-1] + (h*a*(y[i-1])/pow((x[i-1]*x[i-1]) + (y[i-1]*y[i-1]),0.5));
    y[i] = y[i-1] + h*Vy[i-1];
    x[i] = x[i-1] + h*Vx[i-1];
}

int write_to_file(string datafil,mat t,mat x,mat y,int n)
{
    ofstream outFile;
    outFile.open(datafil, std::ios::out);
    if (! outFile.is_open()) {
        cout << "Problem opening file." << endl;
        exit(1);
    }
    outFile << "t x y" << endl;
    for (int i = 0; i < n; i++) {
        outFile << t[i] << " " << x[i] << " " << y[i] << endl;
    }
    outFile.close();
    return 0;
}


