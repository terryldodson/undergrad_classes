#!/usr/bin/python3
## example3_4 on pp. 114,115 of Kiusalaaus 3rd Ed.

import numpy as np
from math import pi,cos
from newtonPoly import *

xData = np.array([0.15,2.3,3.15,4.85,6.25,7.95])
yData = np.array([4.79867,4.49013,4.2243,3.47313,2.66674,1.51909])

a = coeffts(xData,yData)

print (" x    yInterp   yExact")
print ("-----------------------")

for x in np.arange(0.0,10.1,0.25):
    y = evalPoly(a,xData,x)
    yExact = 4.8*cos(pi*x/20.0)
    print ('{:3.1f} {:9.5f} {:9.5f}'.format(x,y,yExact))
input("Press return to exit...")