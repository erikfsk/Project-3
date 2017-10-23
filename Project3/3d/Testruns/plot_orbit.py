# -*- coding: utf-8 -*-
import re
import os
from subprocess import Popen, PIPE
from matplotlib.pyplot import *


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
		plot(data["x"],data["y"],"-")
	#plot(data["t"],data["x"],label="x")

names = ["Earth, v = $1.4\pi $ A.U.",
			"Earth, v = $1.8\pi $ A.U.",
			"Earth, v = $2\pi $ A.U.",
			"Earth, v = $2.4\pi $ A.U.",
			"Earth, v = $2.6\pi $ A.U.",
			"Earth, v = $3\pi $ A.U.",
			"Earth, v = $8.8 $ A.U.",
			"Earth, v = $8.9 $ A.U."]
legend(names,loc="best")
axis([-7,7,-7,7])
show()