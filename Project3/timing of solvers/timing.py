# -*- coding: utf-8 -*-
import re
import os
from subprocess import Popen, PIPE
from matplotlib.pyplot import *

for i in range(1,7):
	for j in range(2):
		os.system("./solsys.exe 2 1 %s %s" % (10**i,j))