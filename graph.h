/********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     graph.h
  Last updated:  November 19, 2015.
  Description:   Definition of a class that implements a graph.
*********************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <list>
#include <string>
#include <queue>
#include <stack>
using namespace std;

typedef list<int> ListInt;
typedef ListInt::iterator ListIntIter;

class Graph 
{

protected:
    struct vertex 
    {
        ListInt edgeList;
        string name;
    };

    int numVertices, numEdges;
    bool directed;
	vector<bool> markedVertice;
    vector<vertex> vertices;

    int index(const string name);

public:
    // Constructor with specified number of vertices. The parameter has
    // a default value of 0.
    Graph(int nv = 0);
    // destructor
    ~Graph();

    // Starts the graph over.
    void makeEmpty();

    // Tells us if the graph is directed.
    bool isDirected();

    // Set the direction flag to directed or undirected.
    void setDirected();
    void setUndirected();

    // Initialize the data structure for the specified number of
    // vertices.
    void init(int nv);

    // Adds a vertex with the specified index. It also adds all the
    // intermediate vertices from the current position to the new
    // one. It creates labels with uppercase letters in order.
    void addVertex(int index);

    // Adds a vertex with a given name.
    void addVertex(const string the_name);

    // Adds an edge based on vertex names. If the graph is undirected,
    // it adds the edge in both directions.
    void addEdge(char *name1, char *name2);

    // Adds an edge based on vertex names. If the graph is undirected,
    // it adds the edge in both directions.
    void addEdge(const string name1, const string name2);

    // Adds an edge between vertices identified by their inde.x
    void addEdge(const int index1, const int index2);

    // Reads the graph from a file.
    void read(const char *filename);

    void print();

    // Writes the graph to a file that is compatible with the function read.
    void write(const char *filename);

    // Inputs a graph from the user. First it asks for the number
    // of vertices, then call the function init with the number of
    // vertices to automatically generate the labels as uppercase
    // letters, and then ask the use to input the edges. The user will
    // be expected to enter uppercase letters to identify the edges, and
    // anything else will end the input process.
    void input();

    // Print the graph in breadth-first order.
    void printBf();

    // Print the graph in depth-first order.
    void printDf();
    void recursivePrintDf(int i);

    // takes a user inputted vertex name and checks if it is valid.
    bool isValidVertice(string name);

    // checks if a given edge already exists.
    bool edgeExists(int index1, int index2);

    // initializes the markedVertex vector.
    void initializeMarkArray(vector<bool> &markedVertice);
};

#endif
