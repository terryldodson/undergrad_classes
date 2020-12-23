#!/usr/bin/python3

## Prob Set 2.2 (#3, p.78)

from numpy import array,ones,zeros,diagonal,linalg,dot
from LUdecomp3 import *
import os

os.system('clear')  # This is handy for clearing the console screen

d = array([2,5,16,39,14],dtype=float)
c = array([-2,-6,12,-6],dtype=float)
e = c.copy()
A=zeros((5,5),dtype=float)
L=zeros((5,5),dtype=float)
D=zeros((5,5),dtype=float)
for k in range(0,5):  # Load dense matrix A for display purposes
    A[k,k]=d[k]
    if (k > 0): 
       A[k,k-1]=c[k-1]
       A[k-1,k]=c[k-1]
c,d,e = LUdecomp3(c,d,e)
for k in range(0,5):
    D[k,k]=d[k]
    L[k,k]=1.0
    if (k < 4): 
          L[k+1,k]=e[k]/d[k]
print( '\nA =\n',A)
print( '\nD =\n',D)
print( '\nL =\n',L)
B=dot(dot(L,D),L.transpose())
print('\nLDL^T=\n',B)
print('\nError in decomposition =',linalg.norm(A-B))
input("\nPress return to exit")