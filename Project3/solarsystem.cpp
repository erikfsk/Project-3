#include "solarsystem.h"

solarsystem::solarsystem(planet* planets_input, int nr_of_planets_input)
{  
    nr_of_planets = nr_of_planets_input;
    system_of_planets = planets_input;
}


void solarsystem::solve_verlet(int n, double t_step){
    Acceleration();
    clear_file();
    for(int i = 1; i<n ; i++){
        verlet_position(t_step);
        Acceleration_reset();
        Acceleration();
        verlet_velocity(t_step);
        if(i % 10 == 0){
            write_to_file();
        }
    }
}

void solarsystem::Acceleration(){
    for(int i=0; i<nr_of_planets-1; i++){
        for(int j=i+1; j<nr_of_planets; j++){
            system_of_planets[i].Acceleration(system_of_planets[j],1);
            system_of_planets[j].Acceleration(system_of_planets[i],1);
        }
    }
    return ; 
}

void solarsystem::Acceleration_reset(){
    for(int i = 0; i < nr_of_planets; i++){
        system_of_planets[i].Acceleration_reset();
    }
    return ;
}

void solarsystem::verlet_position(double t_step){
    for(int i = 0; i < nr_of_planets; i++){
        system_of_planets[i].verlet_position(t_step);
    }
    return ;
}

void solarsystem::verlet_velocity(double t_step){
    for(int i = 0; i < nr_of_planets; i++){
        system_of_planets[i].verlet_velocity(t_step);
    }
    return ;
}

bool solarsystem::clear_file(){
    for(int i = 0; i < nr_of_planets; i++){
        system_of_planets[i].clear_file();
    }
    return true;
}

bool solarsystem::write_to_file(){
    for(int i = 0; i < nr_of_planets; i++){
        system_of_planets[i].write_to_file();
    }
    return true;
}