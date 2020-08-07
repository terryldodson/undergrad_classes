#!/usr/bin/python3
## example5_5 on pp. 194-195 of Kiusalaas, 3rd Ed.
from numpy import array, float64
from gaussPivot import *
from polyFit import *
import pylab

xData = array([0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4])
yData = array([1.9934, 2.1465, 2.2129, 2.1790, \
                2.0683, 1.9448, 1.7655, 1.5891])
n=len(xData)
while 1:
    try:
        ys=zeros((n),dtype=float64)
        m = eval(input("\nDegree of polynomial ==> "))
        coeff = polyFit(xData,yData,m)
        for j in range(0,n):  # Need to evaluate poly at each
           for i in range(m+1):
             ys[j]+=coeff[i]*xData[j]**i

        if (m == 3):

           print ('\nFor cubic interpolant...')
           print ('\nDerivative at x = 0 : %7.4f'%coeff[1])
           deriv_at_1=coeff[1]+2.0*coeff[2]+3.0*coeff[3]
           print (  'Derivative at x = 1 : %7.4f\n'%deriv_at_1)

        print ("Coefficients are:\n",coeff)
        print ("Std. deviation =",stdDev(coeff,xData,yData))
        pylab.xlabel("x")
        my_title= 'Fit with poly degree = ' + str(m)
        pylab.text(0.2,1.8,r'Example 5.5, pp. 194-195')
        pylab.title(my_title)
        pylab.ylabel("P(x)")
        pylab.plot(xData, ys, 'b')
        pylab.plot(xData, yData, 'ro') # original data given in table
        pylab.grid()
        pylab.show()

    except SyntaxError: break
input("Finished. Press return to exit")