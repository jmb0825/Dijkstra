#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"
#include "graph.h"
#include "heap.h"

using namespace std;

int nextCommand(int *s, int *t, int *flag)
{
	char c;
	while (1)
	{
		scanf("%c", &c);
		if (c == ' ' || c == '\t' || c == '\n')
		{
			continue;
		}
		if (c == 'E' || c == 'I' || c == 'W')
		{
			break;
		}
		if (c == 'e' || c == 'i' || c == 'w')
		{
			break;
		}
		if (c == 'C' || c == 'c')
		{
			scanf("%d", s);
			scanf("%d", t);
			scanf("%d", flag);
			break;
		}
		printf("Invalid Command\n");
	}
	return c;
}
//Read content from file and creates the adjacency list
void readFromFile(Graph *graph)
{
	int numVertices;
	int numEdges;
	int count = 0;
	string line;
	//Open file
	ifstream myfile("Ginput.txt");
	myfile >> numVertices >> numEdges;
	//Checks given number of edges with actual number of edges
	if (numEdges > readFileSize())
	{
		printf("Error: The number of edges is less than as specified in the beginning of the file.\n");
		return;
	}
	//Initialize adjacency list array
	List *array = initializeArray(numEdges);
	//Initialize a new array of elements
	Element *elementArray;
	elementArray = new Element[numEdges];
	
	//Initialize graph element array by calling function in graph.cpp
	initializeGraph(numEdges, numVertices, graph);

	//holds the index of the array, which is the vertice
	int currentIndex, neighbor, weight;
	//Reads input and creates adjacency list
	for (int i = 0; i < numEdges; i++)
	{
		myfile >> currentIndex;
		myfile >> neighbor;
		myfile >> weight;
		
		//Function called in graph.cpp to add input to the adjacency list
		addNode(currentIndex, neighbor, weight, array);
		
		elementArray[i].node = currentIndex;
	}
	//The entire graph is built using the 
	buildGraph(graph, array, elementArray, numEdges, numVertices);

	myfile.close();
}

//Counts how many numbers are in the file
int readFileSize()
{
	int number_of_lines = 0;
	string line;
	ifstream myfile("Ginput.txt");
	if (myfile.is_open())
	{
		//Goes through every line in file
		while (!myfile.eof())
		{
			getline(myfile, line);
			//Increment count
			++number_of_lines;
		}
	}
	myfile.close();
	return number_of_lines - 2;
}
