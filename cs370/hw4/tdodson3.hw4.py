#!/usr/bin/env python3
# prob2-3-19 (hwk #4)
#
#  Problem 2.3.19 (pg. 101)
#
#  1) Implement the Ax(v) function below so that it will initialize
#     and return the matrix-vector product Ax, where A is given at
#     the top of page 101 in the textbook.
#  
#  2) Use the provided conjGrad.py module to solve the system described
#     in problem #19 (uncomment and fill in the '??' lines and provide
#     the requested loop and final error difference).
#
# The correct solution is:
#
# [ 21.42857143 38.39285714  57.14285714   47.32142857   75.
#   90.17857143 92.85714286 124.10714286 128.57142857]
#
########################################################################


#
# Conjugate Gradient Method
#
# Author: Terryl Dodson
# NetID: tdodson3
# Assignment #: Hwk 4 for COSC 370

from numpy import zeros,array,linalg
from conjGrad import *

# Refer to pg. 101 for what the matrix Ax should be

def Ax(v):
  Ax = zeros((9))*1.0

#calculated matrix Ax for conjGrad function
  Ax[0] = -4.0 * v[0] + v[1] + v[3]
  Ax[1] = -4.0 * v[1] + v[0] + v[2] + v[4]
  Ax[2] = -4.0 * v[2] + v[1] + v[5]
  Ax[3] = -4.0 * v[3] + v[0] + v[4] + v[6]
  Ax[4] = -4.0 * v[4] + v[3] + v[1] + v[5] + v[7]
  Ax[5] = -4.0 * v[5] + v[4] + v[2] + v[8]
  Ax[6] = -4.0 * v[6] + v[3] + v[7]
  Ax[7] = -4.0 * v[7] + v[6] + v[4] + v[8]
  Ax[8] = -4.0 * v[8] + v[7] + v[5]

  return Ax

b = array([0,0,100,0,0,100,200,200,300])*(-1.0)
x = zeros((9))*1.0
tol = 1e-06

#referred back to the function and passed it necessary parameters 
#A matrix, x matrix, the b vector and the tolerance
#maintained solution for 1e-06 tolerance so it can be used 
#for the error (comparing with 1e-16)
s1,numIter = conjGrad(Ax, x, b, tol)
print("\nThe solution is:\n",s1)
print("\nNumber of iterations =",numIter, "using Tol: ", 1e-06)

print("\n CG Convergence Test")
print("Iterations   Tolerance")

#created a loop to find the number of iterations for each tolerance 
#and printed them out
tolList = [1.e-02, 1.e-04, 1.e-06, 1.e-08, 1.e-10, 1.e-12, 1.e-14, 1.e-16]
for tol in tolList:
    x = zeros((9))*1.0
    s2,numIter = conjGrad(Ax, x, b, tol)
    print("   ", numIter, "        ", tol)

#used the solution vector (s2) for the tolerance of 1.e-16
#and used s1 (solution vector for tolerance 1.e-6) and 
#to calculate the error between the two vectors
err = linalg.norm(s1-s2)
print("\nError between vectors obtained with tol=1e-06 and tol=1e-16: ", err,"\n")