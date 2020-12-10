#
# August 2013 High Temps for Knoxville,TN
#
# Author: Terryl Dodson
# NetID: tdodson3
# Assignment #: Hwk 1 for COSC 370

#importing libraries
from prettytable import PrettyTable
from numpy import arange
import numpy as np
from tabulate import tabulate, _table_formats
import matplotlib.pyplot as plt

#initializing arrays (xData - days in the month, tData - temperatures for each data,
# avg - list that holds the average temperatures values, sum - variable to obtain the sum of temperatures,
# num - obtains number of values)
xData = arange(1,32)  
tData = [86,87,84,86,86,86,84,83,90,89,88,85,86,79,83,81, \
         75,80,81,85,81,88,89,87,84,85,86,88,88,90,90]
avg = []  
sum = 0
num = 1

#for loop to loop through temperature values 
#calculates the average values and stores each value in avg list
for i in tData:
    sum += i
    avg.append(sum / num)
    num += 1    

#formatted average values to 2 decimal places
formatted_avg_list = ['%.2f' % elem for elem in avg]

#created table that displays the average for each day
table = PrettyTable(['Day', 'Avg'])
for x in range(0,31):
    table.add_row([xData[x], formatted_avg_list[x]])
print(table)
    
#set title for the graph
plt.title("High Temperatures for Knoxville, TN - August 2013")

#sets the x and y axes ranges
#plots all three graphs (blue line, red circles, and green line)
#set grid to be true
plt.axis([0, 32, 70, 95])
plt.plot(xData, tData, 'ro')
plt.plot(xData, tData, 'b-')
plt.plot(xData, avg, 'g--')
plt.grid(linestyle = 'dashed')
plt.grid(True)

#set the text for the average line
plt.text(15, 86, 'Monthly Avg', color='green', fontsize=12)

#labeled the x and y axes
plt.xlabel('Day')
plt.ylabel('High Temp')

#display graph
plt.show()
