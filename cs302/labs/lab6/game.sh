#! /bin/sh

R=$1
C=$2

mazemake ${R:=60} ${C:=80} maze.txt
mazeimage maze.txt 

mazesolve maze.txt path.txt 
mazeimage maze.txt path.txt 

convert maze.ppm maze.png
convert path.ppm path.png
