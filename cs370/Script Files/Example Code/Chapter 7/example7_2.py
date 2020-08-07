#!/usr/bin/env python3
## example7_2 (pp. 251-252)
from numpy import array, zeros, exp
from printSoln import *
from euler import *
import matplotlib.pyplot as plt

def F(x,y):
    F = zeros(2)
    F[0] = y[1]
    F[1] = -0.1*y[1] - x 
    return F

x = 0.0               # Start of integration                 
xStop = 2.0           # End of integration                      
y = array([0.0, 1.0]) # Initial values of {y}  
h = 0.0025              # Step size
freq = 1              # Printout frequency 
X,Y     = integrate(F,x,y,xStop,h)
XME,YME = modified_euler_method(F,x,y,xStop,h)
yExact= 100.0*X - 5.0*X**2 + 990.0*(exp(-0.1*X) - 1.0)
plt.plot(X,Y[:,0],'o',X,yExact,'-')
plt.grid(True)
plt.xlabel('x'); plt.ylabel('y')
plt.title('Euler\'s Method')
plt.legend(('Numerical','Exact'),loc=0)
plt.show()
input("\nPress return to exit")
plt.title('Modified and Regular Euler\'s Method')
plt.plot(X,Y[:,0],'o',X,YME[:,0],'d',X,yExact,'-')
plt.legend(('Euler','Mod Euler','Exact'),loc=0)
plt.grid(True)
plt.xlabel('x'); plt.ylabel('y')
plt.title('Modified and Regular Euler\'s Method')
plt.show()
input("\nPress return to exit")