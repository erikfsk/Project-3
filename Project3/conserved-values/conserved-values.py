# -*- coding: utf-8 -*-
import re
import os
from subprocess import Popen, PIPE
from matplotlib.pyplot import *
from numpy import *

output = Popen(["ls"], stdout=PIPE).communicate()[0]
txtfiles = re.findall(".*\.txt",output,re.IGNORECASE)

print txtfiles
for txtfile in txtfiles:
    with open(txtfile,"r") as infile:
        data = {}
        identifiers = infile.readline().split()
        for identifier in identifiers:
            data[identifier] = []

        lines = infile.readlines()
        for line in lines: 
            values = line.split()
            for identifier,value in zip(identifiers,values):
                data[identifier].append(float(value))

        for key in data.keys():
            data[key] = array(data[key])

        print data.keys()
        title(txtfile[16:-4])
        plot(data["kin"]-data["kin"][0],"-",label="Diff. kinetic Energy")
        plot(data["pot"]-data["pot"][0],"-",label="Diff. potential Energy")
        legend(loc="best")
        xlabel("iteration [n]")
        ylabel("$E_i - E_0$")
        grid("on")
        show()  


        title(txtfile[16:-4])
        plot((sqrt(data["vx"]**2+data["vy"]**2)-\
            sqrt(data["vx"][0]**2+data["vy"][0]**2)),"-", label="Diff. momentum")
        legend(loc="best")
        xlabel("iteration [n]")
        ylabel("p$_i -$p$_0$ [kg$\cdot$m/s]")
        grid("on")
        show()

        title(txtfile[16:-4])
        ang_momentum_x = data["vx"] * data["y"] -data["vy"] * data["x"]
        ang_momentum = sqrt(ang_momentum_x**2)
        plot((ang_momentum - ang_momentum[0]),"-", label="Diff. angular momentum")
        legend(loc="best")
        xlabel("iteration [n]")
        ylabel("$\\tau_i - \\tau_0$ [$Nms$]")
        grid("on")
        show()













"""
for i in range(4,5):
    for j in range(2):
        os.system("./solsys.exe 2 1 %s %s" % (10**i,j))



#as input for planet earth! 
if(2 <= nr_planets){
        system_of_planets[1] = planet("earth2.txt"                           //filename
                                        ,4*M_PI*M_PI*mass_earth/mass_sun    //Mass_ratio to sun
                                        ,1                                  //Position x
                                        ,0                                  //Position y
                                        ,0                                  //Position z
                                        ,0                                  //Velocity x
                                        ,2*M_PI                             //Velocity y
                                        ,0                                  //Velocity z
                                        );
    }


#In the loop of the solarsystem solver
double kinetic = system_of_planets[1].KineticEnergy();
        double potential = system_of_planets[1].PotentialEnergy(system_of_planets[0],1,1);
        double* velo = system_of_planets[1].velocity;
        double* pos = system_of_planets[1].position;
        cout << kinetic << " " << potential << " ";
        cout << velo[0] << " " << velo[1] << " " << velo[2] << " ";
        cout << pos[0] << " " << pos[1] << " " << pos[2] << endl;
"""