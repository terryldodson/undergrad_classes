#!/usr/bin/env python3
#
# Template for Problems 17 and 19 in Problem Set 3.1 (Hwk #5)
#

#
# Interpolation using Cubic Splines
#
# Author: Terryl Dodson
# NetID: tdodson3
# Assignment #: Hwk 5 for COSC 370

# Problem 17 (use log-log scale)
#
from cubicSpline import *
from numpy import array,log10
xData = array([0.2, 2.0, 20.0, 200.0, 2000.0, 20000.0])
yData = array([103.0, 13.9, 2.72, 0.8, 0.401, 0.433])
Re_array= array([5.0, 50.0, 500.0, 5000.0])
logxData = log10(xData)
logyData = log10(yData)

#generated curvatures by passing necessary arguments
#made sure to use logxData and logyData since it says 
#we need to use logscale below
k = curvatures(logxData, logyData)

print('\nInterpolating for drag coefficients (C_D)...\n    Re\tC_D')

#created loop to evaluate spline
#passed necessary arguments
#made sure to log10 Re since everything else is logged
#this is what tricked me up
#I didn't realize that Re was logged and that I had to log it 
for Re in Re_array:
    logy = evalSpline(logxData, logyData, k, log10(Re))
    # Use this print statement in your loop ...
    print('{:6.1f}\t{:5.3f}'.format(Re,10.0**logy)) # Re is an element from
                                                  # the RE_array
                                                  # logy is the y-coordinate
                                                  # corresp. to log10(Re)
#
# Problem 19 (do not use log-log scale)
#
tData = array([0.0, 21.1, 37.8, 54.4, 71.1, 87.8, 100.0])
mData = array([1.79, 1.13, 0.696, 0.519, 0.338, 0.321, 0.296]) 
T_array = array([10.0, 30.0, 60.0, 90.0])

#generated curvatures by passing necessary arguments
#no need to log scale
k = curvatures(tData, mData)

print('\nInterpolating for kinematic viscosity (CMu_k)...\n    T\tMu_k')

#created loop to evaluate spline
#passed necessary arguments
for temp in T_array:
    y = evalSpline(tData, mData, k, temp)
    # Use this print statement in your loop ...
    print('{:6.1f}\t{:5.3f}'.format(temp,y)) # temp is an element from
                                           # T_array
