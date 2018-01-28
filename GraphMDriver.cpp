// GraphM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "nodedata.h"
#include "GraphM.h"
#include "GraphL.h"
#include <iostream>

int main()
{
	// part 1
	ifstream infile1("data31.txt");
	if (!infile1) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, find the shortest path from every node to all other nodes
	for (;;) {
		GraphM G;
		G.buildGraph(infile1);
		if (infile1.eof()) {
			break;
		}
		//for (int i = 1; i < MAXNODES_NUM; i++) {
		//	for (int j = 1; j < MAXNODES_NUM; j++) {
		//		if (G.C[i][j] != INT_MAX) {
		//			//cout << G.C[i][j] << " ";
		//		}
		//		else {
		//			//cout << "-";
		//		}
		//	}
		//	cout << endl;
		//}
		G.findShortestPath();

		G.displayAll();              // display shortest distance, path to cout
		G.display(3, 1);              // display path from node 3 to 1 to cout
		G.display(1, 2);
		G.display(1, 4);
		//G.display(1, 5);
		//G.display(1, 3);
	}

	cout << "Testing Part 2" << endl;
	// part 2 
	ifstream infile2("data32.txt");
	if (!infile2) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	//for each graph, find the depth-first search ordering
	for (;;) {
		GraphL G;
		G.buildGraph(infile2);
		if (infile2.eof())
			break;
		G.displayGraph();
		G.depthFirstSearch();    // find and display depth-first ordering to cout
	}

	cout << endl;
	return 0;
}

//------------------------------- buildTree ----------------------------------
// YOU COMMENT

// To build a tree, read strings from a line, terminating when "$$" is
// encountered. Since there is some work to do before the actual insert that is
// specific to the client problem, it's best that building a tree is not a 
// member function. It's a global function. 

//void buildGraph(GraphM& G, ifstream& infile) {
//	int numberOfNodes;
//	infile >> numberOfNodes;
//	G.
//	string s;
//	for (int i=0;i< numberOfNodes;i++) {
//		infile >> s;
//		cout << s << ' ';
//		//if (s == "$$") break;                // at end of one line
//		if (infile.eof()) break;             // no more lines of data
//		NodeData* ptr = new NodeData(s);     // NodeData constructor takes string
//		// would do a setData if there were more than a string
//
//		bool success = G.insert(ptr);
//		if (!success)
//			delete ptr;                    // duplicate case, not inserted 
//	}
//
//}


////------------------------------- initArray ----------------------------------
//// initialize the array of NodeData* to NULL pointers
//
//void initArray(NodeData* ndArray[]) {
//	for (int i = 0; i < ARRAYSIZE; i++)
//		ndArray[i] = nullptr;
//}