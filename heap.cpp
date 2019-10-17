#include <iostream>
#include <fstream>
#include <string>
#include <climits>
#include <stdlib.h>
#include <math.h> 
#include "util.h"
#include "heap.h"
#include "graph.h"

using namespace std;

//Function used to print the entire graph
void printGraph(Graph graph)
{
	cout << graph.v << " " << graph.e << endl;
	for (int i = 1; i <= graph.v; i++)
	{
		//Prints vertice
		cout << i << " : ";
		for(int x=1; x<=graph.e; x++)
		{
		  if (graph.A[i]->neighbor != -1)
			{
				//Pointer to the adjacency list at index i
				List *pointer = graph.A[i];
				cout << "(" << graph.A[i]->neighbor << "," << graph.A[i]->weight << ")";
				//Traverses the adjacency list until the last node is reached
				while (pointer->next != NULL)
				{
					pointer = pointer->next;
					//Prints info from current node
					cout << "; (" << pointer->neighbor << "," << pointer->weight << ")";
				}
				if (pointer->next == NULL)
				{
					break;
				}
			}
		}
		cout << endl;
	}
}

//Deletes the element with the min key and returns to caller.

int deleteMin(Graph graph, int flag)
{
	//Check if heap empty
	if (graph.v <= 0)
	{
		printf("There are no elements in heap to delete. \n");
	}
	
	
	//If heap only has one element, delete it
	if (graph.v == 1)
	{
		graph.v = graph.v - 1;
		return graph.H[0].node;
	}
	//Keep the min value here
	int minValue = graph.H[0].node;
	if (graph.v > 1)
	{
		//Shift heap elements
		graph.H[0].node = graph.H[0].node;
		graph.v = graph.v;
		//Ensure that heap is heapified
		heapify(graph, 0);
	}
	return minValue;

}

//Performs min-heapify operation from x onwards
void heapify(Graph graph, int x)
{
	int left = leftChild(x);
	int right = rightChild(x);
	int smallest;
	//Compares left child to current index
	if (left <= graph.v && graph.H[left].node < graph.H[x].node)
	{
		smallest = left;
	}
	else
	{
		smallest = x;
	}
	//Compares right child to current index
	if (right <= graph.v && graph.H[right].node < graph.H[smallest].node)
	{
		smallest = right;
	}
	//Exchanges the two values
	if (smallest != x)
	{
		heapify(graph, smallest);
	}
}

//Returns the parent node of the given node
int parent(int x)
{
	int value;
	value = (x - 1) / 2;
	return value;
}

//Returns the left child of the given node
int leftChild(int x)
{
	int value;
	x++;
	value = 2 * x - 1;
	return value;
}

//Returns the right child of the given node
int rightChild(int x)
{
	x++;
	int value = 2 * x;

	return value;
}

//Exchanges the two nodes pointed to by that parameters
void exchange(int *a, int *b)
{
	int store = *a;
	*a = *b;
	*b = store;
}

