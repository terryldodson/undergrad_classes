#!/opt/local/bin/python3.3
#
# Basics of Python 3 (COSC 370, Fall 2014) Part III
#
# Error Control
# 
# try :
#      (code)
# except <error> :
#      (code)
#
# If you drop '<error>' above, all exceptions are caught.
#
b=1
try :
     a=0
     c=b/a
except ZeroDivisionError :
     print ('You just divided by zero!')

#
# Functions and Modules
#
# Syntax:     def fname(parm1,parm2,...) :
#                 statements
#                 return values
#
predict={'Joe': {'Falcons': 2.5, 'Ravens': 3.5,
 'Seahawks': 3.0, 'Steelers': 3.5, 'Patriots': 2.5, 'Jets': 3.0},
'Arthur': {'Falcons': 1.5, 'Ravens': 1.5,
 'Seahawks': 2.0, 'Steelers': 2.5, 'Patriots': 2.5, 'Jets': 2.0},
'Fred': {'Falcons': 2.5, 'Ravens': 1.0,
 'Seahawks': 1.0, 'Steelers': 2.0, 'Patriots': 2.0, 'Jets': 0.5}}

from math import sqrt

def sim_distance(list,item1,item2):  # Get the list of shared_items
#
# Returns a distance-based similarity score for item1 and item2 in list
#
    si={}
    for entry in list[item1]:
      if entry in list[item2]: si[entry]=1
#
# if they have no ratings in common, return 0
#
    if len(si)==0: return 0

#   Add up the squares of all the differences

    sum_of_squares=sum([pow(list[item1][entry]-list[item2][entry],2)
    for entry in list[item1] if entry in list[item2]])
    return 1/(1+sqrt(sum_of_squares))

print ('Similarity between Joe and Fred is %4.2f'\
       %sim_distance(predict,'Joe','Fred'))

#
#  What happens when a mutable object is passed to a function?
#

def squares (a) :
    for i in range (len(a)) :
        a[i]=a[i]**2

a=[1,2,3,4]
squares(a)
print (a)    # What do you expect to see on output?

#
# For array-based funnctions you will want to load the NumPy module (if not
# (already available)
#
# Useful functions:
#     zeros( (dim1,dim2), dtype=spec)
#      ones( (dim1,dim2), dtype=spec)
#    arange( from, to, increment)        # returns an array rather than a list

from numpy import *    # loading all functions from the Numpy module

a = arange(10).reshape(2,5)
print (a)
print (a.shape)
b = array([[2,-1],[-1,3]],dtype=float)
print (b)
c= ones((3,3),dtype=float)
print (c)
#
# Accessing/changing array elements:
#

a = zeros((3,3),dtype=float)
a[0]  = [2.0,1.1,1.5] # change a row
a[1,1] = 5.2          # change an element
a[2,0:2] = [8.0,-3.3] # change part of a row
print (a)

#
# Operations on arrays
#
a = array([0.0,4.0,9.0,16.0])
print (a/16)
print (a - 4.0)   # operation is broadcast to all elements
print (sqrt(a))

#
# Note that functions from 'math' module cannot be applied to arrays
#
from math import sqrt
a = array([1.0,4.0,9.0,16.0])
print (sqrt(a[1]))
#print (sqrt(a))   # TypeError: only length-1 arrays can be converted to Python scalars

#
# Other useful array functions:
#

a = array([[ 4.0, -2.0,  1.0], \
           [-2.0,  4.0, -2.0], \
           [ 1.0, -2.0,  3.0]])
b = array([1.0,4.0,2.0])

print (dot(b,b))      # dot product
print (multiply(a,b)) # element-wise product
print (dot(a,b))      # matrix-vector product
print (diagonal(a))   # principal diagonal
print (diagonal(a,1)) # first subdiagonal
print (trace(a))      # sum of diagonal elements
print (argmax(b))     # index of largest element (keep in mind zero indexing)
c = b.copy()        # how to get independent copy - not an alias
print (c)
