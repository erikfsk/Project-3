#include <iostream>
#include <cstdio>
#include <cmath>
#include <armadillo>
#include <fstream>
#include <stdlib.h>
#include <boost/timer.hpp>

using namespace std;
using namespace arma;



void eulers_step(vec &x, vec &y, vec &Vx, vec &Vy,double h,int i,double mass_ratio);
double eulers_method(vec &x, vec &y, vec &Vx, vec &Vy,double h,int n,double mass_ratio);

void verlet_step(vec &x, vec &y, vec &Vx, vec &Vy,double h,int i,double mass_ratio);
double verlet_method(vec &x, vec &y, vec &Vx, vec &Vy,double h,int n,double mass_ratio);

double force_g(double distance,double mass_0, double mass_1);
int write_to_file(string datafil,mat t,mat x,mat y,int n);


int main (int argc, char *argv[])
{
    double t_start = 0; double t_end = 1; int n = atoi(argv[1]);
    double t_step = (t_end-t_start)/(n-1);


    vec x = ones<vec>(n); x[0] = 1.;
    vec Vx = ones<vec>(n); Vx[0] = 0;
    vec y = ones<vec>(n); y[0] = 0.;
    vec Vy = ones<vec>(n); Vy[0] = 2*M_PI;
    vec t = ones<vec>(n); 

    for(int i = 0; i < n; i++){
        t[i] = t_step*i;
    }

    cout << "Hello, project 3" << endl ;
    double mass_4pi = 1;//2*pow(10,32);
    eulers_method(x, y, Vx, Vy,t_step,n,mass_4pi);
    write_to_file("euler.txt",t,x,y,n);
    verlet_method(x, y, Vx, Vy,t_step,n,mass_4pi);
    write_to_file("verlet.txt",t,x,y,n);
    cout << "Project 3 done" << endl;
    double mass_self = 6*pow(10,24);
    double mass_sun = 2*pow(10,32);

}

double eulers_method(vec &x, vec &y, vec &Vx, vec &Vy,double h,int n,double mass_ratio){
    for(int i = 1; i < n; i++){
        eulers_step(x,y,Vx,Vy,h,i,mass_ratio);
    }
}

void eulers_step(vec &x, vec &y, vec &Vx, vec &Vy,double h,int i,double mass_ratio){
    double hyp = sqrt((x[i-1]*x[i-1]) + (y[i-1]*y[i-1]));
    double a = -(mass_ratio * 4*M_PI*M_PI)/(hyp*hyp*hyp);
    Vy[i] = Vy[i-1] + (h*a*(y[i-1]));
    Vx[i] = Vx[i-1] + (h*a*(x[i-1]));
    
    y[i] = y[i-1] + h*Vy[i-1];
    x[i] = x[i-1] + h*Vx[i-1];
}

double verlet_method(vec &x, vec &y, vec &Vx, vec &Vy,double h,int n,double mass_ratio){
    for(int i = 1; i < n; i++){
        verlet_step(x,y,Vx,Vy,h,i,mass_ratio);
    }
}

void verlet_step(vec &x, vec &y, vec &Vx, vec &Vy,double h,int i,double mass_ratio){
    double hyp = sqrt((x[i-1]*x[i-1]) + (y[i-1]*y[i-1]));
    double a = -(mass_ratio * 4*M_PI*M_PI)/(hyp*hyp*hyp);

    y[i] = y[i-1] + h*Vy[i-1] + (0.5*h*h*a*(y[i-1]));
    x[i] = x[i-1] + h*Vx[i-1] + (0.5*h*h*a*(x[i-1]));

    Vy[i] = Vy[i-1] + 0.5*h*(a*(y[i-1] + y[i]));
    Vx[i] = Vx[i-1] + 0.5*h*(a*(x[i-1] + x[i]));
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

