# -*- coding: utf-8 -*-
import re
import os
from subprocess import Popen, PIPE
from matplotlib.pyplot import *


output = Popen(["ls"], stdout=PIPE).communicate()[0]
txtfiles = re.findall(".*\.txt",output,re.IGNORECASE)


first_picture = txtfiles[2:5:2] + txtfiles[7::2]
second_picture = txtfiles[1:5:2] + txtfiles[6::2]


print first_picture
print second_picture



for txtfile in first_picture:
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
		
	plot(data["x"],data["y"],"-")

plot(0,0,"r*")
names = [	"Earth, m$_j$ = 100m$_{j_0}$",
			"Earth, m$_j$ = 1100m$_{j_0}$",
			"Jupitur, m$_j$ = 100m$_{j_0}$",
			"Jupitur, m$_j$ = 1100m$_{j_0}$",
			"Sun"]
legend(names,loc="best")
grid("on")
xlabel("X [au]")
ylabel("Y [au]")
axis([-7,14,-7,7])
show()



for txtfile in second_picture:
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
	if "sun" in txtfile:
		plot(data["x"],data["y"],"r*",label=txtfile[:-4])
	else:	
		plot(data["x"],data["y"],"-")
	#plot(data["t"],data["x"],label="x")

plot(0,0,"r*")
names = [	"Earth, m$_j$ = 10m$_{j_0}$ ",
			"Earth, m$_j$ = 1000m$_{j_0}$",
			"Jupitur, m$_j$ = 10m$_{j_0}$",
			"Jupitur, m$_j$ = 1000m$_{j_0}$",
			"Sun"]
legend(names,loc="best")
grid("on")
xlabel("X [au]")
ylabel("Y [au]")
axis([-7,14,-7,7])
show()

print txtfiles[0::5]
for txtfile in txtfiles[0::5]:
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
	if "sun" in txtfile:
		plot(data["x"],data["y"],"r*",label=txtfile[:-4])
	else:	
		plot(data["x"],data["y"],"-")
	#plot(data["t"],data["x"],label="x")

plot(0,0,"r*")
names = [	"Earth",
			"Jupitur",
			"Sun"]
legend(names,loc="best")
grid("on")
xlabel("X [au]")
ylabel("Y [au]")
axis([-7,14,-7,7])
show()

