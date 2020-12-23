#!/usr/bin/env python3
#######################################################
# probs2_2.py
# 
# Scripts corresponding to problems 12, 17, and 18 on
# pages 79-82.
######################################################


#
# Choleski and Gaussian Elimination
#
# Author: Terryl Dodson
# NetID: tdodson3
# Assignment #: Hwk 3 for COSC 370

from numpy import array,zeros
from choleski import *
from gaussElimin import *

## problem2_2_12
######################################################
# 1. Populate k, W, and a below with the values from
#    problem 12 on page 79.
#
# Correct Output: 
# [ 1.66666667  2.66666667  2.66666667]
#
######################################################

#initially created a k array with 1
#initially created a W array with the given right-hand vector
#calculated W by given equations on textbook pdf (assuming W = 1)
#created a array filled with zeros (3 cols and 3 rows)
k = array(1,float)
W = array([2, 1, 2],float)
a = zeros((3,3))

#calculated k by given equations on textbook pdf (assuming k = 1)
a[0,0] = k + (2*k) + k + (2*k)
a[0,1] = -(k)
a[1,0] = -(k)
a[0,2] = -(2*k)
a[2,0] = -(2*k)
a[1,1] = k + k
a[1,2] = -(k)
a[2,1] = -(k)
a[2,2] = k + (2*k)

L = choleski(a)
x = choleskiSol(L,W)
print("Displacements are (in units of W/k):\n\n",x)
print("--------------------------------------------")

## problem2_2_17
######################################################
# 1. Populate a and b below with the values from
#    problem 17 on page 82.
#
# Correct Outputs:
# R = 5.0 ohms
# The currents are (in amps):
# [ 2.82926829 1.26829268 4.97560976]
# R = 10.0 ohms
# The currents are (in amps):
# [ 2.66666667 1.33333333 4.88888889]
# R = 20.0 ohms
# The currents are (in amps):
# [ 2.4516129 1.41935484 4.77419355]
#
######################################################

R = [5.0, 10.0, 20.0]
for r in R:
    #created a matrix of zeros (3 rows and 3 cols)
   a = zeros([3,3])

    #calculated matrix by referring to given equations on pdf
    #replaced R on pdf with r for each iteration of R
   a = array([ [50 + r, -r, -30], 
       [-r, 65 + r, -15], 
       [-30, -15, 45] ], dtype=float)
   
   #set b vector by referring to the right side of the equations
   b = [0, 0, 120]

   print("\nR =",r,"ohms")

   print("The currents are (in amps): \n", gaussElimin(a,b))
print("--------------------------------------------")

## problem2_2_18
######################################################
# 1. Populate a and b below with the values from
#    problem 18 on page 82.
#
# Correct Output:
# The loop currents are (in amps):
# [-4.18239492 -2.66455194 -2.71213323 -1.20856463]
######################################################

a = zeros([4,4])

#created a matrix by writing down the equations given on canvas
#distributed the numbers and simplified to like terms
#from there I created the array and set the b vector
#equal to the right side of the equation
a = array([ [80, -50, -30, 0], 
       [-50, 100, -10, -25], 
       [-30, -10, 65, -20], 
       [0, -25, -20, 100] ], dtype=float)
b = array([-120, 0, 0, 0], dtype=float)
print("The currents are (in amps):\n",gaussElimin(a,b))

input("Press return to exit")
