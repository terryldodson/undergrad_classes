#!/usr/bin/python3
##
## example4_3 (pp. 150-151, Kiusalaas 3rd Ed)
##

from math import tan
from numpy import arange,zeros
from rootsearch import *
from bisection import *
import pylab

def f(x): return x - tan(x)

a,b,dx = (0.0, 20.0, 0.01)
print ("The roots of f(x)= x-tan x on (0,20) using delta x = " + str(dx) + " :")
while 1:
    x1,x2 = rootsearch(f,a,b,dx)      # What is rootsearch doing here?
    if x1 != None:
        a = x2
        root = bisection(f,x1,x2,1)    # switch is set to 1 to avoid
        if root != None: print(root)   # singularities in f(x)
    else:                              # What epsilon is bisection using?
        print ("\nDone")
        n=20
        xData = arange(0,n,.1,dtype=float)
        n2=xData.size
        yData = zeros((n2),dtype=float)
        for j in range(0,n2):
          yData[j]=f(xData[j])

        pylab.xlabel("x")
        my_title= 'Plot of f(x)=x-tan x'
        pylab.text(2,100,r'Example 4.3, pp. 150-151')
        pylab.title(my_title)
        pylab.ylabel("f(x)")
        pylab.grid(True)
        pylab.plot(xData, yData, 'b')
        pylab.show()
        break

input("Press return to exit")