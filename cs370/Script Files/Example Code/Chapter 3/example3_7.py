#!/usr/bin/python3
## Example 3.7 on pp.123-124 of Kiusalaas, #rd Ed.
## example3_7

from numpy import array,float64,zeros,arange
from cubicSpline import *
import matplotlib.pyplot as plt

xData = array([1,2,3,4,5],dtype=float64)
yData = array([0,1,0,1,0],dtype=float64)

k = curvatures(xData,yData)
print(k)
x=arange(1.,5.1,0.1)
n=len(x)
y=zeros((n),dtype=float64)
for i in range(0,n):
    y[i]=evalSpline(xData,yData,k,x[i])
    
plt.xlabel("x")
plt.ylabel("y")
plt.title("Example 3.7 on pp. 123-124")

plt.plot(x, y, 'b')
plt.show()