#!/usr/bin/python3

## example2_11 (p.68)

from numpy import array,ones,zeros,diagonal,linalg,dot
from LUdecomp3 import *
import os

os.system('clear')  # This is handy for clearing the console screen

d = ones((5))*2.0
c = ones((4))*(-1.0)
b = array([5.0, -5.0, 4.0, -5.0, 5.0])
b_old = b.copy()
e = c.copy()
A=zeros((5,5),dtype=float)
for k in range(0,5):
    A[k,k]=d[k]
    if (k > 0): 
       A[k,k-1]=c[k-1]
       A[k-1,k]=c[k-1]
c,d,e = LUdecomp3(c,d,e)

print("\nA =\n",A)
print("\nb =\n",b)
x = LUsolve3(c,d,e,b)
print ("\nx = ",x)
print ("Solution vector x =", x)
print (' and the error =',linalg.norm(dot(A,x)-b))
print ('Oops! We forgot to make a copy of b; the correct error =',linalg.norm(dot(A,x)-b_old))
input("\nPress return to exit")