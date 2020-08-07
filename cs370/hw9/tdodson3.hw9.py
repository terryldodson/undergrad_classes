#!/usr/bin/env python3
# 
# Romberg Integration is a mixture of the trapezoidal rule
# and Richardson extrapolation. Used to obtain more of an 
# accurate approximation
#
# Romberg Integration continues to execute 
# until the difference between consecutive diagonal terms
# are sufficiently small
#
# Romberg Integration
#
# Author: Terryl Dodson
# NetID: tdodson3
# Assignment #: Hwk 9 for COSC 370
#
from romberg import *
from numpy import *
import matplotlib.pyplot as plt

#returned the integral function
def f(x):
  if x == 0: return 0
  else: return (x**4*exp(x)) / ((exp(x) - 1) ** 2)

u = arange(0,1.01,0.05)
print ("    u\t   g(u)")

#created list for y coordinates
gu = [] 

#using i to iterate through u
for i in u:
  if i == 0: g = 0.0
  else:
    #passed the function and the integral values to romberg
    #1/i since i is being used in the for loop
    #romberg returns integral (I) and number of panels (nPanels)
    I,nPanels = romberg(f,0,1/i)  

    #multiplied the final integral value (I) by u^3 which is i^3
    g = (i**3) * I                    
  print('{:6.2f}{:13.6f}'.format(i,g))

  #adding each g to the gu list
  gu.append(g)

#set title for the graph
plt.title("Problem 6.1.14")

#plots graph (blue solid line)
#sets x and y limits 
#sets x and y labels
plt.plot(u, gu, 'b-')
plt.xlim(0, 1.0)
plt.ylim(0, 0.35)
plt.xlabel("u")
plt.ylabel("g(u)")
plt.show()
