# -*- coding: utf-8 -*-
import re
import os
from subprocess import Popen, PIPE
from matplotlib.pyplot import *


#os.system("./solsys.exe 10 300 3000000 1")
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
	if "sun" in txtfile:
		plot(data["x"],data["y"],"r*",label=txtfile[:-4])
	else:	
		plot(data["x"],data["y"],"-",label=txtfile[:-4])
	#plot(data["t"],data["x"],label="x")


title("Full solar system for 300 years with n=3e6")
names = [	"Earth",
			"Jupitur",
			"Sun"]
legend(loc="best")
grid("on")
xlabel("X [au]")
ylabel("Y [au]")
show()
axis([-45,50,-45,45])
show()