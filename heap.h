#ifndef HEAP_H
#define HEAP_H

//Create the Graph
struct Graph
{
	//create the field for number of vertices
	int v;
	//create the field for number of edges
	int e;
	//Pointer to the struct element;
	struct Element *H;
	//Double pointer to the struct A
	struct List** A;
};
//Create the element data type
struct Element
{
	//Create the field named node
	int node;
	//Create distance field initialized to infinity
	int d;
	//Create the pi field initialized to 0
	int pi = 0;
};

//Prints the entire graph
void printGraph(Graph graph);
//Deletes min value from heap
int deleteMin(Graph graph, int flag);
//Performs min-heapify operation from x onwards
void heapify(Graph graph, int x);
//Returns the parent node of the given node
int parent(int x);
//Returns the left child of the given node
int leftChild(int x);
//Returns the right child of the given node
int rightChild(int x);
//Exchanges the two nodes pointed to by that parameters
void exchange(int *a, int *b);


#endif
