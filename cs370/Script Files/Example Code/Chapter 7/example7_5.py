#!/usr/bin/python3
## example7_5
from numpy import array,zeros,float64,exp
from printSoln import *
from run_kut4 import *

def F(x,y):
    F = zeros((1),dtype=float64)
    F[0] = 3.0*y[0]-4.0*exp(-x)
    return F

x = 0.0                 # Start of integration
xStop = 10.0            # End of integration
y = array([1.0])        # Initial values of {y}
h = 0.1                 # Step size
freq = 10               # Printout frequency

X,Y = integrate(F,x,y,xStop,h)
printSoln(X,Y,freq)
input("Press return to exit")