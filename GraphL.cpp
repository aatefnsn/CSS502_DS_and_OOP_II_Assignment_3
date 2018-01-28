//-------------------------- GraphL.cpp ---------------------------------
//
// Ahmed Nada CSS-502
// Created:         February 9, 2019
// Last Modified:   February 19, 2019
// --------------------------------------------------------------
//  GraphL calculates depth-first algorithm (search alway starts at
//  node #1).Reads data from provided data file, and find the depth-first
//  search. 
//
//  Implementation and assumptions:
//  -- Implemenet as Graph by using array and linked list
//  -- Implemenet depth-fist algorithm
//  -- Assumption: the data file has to be in descending order as edge nodes 
//     are added to the list from the head direction so smallest comes on top as edge head
//---------------------------------------------------------------------------
#include "pch.h"
#include "GraphL.h"

// --------------------- GraphL() -----------------------------------------
// Default constructor
// ------------------------------------------------------------------------

GraphL::GraphL() {
	this->size = 0; // set size to 0

	for (int i = 0; i < MAXNODES_NUM_GraphL; ++i) {
		nodesArray[i].visited = false; // initialize the adjacency list array visited set to false
		nodesArray[i].edgeHead = nullptr; // initialize the adjacency list array edje head set to nullptr
		nodesArray[i].data = nullptr; // initialize the adjacency list array data set to nullptr
	}
}

// --------------------- ~GraphL() -----------------------------------------
// Destructor
// -------------------------------------------------------------------------

GraphL::~GraphL() {
	this->makeEmpty(); // calls makeEmpty function
}

// --------------------- makeEmpty() -----------------------------------------
// Deletes object, cleans Graph from all objects created to avoid any memory leaks
// Helper function for Destructor
// ---------------------------------------------------------------------------

void GraphL::makeEmpty() {
	for (int i = 0; i <= this->size; i++) {
		delete nodesArray[i].data; // delete all data objects
		nodesArray[i].data = nullptr; // set data pointers to null
	}
	for (int i = 0; i <= this->size; i++) {
		if (nodesArray[i].edgeHead != nullptr) {
			EdgeNode * pointer = nodesArray[i].edgeHead; // go to each array element and set a pointer on the edge head
			while (pointer != nullptr) { // while loop to keep on deleting the edges
				nodesArray[i].edgeHead = nodesArray[i].edgeHead->nextEdge; // move edge head
				delete pointer; // delete the edge node
				pointer = nullptr; // set pointer to null
				pointer = nodesArray[i].edgeHead; // set the pointer to the the new edge head
			}
		}
		else
			continue;
	}
}

// --------------------- displayGraph() -----------------------------------------
// Displays each node information and edge in the graph
// ------------------------------------------------------------------------------

void GraphL::displayGraph() {
	cout << endl;
	cout << "Graph:" << endl;
	EdgeNode * temp;
	for (int i = 1; i <= this->size; i++) {
		cout << "Node" << setw(9) << left << i << *this->nodesArray[i].data << endl; // start by first node as mentioned in assignment
		cout << endl;
		temp = this->nodesArray[i].edgeHead; // set a reference
		while (this->nodesArray[i].edgeHead != nullptr) {
			cout << "   edge " << setw(3) << left << i << this->nodesArray[i].edgeHead->adjGraphNode << endl; //print edge
			this->nodesArray[i].edgeHead = this->nodesArray[i].edgeHead->nextEdge; // move to next
		}
		this->nodesArray[i].edgeHead = temp; // reset edge head to the reference 
	}	
}

// --------------------- depthFirstSearch() -----------------------------------------
// Makes a depth-first search and displays each node in depth-first order
// ----------------------------------------------------------------------------------

void GraphL::depthFirstSearch() {	
	cout << "Depth-first ordering : ";
	for (int v = 1; v <= size; ++v) // loop through whole array size
	{
		if (!nodesArray[v].visited)   // check if node was visited before
		{
			depthFirstSearchHelper(v);  // call helper method defined below
		}
	}
	cout << endl;
}

// --------------------- depthFirstSearchHelper() -----------------------------------------
// Helper function for depthFirstSearch()
// Recursively finds the depthFirstSearch
// ----------------------------------------------------------------------------------------

void GraphL::depthFirstSearchHelper(int node) {
	cout << " " << node;   // print node
	nodesArray[node].visited = true;   // mark it as visited
	EdgeNode* current = nodesArray[node].edgeHead; // move pointer to head

	while (current != nullptr) // loop till end of linked list
	{
		if (!nodesArray[current->adjGraphNode].visited) // check if visited
		{
			depthFirstSearchHelper(current->adjGraphNode);  // recursively call helper
		}
		current = current->nextEdge;    // move pointer to next node in linked list
	}	 
}

// --------------------- buildGraph() -----------------------------------------
// Builds up graph node information and adjacency list of edges between each
// node reading from a data file. Assuming data is supplied sorted in descending 
// order and list always inserts at the edge head
// --------------------------------------------------------------

void GraphL::buildGraph(ifstream& infile) {
	infile >> this->size;	// size is first elemnt in graph lines inside txt file
	string s;
	int source;
	int dest;
	for (int i = 0; i <= this->size; i++) {
		if (infile.eof()) break;		
		getline(infile, s);	
		NodeData* ptr = new NodeData(s); // create node data
		nodesArray[i].data = ptr; // assign it to the array
	}
	while (infile >> source >> dest)
	{
		if (source == 0)
		{
			break; // if source is 0 then break; 
		}
		if (nodesArray[source].edgeHead == nullptr) { // first lement in the list
			EdgeNode * n = new EdgeNode(); // create edge node
			n->adjGraphNode = dest; // set edge node adj node to the destination 
			n->nextEdge = nullptr; // set the next edge to null
			nodesArray[source].edgeHead = n; // set n as the edge head since it isd the only one in the list
		}
		else {
			EdgeNode * n = new EdgeNode(); // if not the first elemnt in the list then create new edge node
			n->adjGraphNode = dest; // set the adj node as dest
			n->nextEdge = nodesArray[source].edgeHead; // set the new node next edge to the current edge head
			nodesArray[source].edgeHead = n;	// set the new node as the new edge head		
		}
	}
}