# -*- coding: utf-8 -*-
import re
import os
from subprocess import Popen, PIPE
from matplotlib.pyplot import *
from numpy import *
os.system("./standard.exe 1000")
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
	print data.keys()
	plot(data["x"],data["y"])
	#plot(data["t"],data["x"],label="x")

plot(0,0,"r*",label="Sun")
legend(["Euler - Earth","Verlet - Earth","Fixed - Sun "],loc="best")
xlabel("X [au]")
ylabel("Y [au]")
grid("on")
savefig("earth-sun.pdf")
show()


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
	print data.keys()
	for key in data.keys():
		data[key] = array(data[key])
	plot(sqrt(data["x"]**2 + data["y"]**2 -1))
	#plot(data["t"],data["x"],label="x")

legend(["Euler - Earth","Verlet - Earth"],loc="best")
xlabel("Iteration [n]")
ylabel("Error [au]")
savefig("earth-sun-error.pdf")
grid("on")
show()