#!/usr/bin/python
## example6_7
from math import cos,sqrt,pi
from romberg import *

def f(x): return 2.0*(x**2)*cos(x**2)

print('  n             I           tol')
for k in range(2,16) :   # try several values of tol 
   tol=1.0*10**-k        # to see how many panels will be used
   I,n = romberg(f,0,sqrt(pi),tol)
   print('{0:3d} {1:20.16f} {2:7.2e}'.format(n,I,tol))

raw_input("\nPress return to exit")