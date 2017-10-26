# -*- coding: utf-8 -*-
from matplotlib.pyplot import *
from numpy import *

def get_data(txtfile):
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
		for identifier in identifiers:
			data[identifier] = array(data[identifier])
	return data



planet = get_data("mercury_8_.txt")
planet2 = get_data("mercury_8.txt")
#plot(sqrt(planet["x"]*planet["x"] + planet["y"]*planet["y"]),"r-",label="r")
plot(arctan2(planet["y"],planet["x"])*(360/(2*pi))*3600,"g-",label="arctan(y/x)")
plot(arctan2(planet2["y"],planet2["x"])*(360/(2*pi))*3600,"g-",label="arctan(y/x)")
legend(loc="best")
show()
"""
minimum_x_values = []
minimum_y_values = []
for i in range(1,len(planet["x"])-1):
	x_old = planet["x"][i-1]
	y_old = planet["y"][i-1]
	x_ = planet["x"][i]
	y_ = planet["y"][i]
	x_new = planet["x"][i+1]
	y_new = planet["y"][i+1]

	r_old = sqrt(x_old*x_old + y_old*y_old)
	r_ = sqrt(x_*x_ + y_*y_)
	r_new = sqrt(x_new*x_new + y_new*y_new)
	if (r_old > r_) and (r_ < r_new):
		minimum_y_values.append(y_)
		minimum_x_values.append(x_)


minimum_x_values = array(minimum_x_values)
minimum_y_values = array(minimum_y_values)

plot(sqrt(minimum_x_values*minimum_x_values + minimum_y_values*minimum_y_values))
show()



"""