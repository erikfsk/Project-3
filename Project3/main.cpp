#include <iostream>
#include <cstdio>
#include <cmath>
#include <armadillo>
#include <fstream>
#include <stdlib.h>
#include <boost/timer.hpp>

using namespace std;
using namespace arma;

void interacting(int n, double h,double w_r);
void noninteracting(int n, double h);

bool test_jacobi();
bool test_biggest_func();
vec jacobi(mat a, int n);
void jacobi_solver(mat &a,int n,int k,int l);
double biggest_func(mat a,int n, int &k, int &l);
int write_to_file(string datafil,mat f_tilde,int n,double h);


int main (int argc, char *argv[])
{
    if(!test_jacobi() || !test_biggest_func()) {
        cout << "error" << endl;
        exit(0);
    }


    //int n = atoi(argv[1]);
    double w_r = 0.5;
    double rho_end = 5;


    boost::timer t_test;
    t_test.elapsed();

    for(int n = 10; n < 321; n = n*2){
        double h = (rho_end)/n;
        boost::timer t;
        noninteracting(n,h);
        cout << "Time usage noninteracting: " << t.elapsed() << endl;

        boost::timer t_;
        interacting(n,h,w_r);
        cout << "Time usage interacting: " << t_.elapsed() << endl;
    }
}




void noninteracting(int n, double h){
    mat V = zeros<mat>(n,n);
    for (int i=0; i<n; i++) {
        V(i,i)= (2/(h*h)) +(h*i*h*i);
        if (i < n-1){
          V(i+1,i) = -1/(h*h);
        }
        if (i > 0){
          V(i-1,i) = -1/(h*h);
        }
    }

    mat eig = sort(jacobi(V,n));
    cout << eig(0) << endl;
    cout << eig(1) << endl;
    cout << eig(2) << endl;
}



void interacting(int n, double h,double w_r){
    mat V = zeros<mat>(n,n);

    for (int i=0; i<n; i++) {

        V(i,i)= (2/(h*h)) + (w_r*w_r*h*i*h*i) + (1/(h*i));
        if (i < n-1){
          V(i+1,i) = -1/(h*h);
        }
        if (i > 0){
          V(i-1,i) = -1/(h*h);
        }
    }
}



vec jacobi(mat a, int n)
{
    int k;
    int l;
    double biggest = biggest_func(a,n,k,l);
    while (abs(biggest)>0.01){
        jacobi_solver(a,n,k,l);
        biggest = biggest_func(a,n,k,l);
    }
    vec eigs = a.diag();
    return eigs;
}



void jacobi_solver(mat &a,int n,int k,int l){
    double tau = (a(l,l) - a(k,k))/(2*a(k,l));
    double t_;
    if ( tau > 0 ) {
        t_ = 1.0/ (tau + sqrt(1.0 + tau*tau));
    } else {
        t_ = -1.0/ (-tau + sqrt(1.0 + tau*tau));
    }

    double c_ = 1/sqrt(1 + (t_*t_));    //cos(theta)
    double s_ = c_*t_;                  //sin(theta)
    double a_kk = a(k,k);
    double a_ll = a(l,l);
    double a_kl = a(k,l);

    a(k,k) = (a_kk*c_*c_) - (2*a_kl*c_*s_) + (a_ll*s_*s_);
    a(l,l) = (a_ll*c_*c_) + (2*a_kl*c_*s_) + (a_kk*s_*s_);
    a(k,l) = ((a_kk - a_ll)*s_*c_) + (a_kl*(c_*c_ - s_*s_));
    a(l,k) = a(k,l);
    for(int i = 0;i<n;i++){
        if (i !=k && i!= l){
            double a_il = a(i,l);
            double a_ik = a(i,k);
            a(i,k) = a_ik*(c_) - a_il*(s_);
            a(i,l) = a_il*(c_) + a_ik*(s_);
            a(k,i) = a(i,k);
            a(l,i) = a(i,l);
        }
    }
}



double biggest_func(mat a,int n, int &k, int &l){
    double biggest = 0;
    for(int i = 0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i!=j){
                if(abs(a(i,j)) > abs(biggest)){
                    biggest = a(i,j);
                    k = i; l = j;
                }
            }
        }
    }
    return biggest;
}



bool test_jacobi(){
    int n = 3;
    mat test = zeros<mat>(n,n);
    for (int i=0; i<n; i++) {
        test(i,i)= 1;
        if (i < n-1){
          test(i+1,i) = 2;
        }
        if (i > 0){
          test(i-1,i) = 2;
        }
    }

    double tol = 1e-5;
    mat computed = sort(jacobi(test,n));
    vec expected = sort(eig_sym(test)); // testing with armadillo

    for(int i = 0; i < 3; i++){
        if (abs(computed(i) - expected(i)) > tol){
            return false;
        }
    }
    cout << "jacobi test was successful" << endl;
    return true;
}



bool test_biggest_func(){
    int n = 3;
    mat test = zeros<mat>(n,n);
    for (int i=0; i<n; i++) {
        test(i,i)= 33;
        if (i < n-1){
          test(i+1,i) = 7;
        }
        if (i > 0){
          test(i-1,i) = 1;
        }
    }

    int k = 0;
    int l = 0;
    double tol = 1e-5;
    double expected = 7;
    double computed = biggest_func(test,n,k,l);
    if (abs(computed - expected) > tol){
        return false;
    }
    cout << "Biggest_func test was successful" << endl;
    return true;
}




