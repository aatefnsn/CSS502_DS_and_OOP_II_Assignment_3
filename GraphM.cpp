// --------------------- GraphM.cpp -----------------------------------------
//
// Ahmed Nada, CSS-502
// Created:         February 9, 2019
// Last Modified:   February 19, 2019
// --------------------------------------------------------------
// Purpose: Implement Dijkstra's shortest path algorithm by reading in a
// data file consisting of many lines and be able to find the lowest cost
// paths.  Then display the cost and path from every node to to every
// other node. All methods in the header file are implemented here in the
// source file. 
// --------------------------------------------------------------
// Assumptions: All input data is assumed to be correctly formatted
// and valid.
// --------------------------------------------------------------
#include "pch.h"
#include "GraphM.h"

// --------------------- Default Constructor -----------------------------------------
// Constructs an empty table and initializes all values
// -----------------------------------------------------------------------------------

GraphM::GraphM() { // constructor
	this->size = 0; // set size to 0
	for (int source = 0; source < MAXNODES_NUM; source++) 
	{
		data[source] = NodeData(); // set data to empty strings
		for (int dest = 0; dest < MAXNODES_NUM; dest++) 
		{
			T[source][dest].dist = INT_MAX; // set distance to infinity
			T[source][dest].path = 0; //set path to int 0 
			T[source][dest].visited = false; // set visited to false
			C[source][dest] = INT_MAX; // set adjacency matrix to infinity
		}
	}
}

// -------------- insertEdge(int source, int dest, int weight) ----------------
// Inserts an edge into a graph between 2 given nodes
// ----------------------------------------------------------------------------

bool GraphM::insertEdge(int source, int dest, int weight) {
	if (source > this->size || source < 1) { // if source node is greater than the size or less than 1 then it is an invalid input
		return false; 
	}

	if (dest > this->size || dest < 1) { // if destination node is greater than the size or less than 1 then it is an invalid input
		return false;
	}

	if (weight < 0) { // Djikstra does not work well with negative weights so no negative weights allowed
		return false; 
	}

	if (source <= this->size && dest <= this->size) 
	{ 
		this->C[source][dest] = weight; // if all satisfied then insert in adjacency matrix
		return true; // and return true
	}
	else
		return false;
}

// --------------------- removeEdge(int source, int dest) ---------------------
// Removes an edge between 2 given nodes
// ----------------------------------------------------------------------------

bool GraphM::removeEdge(int source, int dest) { // remove edge, using same conditions as insert edge method
	if (source > this->size || source < 1)
	{
		return false;
	}

	if (dest > this->size || dest < 1)
	{
		return false;
	}
	if (source <= this->size && dest <= this->size) 
	{
		this->C[source][dest] = INT_MAX; // replace old value with infiinty 
		return true; // return true
	}
	else
		return false;
}

// --------------------- findShortestPath() -----------------------------------------
// Finds the shortest path between every node to every other node
// in the graph using Dijkstra's algorithm. Fills the T matrix with path and distance
// ----------------------------------------------------------------------------------

void GraphM::findShortestPath() 
{
	for (int source = 1; source <= this->size; source++) // row
	{ 
		T[source][source].dist = 0; // always start with node 1 and set its distance to 0, diagonally all dist from the source to itself should be set to 0
		int min_weight = T[source][source].dist; // min weight variable to be used to traverse over the matrix row
		int next_vertix = source; // always source node which has weight 0 will be the first next node
		T[source][next_vertix].path = source; // path will be the source path
		int path_now = 0; // path now variable used to track the path until the end
		for (int i = 1; i <= this->size; i++) { // column 
			for (int k = 1; k <= this->size; k++) 
			{
				if (!T[source][k].visited && T[source][k].dist < min_weight) // update min weight for a vertix that is not visited before and has lower weight
				{ 
					min_weight = T[source][k].dist; // update min wight
					next_vertix = k; // set next vertix to the node with the least weight and that is not visited before
				}
			}
			if (min_weight == INT_MAX) // if no remaining vertixes to be visited and there is one path with infitity weight then skip and move to the next vertix
			{ 
				continue;
			}
	path_now = T[source][next_vertix].path; // get the current path so far that needs to be updated
	T[source][next_vertix].visited = true; // set visited to true
	for (int j = 0; j <= this->size; j++) // after getting the next vertix go over all its neighoring vertixes and update weights and path
	{  
		if (C[next_vertix][j] != INT_MAX && (min_weight + C[next_vertix][j]) < T[source][j].dist) // if there is a path from the vertix to another vertix with better weight/distance
		{ 
			T[source][j].dist = min_weight + C[next_vertix][j]; // then update the weight/distance
			T[source][j].path = path_now * 10 + j; // update the path by multiplying by 10 and adding the vertix index
		}
	}
	min_weight = INT_MAX; // reset min weight to it will always find a better path less than infinity 
		}
	}
}

// --------------------- spaced(string str) -----------------------------------------
// helper method to instroduce spaces in between characters of a string
// ----------------------------------------------------------------------------------

string GraphM::spaced(string str) // helper method for inserting space
{
	if (str == "") return str;

	string result(2 * str.size() - 1, ' '); // create new string double the size and fill with spaces
	for (int i = 0, j = 0; i < str.size(); i++, j += 2) result[j] = str[i]; // insert old string chars into the new one, hopping old string by 1 and new string by 2
	return result;
}

// --------------------- displayAll() -----------------------------------------
// Uses couts to demonstrate that the alogorithm works properly by printing out
// the node data, the path from each node to every other node and the path weight
//and path nodes
// ----------------------------------------------------------------------------

void GraphM::displayAll()
{
	cout << "Description" << setw(20) << "From node" << setw(10) << "To node"
		<< setw(14) << "Dijkstra's" << setw(7) << "Path" << endl; // header as required

	for (int source = 1; source <= size; source++)
	{
		cout << data[source] << endl;     // print node name
		cout << endl;
		for (int dest = 1; dest <= size; dest++)
		{
			if (T[source][dest].dist != 0) // if distance is not 0, distance to same node is always 0 so as to make sure displayAll method will not display matrix to 
			{
				cout << setw(27) << source;   // print source node
				cout << setw(10) << dest;     // print dest node
				if (T[source][dest].dist == INT_MAX) // if diestance is infinity this means no path
				{
					cout << setw(12) << "----" << endl; // no adjacent nodes so just dots
				}
				else
				{
					cout << setw(12) << T[source][dest].dist;   // print distance
					cout << setw(10);
					string s = to_string(T[source][dest].path); // get path from int to string
					s = spaced(s); // convert it into spaced string
					cout << setw(9 + (s.length())) << s << endl; // output path
				}
			}
		}
	}
}

// --------------------- display() -----------------------------------------
// Uses couts to display the shortest distance with path info between the
// source Node to the dest Node
// -------------------------------------------------------------------------

void  GraphM::display(int source, int dest) 
{
	if (T[source][dest].dist != 0)
	{
		cout << setw(10) << source;   // print source node
		cout << setw(5) << dest;     // print dest node
		if (T[source][dest].dist == INT_MAX)
		{
			cout << setw(12) << "----" << endl; // no adjacent nodes
		}
		else
		{
			cout << setw(12) << T[source][dest].dist;   // print distance
			cout << setw(10);
			string s = to_string(T[source][dest].path);
			s = spaced(s);
			cout << setw(9 + (s.length())) << s << endl;  // print spaced path

			for (int i = 0; i < to_string(T[source][dest].path).length(); i++){
				cout << data[to_string(T[source][dest].path).at(i) - 48] << endl; // print path data by getting the 
				//path as individual integers by converting to string and getting asci characters and subtract by 48 to get the integer representation
				cout << endl;
			}
		}
	}
}

// --------------------- buildGraph() -----------------------------------------
// Builds up graph node information and adjacency matrix of edges
// between each node reading from a file.
// ----------------------------------------------------------------------------

void GraphM::buildGraph(ifstream& infile) 
{
	infile >> this->size;	// first line represents size
	string s;
	int source;
	int dest;
	int weight;
	for (int i=0; i <=this->size; i++) 
	{
		data[i].setData(infile); // set first #size line as node data
	}

	for (;;) 
	{
		getline(infile, s);
		if (infile.eof()) break;
		source = s.at(0)-48; // get source
		if (source == 0 ) break;		
		stringstream linestream(s);
		getline(linestream, s,' ');
		linestream >> dest >> weight;	 // set destination and weight	
		insertEdge(source, dest, weight); // calling insert Edge 
	}
}
