#!/usr/bin/python3
## example2_8 on p. 54

import os
from numpy import linalg,array,dot,transpose
from choleski import *

os.system('clear')  # This is handy for clearing the console screen

A = array([[ 1.44, -0.36,  5.52,  0.0], \
           [-0.36, 10.33, -7.78,  0.0], \
           [ 5.52, -7.78, 28.40,  9.0], \
           [ 0.0,   0.0,   9.0,  61.0]])
A_old=A.copy()
L = choleski(A)  # original contents of A overwritten
B=dot(L,transpose(L))
print ('A =\n',A_old)
print ('L =\n',L)
print ('\nCheck: L*L_transpose =\n', B)
print('\nError in decomposition = ',linalg.norm(A_old-B))
input("\nPress return to exit")  