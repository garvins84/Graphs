/********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     graph.cc
  Last updated:  November 19, 2015.
  Description:   Implementation of the graph class.
*********************************************************************/

#include "graph.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>

// A sort of hash function for the names - works only if the names are
// in sequence, all of them starting with an uppercase, and none of
// them having the same starting letter. Like, 'A', 'B', 'C', etc.
int Graph::index(const string name)
{
    return int(name[0] - 'A');
} // Graph::index()

// Default constructor - makes an empty undirected graph.
Graph::Graph(int nv)
{
    numVertices = 0;
    numEdges = 0;
    directed = false;
    if (nv>0)
        init(nv);
} // Graph::Graph()


// Destructor - empty the lists and the vector.
Graph::~Graph()
{
    makeEmpty();
} // Graph::~Graph()

// Starts the graph over.
void Graph::makeEmpty()
{
    directed = false;
    if (numVertices) 
    {
        for (int i=0; i<numVertices; i++) 
            vertices[i].edgeList.clear();
        vertices.erase(vertices.begin(), vertices.end());
        numVertices = 0;
        numEdges = 0;
    }
} // Graph::makeEmpty()

// Tells us if the graph is directed.
bool Graph::isDirected()
{
    return directed;
} // Graph::isDirected()

// Set the direction flag to directed or undirected.
void Graph::setDirected()
{
    directed = true;
} // Graph::setDirected()

void Graph::setUndirected()
{
    directed = false;
} // Graph::setUndirected()

// Initialize the data structure for the specified number of vertices.
void Graph::init(int nv)
{
    addVertex(nv-1); // Last index we need
} // Graph::init()



// Adds a vertex with the specified ind_nex. It also adds all the
// intermediate vertices from the current position to the new one. It
// creates labels with uppercase letters in order.
void Graph::addVertex(int index)
{
    string s = "A";
    for(int i = numVertices; i<=index; i++) 
    {
        s[0] = char('A' + i);
        addVertex(s);
    }
} // Graph::addVertex()

// Adds a vertex with a given name.
void Graph::addVertex(const string theName)
{
    vertex newVertex;
    newVertex.name = theName;
    vertices.push_back(newVertex);
    numVertices++;
}

// Adds an edge based on vertex names. If the graph is undirected,
// it adds the edge in both directions.
void Graph::addEdge(char *name1, char *name2)
{
    int index1 = index(string(name1));
    int index2 = index(string(name2));
    if (index1 > numVertices)
        addVertex(index1);
    if (index2 >= numVertices)
        addVertex(index2);
    addEdge(index1, index2);
} // Graph::addEdge()

// Adds an edge based on vertex names. If the graph is undirected,
// it adds the edge in both directions.
void Graph::addEdge(const string name1, const string name2)
{
    int index1 = index(name1);
    int index2 = index(name2);
    if (index1 >= numVertices)
        addVertex(name1);
    if (index2 >= numVertices)
        addVertex(name2);
    addEdge(index1, index2);
} // Graph::addEdge()

// Adds an edge between vertices identified by their index
void Graph::addEdge(const int index1, const int index2)
{
	if(!edgeExists(index1, index2))
	{
		vertices[index1].edgeList.push_back(index2);
		if (!directed)
			vertices[index2].edgeList.push_back(index1);
		numEdges++;  
	}
} // Graph::addEdge()

// Reads the graph from a file
void Graph::read(const char *filename)
{
    ifstream fin(filename);
    char buffer[20], buffer1[20];
    int nrv;
    fin >> buffer; // read the letter U or D
    if (buffer[0] == 'd' || buffer[0] == 'D')  
        directed = true;
    else
        directed = false;
    fin >> nrv; // read the number of vertices

    for (int i=0; i<nrv; i++) // read all the names of vertices
    {
        fin >> buffer; // read the vertex name
        addVertex(string(buffer)); // this will also update numVertices
    }

    // read all the edges until the end of the file 
    while (!fin.eof() && fin.good()) // we have not reached the end of the file
    {
        fin >> buffer;
        if (strlen(buffer) && fin.good()) // was the first name read correctly?
        {
            fin >> buffer1;
            if (strlen(buffer) && strlen(buffer1))  // how about the second?
            {
                // we know both names are valid here
                buffer[strlen(buffer)-1]='\0'; // Deleting the ','
                addEdge(string(buffer), string(buffer1));
            }
        }
    }
    fin.close();
} // Graph::read()

// Simple print of the graph.
void Graph::print()
{
    int i;
    if (directed)
        cout << "The graph is directed" << endl;
    else
        cout << "The graph is undirected" << endl;
    cout << "The graph contains " << numVertices
         << " vertices and " << numEdges << " edges" << endl;

    if (numVertices) 
    {
        // print all the names
        cout << "The vertex names are: ";
        for (i=0; i<numVertices; i++)
            cout << vertices[i].name << ' ';

        // print all the adjacency lists
        cout << endl 
             << "The adjacency list for each vertex is:" << endl;
        for (i=0; i<numVertices; i++) 
        {
            cout << "vertex " << i << ": ";
            ListIntIter iter;
            iter = vertices[i].edgeList.begin();
            while (iter != vertices[i].edgeList.end()) 
            {
                // here we have an edge from i to *iter.
                cout << *iter << ' '; // output the content of the node
                iter++;               // move to the next node
            }
            cout << endl;
        }
    }
} // Graph::print()

// Functions to be implemented by the students.

// Writes the graph to a file that is compatible with the function read.
void Graph::write(const char *filename)
{
    ofstream fout;
    fout.open (filename);

    if (directed)
        fout << 'D' << endl
	     << numVertices << endl;
    else
	fout << 'U' << endl
	     << numVertices << endl;
	
    if (numVertices) 
    {
        for (int i=0; i<numVertices; i++)
	    fout << vertices[i].name << endl;
    }
    for (int i=0; i<numVertices; i++) 
    {
        ListIntIter iter;
        iter = vertices[i].edgeList.begin();  // use iterator to traverse edges
        while (iter != vertices[i].edgeList.end()) 
        {
	    if (directed)	       // output all edges for the given vertex
	    {
	        fout << vertices[i].name ;
		fout << ", ";
		fout << vertices[*iter].name << endl;// output the vert to file
		iter++;                              // move to the next node
	    }
	    else                                     // graph is not directed
	    {
	        if (i < *iter)                     // only print edges one way
		{
		    fout << vertices[i].name;
		    fout << ", ";
		    fout << vertices[*iter].name << endl;   // output to file
	        }
		iter++;                              // move to the next node
	    }
        }
    }
        fout.close();
}


// Inputs a graph from the user. First it should ask for the number of
// vertices, then call the function init with the number of vertices
// to automatically generate the labels as uppercase letters, and then
// ask the use to input the edges. The user will be expected to enter
// uppercase letters to identify the edges, and anything else should
// end the input process.
void Graph::input()
{
    int inputVertices;
    char direction;
    string name1("A"),  name2("A");
    bool validName = true;
    makeEmpty();		    //start with a fresh graph
    do                                                                             {
        cout << "Please type 'U' for undirected or 'D' for directed graph. ";
        cin >> direction;
	direction = toupper(direction);
    }while (direction != 'U' && direction != 'D');

    if (direction == 'D')
        setDirected();
    else 
	setUndirected();

    cout << "Please enter the number of vertices\n";
    cin >> inputVertices;
    init(inputVertices);  // initialize and label vertices with capital letters

    cout << "The following vertice names have been generated:\n";
    for (int i = 0; i < numVertices; ++i)
        cout << vertices[i].name << endl;
    cout << endl;

    cout << "Set the edges for the vertices." 
         << "Acceptable input is uppercase letters," 
         <<  "anything else will end the input proccess.\n";
    while(validName)
    {
        cout << "Please enter the source vertex\n";
	cin >> name1[0];
	validName = isValidVertice(name1);
	if(validName)
	{
	    cout << "Please enter the destination vertex\n";
	    cin >> name2[0];
	    validName = isValidVertice(name2);
	    if(validName && name1[0] != name2[0])
	        addEdge(name1,name2);
	    else
	        cin.get();
	}
        else
	    cin.get();
    }
} // Graph::input()

// driver function for printDf
void Graph::printDf() 
{
    initializeMarkArray(markedVertice);
    int i = 0;
    recursivePrintDf(i);
}  // Graph::printDf()
                      

// prints the graph depth first, i.e
// the source vertex, then its closest neighbor,
// and that neighbors closest neighbors, and etc for each unmarked neighbor.
void Graph::recursivePrintDf(int i) 
{   
    markedVertice[i] = true;		 // mark the vertice at current index
    cout << vertices[i].name;
    ListIntIter iter = vertices[i].edgeList.begin();
    while (iter != vertices[i].edgeList.end()) 
    {
        if (!markedVertice[*iter])// check if the vertex at iter is  marked
            recursivePrintDf (*iter); 
        iter++;
    }
}  // Graph::recursivePrintDf()

// prints the graph breadth first, i.e. 
// the source vertex, then its neighbors,
// then its neighbors neighbors, etc.
void Graph::printBf()
{
    initializeMarkArray(markedVertice);
    int i = 0;
    queue<string> bread;							   
    markedVertice[i] = true;		   // first vertex has been travelled
    bread.push(vertices[i].name);	   // first vertex is enqueued
	
    while(!(bread.empty()))
    {
        i = index(bread.front()); // i contains the value of the index at front
	cout << bread.front();
	bread.pop();
        ListIntIter iter;  // traverse the list of neighbors at vertex
        iter = vertices[i].edgeList.begin();
        while (iter != vertices[i].edgeList.end()) 
        {
	  // if vertex isn't marked, enqueue it and mark it
	    if (markedVertice[*iter] == false)
	    {
	        markedVertice[*iter] = true;
		bread.push(vertices[*iter].name); 
	    }
	    iter++;			      // move to the next node
        }         
    }
} // Graph::printBf()


// function simply takes a user inputted vertex
// and makes sure it is valid, i.e. an upper case
// letter
bool Graph::isValidVertice(const string name)
{
    if(!isupper(name[0]))
        return false;
    return true;
} // Graph::isValidVertice()

// function checks if there is already an edge
// between two vertices. This prevents an edge
// from being added twice.
bool Graph::edgeExists(int index1, int index2)
{
    ListIntIter iter;
    iter = vertices[index1].edgeList.begin(); // travel list of source vertex
    while (iter != vertices[index1].edgeList.end()) 
    {
        if (*iter == index2)               // match edge already exists in list
	    return true;
	++iter;
    }
    return false;
} // Graph::edgeExists()

// resizes the vector markedVertice if need be. Also
// initializes each element to false.
void Graph::initializeMarkArray(vector<bool> & markedVertice)
{
    if (markedVertice.size() != numVertices)
        markedVertice.resize(numVertices);
    for (int i = 0; i < numVertices; ++i)
        markedVertice[i] = false;
} // Graph::initializeMarkArray()
