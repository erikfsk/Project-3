#include "solarsystem.h"

solarsystem::solarsystem(planet* planets_input, int nr_of_planets_input)
{  
    nr_of_planets = nr_of_planets_input;
    system_of_planets = planets_input;
}






void solarsystem::solve_verlet(int n, double t_step){
    //Setting mass center and giving system 0 momentum
    mass_center();
    remove_momentum();

    // the algorithm for verlet
    Acceleration(); 
    clear_file();
    

    for(int i = 1; i<n ; i++){
        verlet_position(t_step,0);          // 0 means all the planets + the sun
        Acceleration_reset();
        Acceleration();
        verlet_velocity(t_step,0);          // 0 means all the planets + the sun
        if(i % 12 == 0){
            write_to_file(0);               // 0 means all the planets + the sun
        }

    }
}

void solarsystem::solve_euler_fixed_sun(int n, double t_step){
    clear_file();
    system_of_planets[0].write_to_file();   //the sun is fixed at 0 0 0 dont need to write every loop
    

    for(int i = 1; i<n ; i++){
        Acceleration_reset();
        Acceleration_fixed_sun();
        euler_position(t_step,1);           // 1 means all the planets
        euler_velocity(t_step,1);           // 1 means all the planets
        if(i % 12 == 0){
            write_to_file(1);               // 1 means all the planets
        }
    }
}

void solarsystem::solve_verlet_fixed_sun(int n, double t_step){
    Acceleration_fixed_sun();
    clear_file();
    system_of_planets[0].write_to_file();   //the sun is fixed at 0 0 0 dont need to write every loop
    

    for(int i = 1; i<n ; i++){              
        verlet_position(t_step,1);          // 1 means all the planets
        Acceleration_reset();
        Acceleration_fixed_sun();
        verlet_velocity(t_step,1);          // 1 means all the planets
        if(i % 12 == 0){
            write_to_file(1);               // 1 means all the planets
        }

    }
}

void solarsystem::solve_verlet_only_from_sun(int n, double t_step){
    /*
    This solver is only for testing different scenarios at once
    It is used to look at the escape velocity of the earth. 
    It simulate many planet-sun systems with a fixed sun at the same time. 
    */
    Acceleration_only_from_sun();           
    clear_file();
    system_of_planets[0].write_to_file();   //the sun is fixed at 0 0 0 dont need to write every loop


    for(int i = 1; i<n ; i++){
        verlet_position(t_step,1);          // 1 means all the planets
        Acceleration_reset();
        Acceleration_only_from_sun();
        verlet_velocity(t_step,1);          // 1 means all the planets
        if(i % 12 == 0){
            write_to_file(1);               // 1 means all the planets
        }
    }
}



void solarsystem::solve_verlet_fixed_sun_perihelion(int n, double t_step){
    Acceleration_fixed_sun_perihelion();
    clear_file();

    //variabels for finding local minimum of the radius for mercury
    double old_position[3];old_position[0] = 0; old_position[1] = 0; old_position[2]= 0;
    double position[3];position[0] = 0; position[1] = 0; position[2]= 0;
    double new_position[3];
    new_position[0] = system_of_planets[1].position[0];
    new_position[1] = system_of_planets[1].position[1];
    new_position[2] = system_of_planets[1].position[2];


    system_of_planets[0].write_to_file();       //sun is fixed
    for(int i = 1; i<n ; i++){
        verlet_position(t_step,1);              // 1 means all the planets
        Acceleration_reset();
        Acceleration_fixed_sun_perihelion();
        verlet_velocity(t_step,1);              // 1 means all the planets


        //FROM HERE... 
        for(int i = 0; i < 3; i++){
            old_position[i] = position[i];
            position[i] = new_position[i];
            new_position[i] = system_of_planets[1].position[i];
        }
        double r_old =sqrt(old_position[0]*old_position[0] +old_position[1]*old_position[1] +old_position[2]*old_position[2]);
        double r = sqrt(position[0]*position[0] + position[1]*position[1] +position[2]*position[2]);
        double r_new =sqrt(new_position[0]*new_position[0] + new_position[1]*new_position[1] + new_position[2]*new_position[2]);
        if(r_old > r and r < r_new){
            write_to_file(1);
        }
        //UNTIL HERE
        //is only so i only write to file the local minimums
        //          of the radius of the orbit of mercury

    }
}





void solarsystem::Acceleration(){
    //loops over all the planets and calculate the acceleration between them
    for(int i=0; i<nr_of_planets-1; i++){
        for(int j=i+1; j<nr_of_planets; j++){
            system_of_planets[i].Acceleration(system_of_planets[j],1);
            system_of_planets[j].Acceleration(system_of_planets[i],1);
        }
    } 
}


void solarsystem::Acceleration_reset(){
    //reset the acceleration for all planets
    for(int i = 0; i < nr_of_planets; i++){
        system_of_planets[i].Acceleration_reset();
    }
}


void solarsystem::Acceleration_fixed_sun(){
    //loops over all the planets and calculate the acceleration between them
    //except the sun's acceleration is not calculated. Because that acceleration is not used
    //if this method is called
    for(int i=0; i<nr_of_planets-1; i++){
        for(int j=i+1; j<nr_of_planets; j++){
            if(i != 0){
                system_of_planets[i].Acceleration(system_of_planets[j],1);    
            }
            system_of_planets[j].Acceleration(system_of_planets[i],1);
        }
    }
}


void solarsystem::Acceleration_only_from_sun(){
    //as said in the solver. Here only the acceleration from the sun is used
    for(int i=1; i<nr_of_planets; i++){
        system_of_planets[i].Acceleration(system_of_planets[0],1);    
    }
}

void solarsystem::Acceleration_fixed_sun_perihelion(){
    //this function is used for the perihelion assignment and could have been shorten down
    //since we know that it is only and mercury here. But this way it can be more planets
    for(int i=0; i<nr_of_planets-1; i++){
        for(int j=i+1; j<nr_of_planets; j++){
            if(i != 0){
                system_of_planets[i].Acceleration_perihelion(system_of_planets[j],1);    
            }
            system_of_planets[j].Acceleration_perihelion(system_of_planets[i],1);
        }
    }
}



void solarsystem::mass_center(){
    double mass_center[3]; double total_mass = 0;
    mass_center[0] = 0;mass_center[1] = 0;mass_center[2] = 0;


    //calculate mass center*mass_total
    for(int i = 0; i < nr_of_planets; i++){
        for(int j = 0; j < 3; j++){
            mass_center[j] += system_of_planets[i].position[j]*system_of_planets[i].mass;
        }
        total_mass += system_of_planets[i].mass;
    }

    //calculate mass center for x y and z
    for(int i = 0; i <3 ; i++){
        mass_center[i] = mass_center[i]/total_mass;
    }

    //updating the positions so that origo is the mass center
    for(int i = 0; i < nr_of_planets; i++){
        for(int j = 0; j<3; j++){
            system_of_planets[i].position[j] -= mass_center[j];
        }
    }
}

void solarsystem::remove_momentum(){
    double momentum[3]; double total_mass = 0;
    momentum[0] = 0;momentum[1] = 0;momentum[2] = 0;

    //calculating total momentum
    for(int i = 1; i < nr_of_planets; i++){
        for(int j = 0; j < 3; j++){
            momentum[j] += system_of_planets[i].velocity[j]*system_of_planets[i].mass;
        }
    }

    //giving the sun the opposite momentum so the momentum is 0 and 
    //the solarsystem does not drift 
    for(int i = 0; i <3 ; i++){
        system_of_planets[0].velocity[i] = -momentum[i]/system_of_planets[0].mass;
    }
}





void solarsystem::verlet_position(double t_step,int i){
    //update all the positions for the planets verlet method
    for(i; i < nr_of_planets; i++){
        system_of_planets[i].verlet_position(t_step);
    }
}

void solarsystem::verlet_velocity(double t_step,int i){
    //update all the velocitys for the planets verlet method
    for(i; i < nr_of_planets; i++){
        system_of_planets[i].verlet_velocity(t_step);
    }
}











void solarsystem::euler_position(double t_step,int i){
    //update all the positions for the planets euler method
    for(i; i < nr_of_planets; i++){
        system_of_planets[i].verlet_position(t_step);
    }
}

void solarsystem::euler_velocity(double t_step,int i){
    //update all the velocitys for the planets euler method
    for(i; i < nr_of_planets; i++){
        system_of_planets[i].verlet_velocity(t_step);
    }
}













bool solarsystem::clear_file(){
    //clearing the files for all the planets
    for(int i = 0; i < nr_of_planets; i++){
        system_of_planets[i].clear_file();
    }
    return true;
}

bool solarsystem::write_to_file(int i){
    //writing positions to the files for i of the planets
    for(i; i < nr_of_planets; i++){
        system_of_planets[i].write_to_file();
    }
    return true;
}