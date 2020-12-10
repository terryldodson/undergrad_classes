#!/opt/local/bin/python3.3
#
# Basics of Python 3 (COSC 370, Fall 2014) Part IV
#
# Namespace = dictionary of variable names and their values
# 
# Three levels:
#      1) Local - created when a function is called (parameters passed and variables
#                 created within the function); deleted when function terminates.
#                 Variables created inside functions only have that function's local
#                 namespace.
#
#     2) Global - created when the module is loaded; variables assigned in this
#                 namespace are visible to all functions in the module.
#
#   3) Built-in - created when interpreter starts; variables assigned are visible to
#                 all program units.
#
#  Resolution of variable:
#
#     Local -> Global -> Built-in -> issue NameError exception
#
# Variables created in the global namespace do not have to be passed to functions
# as arguments - but this is generally frowned upon in structured programming.  Why?
#
def divide ( ):
    c = a/b
    print ('a/b = ',c)
a = 100.0
b=5.0
divide()

def divide2 ( ):
     c= a/b
a = 100.0
b = 5.0
divide2( )
# print ('a/b = ',c)    # What is wrong with this statement?

#
# Running programs
#
# Byte code of module is written to a file with the '.pyc' extension.  The interpreter
# will always look for a module's .pyc file first.
#
# When executing something like 'python3.3 myprog.py' it is a good 
# practice to add the line
#
#  input('Press return') 
#
# to avoid a program window from closing (sometimes happens on PC's 
# running the Windows OS).
#
# Error messages can be slightly confusing.  Here's an example:
#
# from numpy import array
# a = array([1.0,2.0,3.0]      # See what is missing?
# print (a)
# input('Press return')
#
# The interpreter considers the third line as a continuation of the second line
# and the output would be something like ...
#
# File:"C:\Python22\test_module.py", Line 3
#   print (a)
#        ^
# SyntaxError: invalid syntax

#
# Another good practice is to add a "docstring" at the beginning of each module.
#
#  We will create a separate file called my_error.py for this module...
#
## module my_error 
#  '''err(string).  Prints 'string' and terminates program.'''
#  import sys
#  def err(string) :
#     print (string)
#     input('Press return to exit')
#     sys.exit()

import my_error
print (my_error.__doc__)  # show docstring for this module (use two underscores before
                          # and after 'doc'
