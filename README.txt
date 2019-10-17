Author: Jacob Babik
Date: 04-18-2019

Files included: main.h, main.cpp, util.h, util.cpp, heap.h, heap.cpp, graph.h, graph.cpp

Language: C++
Compiler: g++

Description: This program demonstrates the implementation of Dijkstra's shortest path algorithm using
min-heap as the priority queue. The program creates a weighted, directed, graph by reading in information
from a file named "Ginput.txt", which is located in the same directory. On reading "I", the program
reads in a graph from the "Ginput.txt" file. The user can print the graph information by typing "W". 
The user can find the shortest path from a vertice s to vertice t by typing C s t flag. The flag value
is 0 to print the length of the shortest path, and 1 to print the shortest path itself. The Makefile
will create an executable named "run" and the program can be run by typing ./run. An example
"Ginput.txt" file is given.
