#!/usr/bin/python3

## problem set 2.1 (#16) on p. 57

from numpy import array,dot,linalg,float64
from choleski import *

def solve(a,b):
   n = len(b)

   # Solution of [L]{y} = {b}
   for k in range(0,n):
      b[k] = (b[k] - dot(a[k,0:k],b[0:k]))/a[k,k]

   # Solution of [L_transpose]{x} = {y}
   for k in range(n-1,-1,-1):
      b[k] = (b[k] - dot(a[k+1:n,k],b[k+1:n]))/a[k,k]

A = array([[ 4,-2, 2], [-2, 2,-4], [ 2,-4,11]],dtype=float)
b = array([6,-10,27],dtype=float)
A_old=A.copy()
b_old=b.copy()
L = choleski(A) # recall that original matrix A is overwritten
solve(L,b)      # original b vector is destroyed
print('Solution vector x =', b, 'and the error =',linalg.norm(dot(A_old,b)-b_old))
input('\nPress return to exit')