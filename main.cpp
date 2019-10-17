#include <cstdlib>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <stdio.h>
#include "graph.h"
#include "heap.h"
#include "util.h"

using namespace std;

//Element *element;
//Ensures that the file exists
bool fexists(const char *filename)
{
	ifstream ifile(filename);
	return (bool)ifile;
}

int main()
{
	char c;
	int s,t,flag;
	//Create new graph object
	Graph graph;
	bool graphCreated = false;
	while (1)
	{
		c = nextCommand(&s, &t, &flag);
		switch (c)
		{
			//Exit
		case 'e':
		case 'E':
			printf("COMMAND: %c. \n", c);
			printf("The program is going to be terminated. \n");
			exit(0);
			//Read from file and create graph
		case 'i':
		case 'I':
			printf("COMMAND: %c. \n", c);
			if (fexists("Ginput.txt"))
			{
				readFromFile(&graph);
				graphCreated = true;
				break;
			}
			else
			{
				printf("There was a problem opening file Ginput.txt for reading. \n");
				break;
			}
			//Display graph information
		case 'w':
		case 'W':
			printf("COMMAND: %c. \n", c);
			if (graphCreated == false)
			{
				printf("Error: There is no graph to print.\n");
			}
			else
			{
				printGraph(graph);
			}
			break;
			
			//Run Dijkstra's shortest path algorithm
		case 'c':
		case 'C':
			printf("COMMAND: %c %d %d %d. \n", c, s, t, flag);
			if (graphCreated == false)
			{
				printf("Error: There is no graph to run Dijkstra's algoritm on. \n");
				break;
			}
			//Checks to make sure vertices given exist in graph
			if (s <= 0 || s > graph.v || t < 0 || t > graph.v)
			{
				printf("Error: One or more of the nodes is invalid. \n");
				if (flag != 0 && flag != 1)
				{
					printf("Error: Invalid flag value. \n");
				}
				break;
			}
			if (graph.A[s]->neighbor == -1)
			{
				printf("Sorry, node %d is not reachable from node %d. \n", t, s);
				break;
			}
			else
			{
				Dijkstra_SP(graph, s, t, flag);
			}
			break;
		default:
			break;
		}
	}
	return 0;
}
