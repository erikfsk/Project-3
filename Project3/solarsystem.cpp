#include "solarsystem.h"

solarsystem::solarsystem(planet* planets_input, int nr_of_planets_input)
{  
    nr_of_planets = nr_of_planets_input;
    system_of_planets = planets_input;
}






void solarsystem::solve_verlet(int n, double t_step){
    mass_center();
    remove_momentum();
    Acceleration();
    clear_file();
    for(int i = 1; i<n ; i++){
        verlet_position(t_step,0);
        Acceleration_reset();
        Acceleration();
        verlet_velocity(t_step,0);
        if(i % 12 == 0){
            write_to_file(0);
        }

    }
}

void solarsystem::solve_euler_fixed_sun(int n, double t_step){
    clear_file();
    system_of_planets[0].write_to_file();
    for(int i = 1; i<n ; i++){
        Acceleration_reset();
        Acceleration_fixed_sun();
        euler_position(t_step,1);
        euler_velocity(t_step,1);
        if(i % 12 == 0){
            write_to_file(1);
        }
    }
}

void solarsystem::solve_verlet_fixed_sun(int n, double t_step){
    Acceleration_fixed_sun();
    clear_file();
    system_of_planets[0].write_to_file();
    for(int i = 1; i<n ; i++){
        verlet_position(t_step,1);
        Acceleration_reset();
        Acceleration_fixed_sun();
        verlet_velocity(t_step,1);
        if(i % 12 == 0){
            write_to_file(1);
        }

    }
}

void solarsystem::solve_verlet_only_from_sun(int n, double t_step){
    Acceleration_only_from_sun();
    clear_file();
    system_of_planets[0].write_to_file();
    for(int i = 1; i<n ; i++){
        verlet_position(t_step,1);
        Acceleration_reset();
        Acceleration_only_from_sun();
        verlet_velocity(t_step,1);
        if(i % 12 == 0){
            write_to_file(1);
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


void solarsystem::Acceleration_fixed_sun(){
    for(int i=0; i<nr_of_planets-1; i++){
        for(int j=i+1; j<nr_of_planets; j++){
            if(i != 0){
                system_of_planets[i].Acceleration(system_of_planets[j],1);    
            }
            system_of_planets[j].Acceleration(system_of_planets[i],1);
        }
    }
    return ; 
}


void solarsystem::Acceleration_only_from_sun(){
    for(int i=1; i<nr_of_planets; i++){
        system_of_planets[i].Acceleration(system_of_planets[0],1);    
    }
    return ; 
}




void solarsystem::mass_center(){
    double mass_center[3]; double total_mass = 0;
    mass_center[0] = 0;mass_center[1] = 0;mass_center[2] = 0;

    for(int i = 0; i < nr_of_planets; i++){
        for(int j = 0; j < 3; j++){
            mass_center[j] += system_of_planets[i].position[j]*system_of_planets[i].mass;
        }
        total_mass += system_of_planets[i].mass;
    }

    for(int i = 0; i <3 ; i++){
        mass_center[i] = mass_center[i]/total_mass;
    }

    for(int i = 0; i < nr_of_planets; i++){
        for(int j = 0; j<3; j++){
            system_of_planets[i].position[j] -= mass_center[j];
        }
    }
}

void solarsystem::remove_momentum(){
    double momentum[3]; double total_mass = 0;
    momentum[0] = 0;momentum[1] = 0;momentum[2] = 0;

    for(int i = 1; i < nr_of_planets; i++){
        for(int j = 0; j < 3; j++){
            momentum[j] += system_of_planets[i].velocity[j]*system_of_planets[i].mass;
        }
    }

    for(int i = 0; i <3 ; i++){
        system_of_planets[0].velocity[i] = -momentum[i]/system_of_planets[0].mass;
    }
}





void solarsystem::verlet_position(double t_step,int i){
    for(i; i < nr_of_planets; i++){
        system_of_planets[i].verlet_position(t_step);
    }
    return ;
}

void solarsystem::verlet_velocity(double t_step,int i){
    for(i; i < nr_of_planets; i++){
        system_of_planets[i].verlet_velocity(t_step);
    }
    return ;
}











void solarsystem::euler_position(double t_step,int i){
    for(i; i < nr_of_planets; i++){
        system_of_planets[i].verlet_position(t_step);
    }
    return ;
}

void solarsystem::euler_velocity(double t_step,int i){
    for(i; i < nr_of_planets; i++){
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

bool solarsystem::write_to_file(int i){
    for(i; i < nr_of_planets; i++){
        system_of_planets[i].write_to_file();
    }
    return true;
}