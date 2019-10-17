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

//Creates array for adjacency list
List* initializeArray(int numEdges)
{
	List *array;
	array = new List[numEdges];
	return array;
}
//Adds node to array of linked lists
void addNode(int index, int neighbor, int weight, List *array)
{
	//Create two new list structures
	List *L1, *L2;
	L1 = new List;
	L2 = new List;
	//Initialize L1 with values from file
	L1->neighbor = neighbor;
	L1->weight = weight;
	L1->next = NULL;
	//Insert into linked list head if possible
	if (array[index].neighbor == -1)
	{
		array[index] = *L1;
	}
	//If nodes already exist, insert at the end of the linked list
	else
	{
		//Increment pointer to end of linked list
		for (L2 = &array[index]; L2->next != NULL; L2=L2->next)
		{
			//do nothing
		}
		//Set new node = L1
		L2->next = L1;
	}
}
//Function to dynamically allocate memory for the graph
void initializeGraph(int numEdges, int numVerticies, Graph *graph)
{
	graph->H = (Element *)malloc(sizeof(Element) *numVerticies);
	graph->A = (List **)malloc(sizeof(List*) *numEdges);
}
//Builds the graph consisting of an adjacency list and an array of elements
void buildGraph(Graph *graph, List A[], Element H[], int numEdges, int numVertices)
{
  graph->e = numEdges;
  graph->v = numVertices;
	for (int i = 1; i <= numVertices; i++)
	{
		graph->A[i] = &A[i];
		graph->A[i]->neighbor = A[i].neighbor;
		graph->A[i]->weight = A[i].weight;
		graph->A[i]->next = A[i].next;
		graph->H[i].node = H[i].node;
	}
}
//Returns the minimum weight between two given nodes
int weight(Graph graph, int u, int v)
{
	int min = INT_MAX;
	if (graph.A[u] != NULL)
	{
		//Pointer to traverse linked list
		List *pointer = graph.A[u];
		//Find the weight between two nodes.
		//If there is more than one weight, traverse linked list and
		//then return the minimum weight.
	    while (pointer != NULL)
		{
			if (pointer->neighbor == v && pointer->weight<min)
			{
				min = pointer->weight;
			}
			pointer = pointer->next;
		}
	    return min;
	}
	else
	{
	    cout << "WEIGHT ERROR" << endl;
	}
}
//The relax function finds the shortest path between two nodes
void Relax(Graph graph, int u, int v, int w)
{
	//If the distance to v is greater than u+weight
	if (graph.H[v].d > graph.H[u].d + weight(graph, u, v))
	{
		//Set v equal to new distance and parent values
		graph.H[v].d = graph.H[u].d + weight(graph, u, v);
		graph.H[v].pi = u;
	}

}
//Initializes the graph to be ready to find the shortest path
void InitializeSingleSource(Graph *graph, int s)
{
	//Array with only 1 node for each vertex
	Element *newElementArray;
	newElementArray = new Element[graph->v+1];
	//Sets each Element structure to initial values
	for (int i = 1; i <= graph->v; i++)
	{
		newElementArray[i].node = i;
		newElementArray[i].d = INT_MAX;
		newElementArray[i].pi = 0;
	}
	graph->H = newElementArray;
	//Set source node distance to 0
	graph->H[s].d = 0;
}
//Runs Dikstra's Shortest Path Algorithm
void Dijkstra_SP(Graph graph, int s, int t, int flag)
{
	InitializeSingleSource(&graph, s);
	//S is all the nodes that have already been explored
	Element *S;
	S = new Element[graph.v+1];
	//Q is the Queue of elements that need to be explored
	Element *Q;
	Q = new Element[graph.v+1];
	//Get Q values from graph
	for (int i = 1; i <= graph.v; i++)
	{
		Q[i].node = graph.H[i].node;
		Q[i].d = graph.H[i].d;
		Q[i].pi = graph.H[i].pi;
	}
	int numNodes = graph.v;
	int numNodes2 = numNodes;
	int currentMin = INT_MAX;
	int index = 1;
    //Initialized to source node
	int u = Q[s].node;
	//Index counter for S array
	int scount = 0;
	
	//Runs while there are still undiscovered nodes
	while (numNodes != 0)
	{	
		//For loop to find the current min in the Q
		for (int i = 1; i <= numNodes2; i++)
		{
			bool present = false;
			for(int x = 1; x<=scount; x++)
		    {
				if(graph.H[i].node == S[x].node)
				{
					present = true;
				}
			}
			if (graph.H[i].d < currentMin && present == false)
			{
				currentMin = graph.H[i].d;
				index = i;
			}
		}
	    //u is set equal to the current min element
		u = graph.H[index].node;
		
		scount++;
		//The minimum node is added to the list of discovered nodes
		S[scount] = graph.H[index];
		//Number of nodes in Q decremented
		numNodes--;

		//Relax function called if there is a node at the index given
		if (graph.A[u]->neighbor != -1)
		{
			//Pointer to adjacency list, used to traverse linked list
			List *pointer = graph.A[u];
			//Relax the current node
			Relax(graph, u, pointer->neighbor, weight(graph, u, pointer->neighbor));
			//If there are more nodes in the linked list, call relax on them
			while (pointer->next != NULL)
			{
				pointer = pointer->next;
				Relax(graph, u, pointer->neighbor, weight(graph, u, pointer->neighbor));
			}
		}
		currentMin = INT_MAX;
	}
	//If given flag is 0, the length of the path is printed
	if (flag == 0)
	{
		cout << "LENGTH: "<< graph.H[t].d << endl;
	}
	//If given flag is 1, the path is printed by calling printPath in graph.cpp
	else if (flag == 1)
	{
		printPath(graph, s, t);
	}
	else
	{
		cout << "Error: Invalid flag value." << endl;
	}
}
//The shortest path between the nodes is printed
void printPath(Graph graph, int s, int t)
{
	cout << "PATH: ";
	if (s == t)
	{
		cout << s << endl;
	}
	else
	{
		cout << s;
		//Array to hold pi values
		int array[200];
		int index_t = t;
		int counter = 2;
		//First element set to destination vertice
		array[1] = t;
		//Adds pi values into the array until the source is reached
		while (graph.H[index_t].pi != s && graph.H[index_t].pi != t && index_t != 0)
		{
			array[counter] = graph.H[index_t].pi;
			index_t = array[counter];
			counter++;
		}
		//Printing array of pi values in reverse order
		for (int i = counter - 1; i >= 1; i--)
		{
			cout << "," << array[i];
		}
		cout << endl;
	}
}
