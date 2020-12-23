#!/usr/bin/env python3
#
# Template for COSC 370 Hwk #8
#
# Finite Difference Approximation & Polynomial Interpolation
#
# Author: Terryl Dodson
# NetID: tdodson3
# Assignment #: Hwk 8 for COSC 370

#
import numpy as np
from numpy import round, array, polyfit, polyder, polyval
#
# Problem 5.1.9
#
# Problem: Need to find the first derivative 
# given the x and y values for the function
#
# Method: Used CDA (central difference approximation)
# h1 substitued for h in the original equation
#
print("Problem 5.1.9\n=============")
#
#
data9 = { 0.0: 0.0, 0.1: 0.078348, 0.2: 0.138910, 0.3: 0.192916, 0.4: 0.244981 }

#
# We want to approximate f'(0.2) using two different values of h (=0.2, 0.1)
#
# Calculated first CDA using h=0.2
h1 = 0.2
x = 0.2
den = 2*h1

centralApprox1 = ((data9[x+h1]) - data9[x-h1]) / den
print("Central FDA Approximation (h = 0.2): %f" % centralApprox1)

#
# halfed h1 which set h2 to 0.1
# rounded value to reassure proper key
# will be selected
# Calculated CDA using h=0.1

h2 = h1 / 2.0
den1 = 2*h2
centralApprox2 = ((data9[round(x+h2, decimals=1)]) - data9[round(x-h2, decimals=1)]) / den1

# Recalculated approximation using Richard Extrapolation
# in order to obtain a more accurate approximation
#
# Caclulated approximation by using approximations 
# from CDA

p = 2.0
num = ((2**p) * centralApprox2)-centralApprox1
den = (2**p) - 1
richardsonExtrap = num/den
print("Richardson Extrapolation (h2 = h1 / 2, p = 2): %f" % richardsonExtrap)


#
# Problem 5.1.11
#
# Problem: Need to find the first and second
# derivative of the cubic spline

# Method: Used polynomial interpolation to
# find derivatives
#
print("\nProblem 5.1.11\n==============")

xData = array([-2.2, -0.3, 0.8, 1.9])
yData = array([15.18, 10.962, 1.92, -2.04])

# used polyfit to obtain the coefficients 
# for the polynomial 
p = np.polyfit(xData, yData, 3)

# compute the first and second derivative functions using the coefficients found
# first argument are coefficients, second is the order of the derivative
d1 = np.polyder(p, 1)
d2 = np.polyder(p, 2)

#
# coefficients of actual polynomial
pActual = array([1, -0.3, -8.56, 8.448])

# compute the first and second derivative functions using the actual coefficients that was given
# first argument are coefficients, second is the order of the derivative
d1Actual = np.polyder(pActual, 1)
d2Actual = np.polyder(pActual, 2)

# evaluated first derivative of polynomial at x=0
# evaluated first derivative of acutal polynomial given at x=0
# first argument are the first derivative functions
# second argument is value of x (0)
fd =  polyval(d1, 0)
fdActual = polyval(d1Actual, 0)

print("Interpolated f'(0): %f" % fd)
print("Actual f'(0): %f" % fdActual)
print("Error: %f\n" % (fdActual - fd))

# evaluated second derivative of polynomial at x=0
# evaluated second derivative of acutal polynomial given at x=0
# first argument are the second derivative functions
# second argument is value of x (0)
sd =  polyval(d2, 0)
sdActual =  polyval(d2Actual, 0)

print("Interpolated f''(0): %f" % sd)
print("Actual f''(0): %f" % sdActual)
print("Error: %f" % (sdActual - sd))
