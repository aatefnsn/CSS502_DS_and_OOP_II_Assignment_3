// --------------------- GraphM.h -----------------------------------------
//
// Ahmed Nada CSS-502
// Created:         February 9, 2019
// Last Modified:   February 19, 2019
// --------------------------------------------------------------
// Purpose: Implement Dijkstra's shortest path algorithm by reading in a
// data file consisting of many lines and be able to find the lowest cost
// paths.  Then display the cost and path from every node to to every
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
#include <limits>
#include <climits>
#include <stdint.h>
#include <string>
using namespace std;

int const MAXNODES_NUM = 101; // size for T and C table as per requirement

class GraphM {
public:

	GraphM(); // constructor
	void buildGraph(ifstream& infile); // build graph from .txt file
	bool insertEdge(int source, int dest, int weight); // insert edge into matrix
	bool removeEdge(int source, int dest); // remove edge
	void findShortestPath(); // implement Djikstra
	void display(int source, int dest); // display the Graph djikstra results from one source to one destination
	void displayAll();  // display the graph Djikstra results 

private:
	struct TableType
	{
		bool visited;                       // whether node has been visited
		int dist;                           // shortest distance from source known so far
		int path;                           // previous node in path of min dist
	};

	NodeData data[MAXNODES_NUM]; // data for graph nodes 
	int C[MAXNODES_NUM][MAXNODES_NUM];            // Cost array, the adjacency matrix
	int size;                             // number of nodes in the graph
	TableType T[MAXNODES_NUM][MAXNODES_NUM];      // stores visited, distance, path	
	string spaced(string str);       // method to introduce space between path integers and convert to string
};
