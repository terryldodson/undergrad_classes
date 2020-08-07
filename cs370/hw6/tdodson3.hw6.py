#!/usr/bin/env python3
#
# Template for Problem 10 from Problem Set 3.2
#

#
# Needed to predict the thermal efficiency for the year 2000
# In order to do that I needed to create a polynomial
# fit graph, and based off of that I will be able to make my prediction

#
# Least Squares Curve Fitting
#
# Author: Terryl Dodson
# NetID: tdodson3
# Assignment #: Hwk 6 for COSC 370

from numpy import array,zeros
from polyFit import *
import pylab

#the definition for the evalPoly function
def evalPoly(c,x): # c stores coefficients for polynomial
    m = len(c) - 1 # (copied from polyFit module)
    p = c[m]
    for j in range(m):
        p = p*x + c[m-j-1]
    return p

#xData are the years and yData are the efficiencies
xData = array([1718, 1767, 1774, 1775, 1792, 1816, 1828, 1834, 1878, 1906]) 
yData = array([0.5, 0.8, 1.4, 2.7, 4.5, 7.5, 12.0, 17.0, 17.2, 23.0]) 

minsdev=float("inf")
minpoly=0
n=len(xData)
print('Degree  Stdev   2000P')

#iterates through values 1-5 (the polynomial degrees)
for m in range(1,6):   
    ys=zeros((n),dtype='float') # initialize y-coordinates for polynomial curve

    coeff = polyFit(xData, yData, m)        # get coefficients for n-th degree polynomial
    stdev = stdDev(coeff, xData, yData)     # get stdev of the error in the fit
    proj = evalPoly(coeff, 2000)            # found projection by passing it the coeff and the year 2000 
                                            # went based off of coeff that was returned from polyFit(depends on degree)

#
#   Year 2000 projections >= 100 or < 0 are meaniningless        
#
    # checks to see if stdev is less than minsdev
    # and if proj is between 0 and 100
    # if so, then it's able to compute and find the projection
    # if not, it skips the statement and prints 'not viable'
    if (stdev < minsdev) and proj < 100 and proj > 0 :

        print('{:3d}\t{:5.3f}\t{:5.3f}\t{:s}'.format(m,stdev,proj,'viable'))
        ys = evalPoly(coeff, xData) # get y-coordinates of polynomial using x-coordinates in xData array

        # plotting functions (creating the plot)
        # sets labels, titles, plots data points
        pylab.figure()
        pylab.xlabel("x")
        pylab.ylabel("Thermal Efficiency")
        my_title= 'Fit with poly degree = ' + str(m) + '; green dot is 2000 projection'
        pylab.title(my_title)
        pylab.xlim(1710, 2015)                  # x-axis values should range from 1710 to 2015
        pylab.plot(2000, proj, 'go')            # plot Year 2000 projection as a green dot
        pylab.plot(xData, yData, 'ro')          # plot the original data given in the xData and yData
                                                # arrays as red dots
        pylab.plot(xData, ys, 'b-')             # plot polynomial curve using xData and ys arrays
                                                # and make it blue.
        pylab.grid()
        fname='degree' + str(m) + 'fit.png'     # save figure to file rather than display
        pylab.savefig(fname)
    else :
        print('{:3d}\t{:5.3f}\t{:5.3f}\t{:s}'.format(m,stdev,proj,'not viable'))

#--------------------------------------------------------------------------------------
# Table to stdout should look similar to this...
#
# Degree Stdev   2000P
#   1 	 2.855	 34.986	    viable
#   2	 2.768	 45.419	    viable
#   3	 2.266	 -6.602	    not viable
#   4	 2.234	 112.391.   not viable
#   5	 2.496	 113.726.   not viable
#--------------------------------------------------------------------------------------