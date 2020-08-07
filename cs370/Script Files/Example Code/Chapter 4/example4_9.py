#!/usr/bin/python3
## example4_9 (pp. 165-166 of Kiusalaas, 3rd Ed)
from numpy import zeros,array
from math import sin,log
from newtonRaphson2 import *

def f(x):
    f = zeros((len(x)),dtype=float64)
    f[0] = sin(x[0]) + x[1]**2 + log(x[2]) - 7.0
    f[1] = 3.0*x[0] + 2.0**x[1] - x[2]**3 + 1.0
    f[2] = x[0] + x[1] + x[2] - 5.0
    return f

x = array([1.0, 1.0, 1.0])

print (newtonRaphson2(f,x))
input ("\nPress return to exit")