#!/opt/local/bin/python3.3
#
# Basics of Python 3 (COSC 370, Fall 2014) Part II
#
#
# For mutable object x, y = x just creates a new reference to x (no new object or copy
# is created); to get a new copy, use z = x[:]
#
x = [1.0,2.0,3.0]
y = x              # 'y' is an alias of 'x'
y[0]=2.0           # change 'y'
print (x)
z = x[:]           # get copy of 'x'
z[0]=4.0           # change 'z'
print (x)            # Is x affected?

#
# For matrix representations use backslash character for continuation to next line
#
matrix = [ [1,2,3], \
           [4,5,6], \
           [7,8,9] ]

print (matrix)
print (matrix[1][2])

#
# Arithmetic operators are:  +, -, *, /, **, %
# ** = exponentiation and % is the modulus operator (integer remainder after division)
#
str = 'yada '
print (3 * str)     # * replicates the string
a = [3,4,5]
print (3 * a)       # * causes repetition and generates a larger single list
print (a + [6,7])   # + enables appending sublists

str2 ='for you'
print (str + str2)  # string concatenation
#print (4 + str2)   # would generate an error, why? 

#
# Here is a list of augmented assignment statements:
#
#  a += b   # a = a + b
#  a -= b   # a = a - b
#  a *= b   # a = a * b
#  a /= b   # a = a / b
#  a **= b  # a = a ** b
#  a %= b   # a = a % b
#
# Here is a list of comparison operators:  <, >, <=, >=, ==, !=
#
a = 3
b = 2.99
c = '3'
print (a > b)
print (a == c)
print ((a > b) and (a != c))  # for different types, comparison operators force a common type
print ((a > b) or  (a == b))

#
# Conditional blocks: spacing (no tabs) determines code blocks
#
#  if condition :
#         block
#  elif condition :
#         block  
#  else :
#         block
#

def sign_of_a (a) :
   if a < 0.0 :
     sign = 'neg'
   elif a > 0.0 :
     sign = 'pos'
   else: 
     sign = 'zero'
   return sign

a=2.0
print ('a is ' + sign_of_a(a))

#
# Loops have the following structure:
#
#  while condition :
#         block
#  else :
#         block
#

nMax = 4
n = 1
a = [ ]  # empty list
while n < nMax :
    a.append(1.0/n)
    n = n + 1
print (a)

#
# Now, write same loop using "for:
#

nMax = 4
a = [ ]
for n in range(1,nMax) :   # range generates a list for the for-loop to use
    a.append(1.0/n)
print (a)

#
# Any loop (while or for) can be terminated by the "break" statement
#

list = ['a','b','c','d']
# Can allow user to specify input this way
# input = eval(input('Type a char: '))
char_input = 'e'
bound=len(list)
print (bound)
for i in range(bound) :  # generates the list [0,1,2,3] for i
    if list[i] == char_input : 
          print (char_input, 'is in position',i,'in list')
          break
    else :
         if i == bound-1 : 
             print (char_input, 'is not in list')

#
# Type conversion:  int(a), long(a), float(a)
#

a = 6
b = -2.5
c = '4.0'
print (a + b)
print  (int(b))     # truncation here, not rounding
print   (float(c))
# print (int(c))   # this would fail, why?
print   (int(float(c)))

#
# Reading input
#
# input(prompt) displays prompt and reads a line on input;
# converts the input to a string so that eval() function is
# needed to convert string to a numerical value
#
a = input('Input a: ')
print (a, type(a))
b = eval(a)
print (b, type(b))
c = eval(input('Input c: '))
print (c, type(c))

#
# Printing output:  print (object1, object2)
#

a = 123.456
b = [1,2,3,4]
print (a,b)
print ('a=',a,'\nb=',b)

#
# Python3.3 syntax for formatted output:  '{:fmt1}{:fmt2}...'.format(arg1,arg2,...)
#
# Common formats:
#                  wd    -> integer  (w=width)
#                  w.df  -> floating-point notation
#                  w.de  -> exponential notation
#
# Output is always right-justified and padded with blank spaces
#

a = 123.456
n = 5789
print ('{:6.2f}'.format(a))
print ('n={:7d}'.format(n))          # pad with 3 spaces
print ('n={:07d}'.format(n))         # pad with 3 zeros
print ('{:11.3e}{:7d}'.format(a,n))  # print tuple with 2 different formats
