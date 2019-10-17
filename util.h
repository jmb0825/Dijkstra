#ifndef UTIL_H
#define UTIL_H
#include "heap.h"

//Takes commands from the keyboard and feeds to the main program
int nextCommand(int *i, int *v, int *f);
//Determines the count of numbers in the file
int readFileSize();
//Reads the numbers from the file and creates a heap
void readFromFile(Graph *graph);

#endif
