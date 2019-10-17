#ifndef GRAPH_H
#define GRAPH_H
#include "heap.h"
#include "main.h"
#include "graph.h"

//List structure used to create adjacency list
struct List
{
	int neighbor = -1;
	int weight;
	//Pointer to next node
	struct List* next = NULL;
};

//Initializes array for adjacency list
List* initializeArray(int numEdges);
//Adds a node to the adjacency list
void addNode(int index, int neighbor, int weight, List *array);
//Dynamic memory allocation for the graph
void initializeGraph(int numEdges, int numVerticies, Graph *graph);
//uilds the graph given an array of list strcutes and an array of element structures
void buildGraph(Graph *graph, List A[], Element H[], int numEdges, int numVertices);
//Initialzes element array to proper values for shortest path alogorithm to run
void InitializeSingleSource(Graph *graph, int s);
//Relaxes the given nodes, u and v
void Relax(Graph graph, int u, int v, int w);
//Returns the minimum weight between two nodes, u and v
int weight(Graph graph, int u, int v);
//Runs Dijkstra's shortest path algorithm on the given graph
void Dijkstra_SP(Graph graph, int s, int t, int flag);
//Prints the path from the source node to the destination
void printPath(Graph graph, int s, int t);

#endif
