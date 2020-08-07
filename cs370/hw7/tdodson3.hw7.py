#!/usr/bin/env python3
#
# Template for Problem 27 from Problem Set 4.1
#
# In this assignment we were supposed to find the minimum
# minimum trajectory value and the corresponding angle theta to the satellite.
# By doing that, we used the parameters R, theta, C, e, and alpha
# R  and theta (x, y) are the coordinates of the satellite (destination) 
# C, e and alpha are constants that were given (which were initial guesses 
# in order for the equation to equal 0)
#
# Determining Trajectory and Angle for Orbiting Satellite
# using NewtonRaphson 2
#
# Author: Terryl Dodson
# NetID: tdodson3
# Assignment #: Hwk 7 for COSC 370

from newtonRaphson2 import *
from math import sin, pi
import numpy as np
import matplotlib.pyplot as plt

# The trajectory of a satellite orbiting the earth is given by the equation
#
# R = C/(1+e*sin(theta + alpha)), which can also be written as
# R - C/(1+e*sin(theta + alpha)) = 0 (in order to exploit rootfinding methods).
#
#  The Newton-Raphson method can be used to solve a nonlinear system of 
#  3 trajectory equations using the given data. The unknowns are stored in
#  the vector x = [ C, e, alpha], and the initial guess is [6800, 0.5, 0].
#
#   In solving the resulting nonlinear system for x, the derived constants 
#   can be used to determine the minimum trajectory and angle at which it
#   occurs. The trajectory equation of the satellite's orbit as well as
#   the point at which minimum trajectory occurs can be plotted.
#
# Create the vector-valued function F(x) whose root defines a system of 3 trajectory 
# equations (using given data); use radians for all angles.
#
# Let x[0]=C, x[1]=e, and x[2]=alpha, and 30 degrees be represented by pi/6.
# Then, we seek a vector x that solves R- x[0]]/(1+x[1]*sin(theta + x[2])) = 0, [Eqn1]
# for each data pair given above.
#

# function returns F which contains the three nonlinear equations 
# equation was given, only difference in equations are the theta and R values
# used the given R, theta data pairs: (6870km, -30deg),(6728km, 0deg), (6615km, 30deg)
#
def F(x):
    F = zeros((len(x)), dtype=float64)
    F[0] = (x[0] / (1 + x[1] * sin((-pi/6) + x[2]))) - 6870
    F[1] = (x[0] / (1 + x[1] * sin((0) + x[2]))) - 6728
    F[2] = (x[0] / (1 + x[1] * sin((pi/6) + x[2]))) - 6615
    return F

# Initial guesses
x = np.array([6800, 0.5, 0]) 

# called the N-R function passing it the function F and
# the initial values (C, e, alpha)
# returns constants that causes the above nonlinear equations
# to equal 0
x = newtonRaphson2(F,x)

# Print the solution vector x from N-R
print()
np.set_printoptions(precision = 3)
print('[ C  e  alpha] = ' + np.array_str(x))

# used given equations to calculate minTheta and minR
# substituted constants with updated x values
minTheta = (pi/2.0 - x[2]) * 180.0 / pi
minR = x[0]/(1+x[1]) 

# Print minimum trajectory results
print('Minimum trajectory = %.3f km' % minR)
print('Angle at which minimum trajectory occurs = %.3f degrees' % minTheta)
print()

# Create arrays of points spaced every 0.01 radians around the satellite orbit
# (theta) and their respective trajectories (R)
theta = np.arange(0, 2*pi, 0.01)            # theta and R are arrays now
R = x[0] / (1 + x[1]*np.sin(theta + x[2]))

# Plot orbit and minimum trajectory point

ax = plt.subplot(111, polar = True)
ax.plot(theta, R, color = 'r', linewidth = 2, label = 'Path')
ax.plot(minTheta, minR, 'bo', label = 'Min')
ax.legend(numpoints = 1)
ax.grid(True)
ax.set_title("Satellite path")
plt.show()