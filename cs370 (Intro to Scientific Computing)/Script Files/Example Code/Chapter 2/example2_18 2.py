#!/usr/bin/python3
## example2_18 on p. 97 of Kiusalaas, 3rd Ed.
from numpy import zeros,float64,sqrt
from conjGrad import *

def Ax(v):   # define Matrix-vector multiplication function
    n = len(v)
    Ax = zeros((n),dtype=float64)
    Ax[0] = 2.0*v[0] - v[1]+v[n-1]
    Ax[1:n-1] = -v[0:n-2] + 2.0*v[1:n-1] -v [2:n]
    Ax[n-1] = -v[n-2] + 2.0*v[n-1] + v[0]
    return Ax

n = eval(input("Number of equations ==> "))
b = zeros((n),dtype=float64)
b[n-1] = 1.0
x = zeros((n),dtype=float64)
x,numIter = conjGrad(Ax,x,b,1.0e-2)
print ("\nThe solution is:\n",x)
print ("\nNumber of iterations =",numIter)
input("\nPress return to exit")
    