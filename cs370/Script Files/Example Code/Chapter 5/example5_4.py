#!/usr/bin/python3
## example5_4 (pp. 192-193 of Kiusalaas, 3rd Ed)
from cubicSpline import curvatures, evalSpline
from LUdecomp3 import *
from polyFit import *
from numpy import array

xData = array([1.5, 1.9, 2.1, 2.4, 2.6, 3.1])
yData = array([1.0628, 1.3961, 1.5432, 1.7349, 1.8423, 2.0397])

# Only use three points for quadratic through x=2, degree m=2
#
xData_subset = array([1.9, 2.1, 2.4])
yData_subset= array([1.3961, 1.5432, 1.7349])
m=2

# Get coefficients over the three nearest points (to x = 2)

coeff = polyFit(xData_subset,yData_subset,m)

def poly_deriv(a_1,a_2,x):
    return a_1 + 2.0 *a_2 *x

def poly_second_deriv(a_2):
    return 2.0*a_2
    
x=2.0
print ('\nDerivative of poly at 2 = %7.4f\n'%poly_deriv(coeff[1],coeff[2],x))
print ('Second derivative of poly at 2 =%7.4f\n'%poly_second_deriv(coeff[2]))

# Get curvatures for spline on all subintervals (will only use second
# subinterval which contains x=2)

curv=curvatures(xData,yData)

def spline_deriv(k_1,k_2,x_1,x_2,y_1,y_2,x):
    return (k_1/6.0)* (3.0*(x-x_2)**2/(x_1-x_2)-(x_1-x_2)) \
           -(k_2/6.0)*(3.0*(x-x_1)**2/(x_1-x_2)-(x_1-x_2))+(y_1-y_2)/(x_1-x_2)

def spline_second_deriv(k_1,k_2,x_1,x_2,x):
    return k_1*(x-x_2)/(x_1-x_2) - k_2*(x-x_1)/(x_1-x_2) 

print ('Derivative of spline at 2 = %7.4f\n'%spline_deriv(curv[1],\
        curv[2],xData[1],xData[2],yData[1],yData[2],x))

print ('Second Derivative of spline at 2 = %7.4f\n'%spline_second_deriv(curv[1],\
        curv[2],xData[1],xData[2],x))
print ('Notice how first derivatives match well but second derivatives do not!')
print ('The higher the derivative, the lower expected precision (general rule).')
input("Press return to exit")