#!/opt/local/bin/python3.3   
#
# Basics of Python 3 (COSC 370, Fall 2014) Part I
#

#
# Variables are dynamically typed in Python
#

a = 1        # a is an integer
print (a)
a = a +1.5   # a is now a float (floating-point number)
print (a)

#
# Strings are sequences of characters enclosed by single or double quotes
# Concatenation is done with "+" and slicing is dne with ":"
#

str1 = 'Fred'
str2 = 'Wilma'
print (str1 + ' and ' + str2)  # concatenation
print(str1[0:2])               # slicing

#
# Strings are immutable objects, i.e., individual characters cannot be
# modified with an assignment statement; strings have fixed length.
#

s = 'My name is John'
#s[0]= 'T'             # would generate an error

#
# Tuples are sequences of arbitrary (but immutable) objects; they support
# the same operations as strings; good for say coordinates of the Cartesian Coord. System
#

record = ('Doe','John',(5,15,75))   # tuple example
last,first,bdate = record           # unpack the tuple
print (first)
byear = bdate[2]                    # index on zero in python
print (byear)
name = record[1] + ' ' + record[0]
print (name)
print (record[0])
print (record[0:1])   # tuple with only 1 element followed by a comma
print (record[0:2])   # print items from position 0 up to but not including position 2 
print (record[0:3])   
#
# Lists are similar to tuples but are mutable, i.e., elements and lengths can be changed
#
list = [1.0,2.0,3.0]    # list enclosed by square brackets
list.append(4.0)        # append another member
print (list)
list.insert(0,0.0)      # do an insert
print (list)
print (len(list))         # get length of the string
list2=list[:]             # get a separate copy of current list variable
list[1:2] = [3.0,3.0]     # modify sublist - this actually expands list, why?
print (list)
list2[1:3] = [3.0,3.0]    # modify sublist - this does not expand list, why?
print (list2)
