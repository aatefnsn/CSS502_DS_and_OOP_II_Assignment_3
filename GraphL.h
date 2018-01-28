// --------------------- GraphL.h -----------------------------------------
//
// Ahmed Nada CSS-502
// Created:         February 9, 2019
// Last Modified:   February 19, 2019
// --------------------------------------------------------------
// Purpose: Implement Depth First Search algorithm by reading in a
// data file consisting of many lines and be able to find the DFS
// paths.  Then display the path from every node to to every
// other node.
// --------------------------------------------------------------
// Assumptions: All input data is assumed to be correctly formatted
// and valid.
// --------------------------------------------------------------
#pragma once
#include "nodedata.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

int const MAXNODES_NUM_GraphL = 101; // max size

class GraphL {
public:
	GraphL(); // constructor
	~GraphL(); // destructor
	void buildGraph(ifstream& infile); // building the graph from the input file
	void displayGraph(); // display the resulting graph in the reuired format
	void depthFirstSearch(); // display the paths of DFS
	void depthFirstSearchHelper(int adj); // helper method

private:

	void makeEmpty(); // method to be called by destructor to delete all data
	int size;

	struct EdgeNode;      // forward reference for the compiler
	struct GraphNode {    // structs used for simplicity, use classes if desired
		EdgeNode* edgeHead; // head of the list of edges
		NodeData* data;     // data information about each node
		bool visited;
	};

	struct EdgeNode {
		int adjGraphNode;  // subscript of the adjacent graph node
		EdgeNode* nextEdge;
	};
	// array of GraphNodes
	GraphNode nodesArray[MAXNODES_NUM_GraphL];
};
