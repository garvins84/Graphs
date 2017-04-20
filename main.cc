/********************************************************************
  Author:        Dana Vrajitoru, IUSB, CS
  Class:         C243 Data Structures
  File name:     main.cc
  Last updated:  November 19, 2015.
  Description:   Testing the graph class.
*********************************************************************/

#include "graph.h"
#include <iostream>
using namespace std;

/********************************************************************
 Prototypes
*********************************************************************/

// Build the graph in the first example from class.
void makeGraph1(Graph &gr);
// Helper functions
void addCharVertex(Graph &gr, const char n);
void addCharEdge(Graph &gr, const char n1, const char n2);

// The main loop of the program.
void mainLoop(Graph &gr);
// Prints the menu options.
void printMenu();
// Executes the menu options.
bool executeMenu(Graph &gr, char option);

/********************************************************************
 Functions
*********************************************************************/

int main()
{
    Graph gr;
    makeGraph1(gr);
    gr.print();
    gr.makeEmpty();
    gr.read("graph1.txt");
    gr.print();
    mainLoop(gr);
    return 0;
} // main()

// Build the graph in the first example from class.
void makeGraph1(Graph &gr)
{
    for (char n='A'; n <= 'E'; n++) 
        addCharVertex(gr, n);
    addCharEdge(gr, 'A', 'B');
    addCharEdge(gr, 'A', 'D');
    addCharEdge(gr, 'A', 'E');
    addCharEdge(gr, 'B', 'C');
    addCharEdge(gr, 'B', 'D');
    addCharEdge(gr, 'C', 'D');
    addCharEdge(gr, 'C', 'E');
} // makeGraph1()

// Helper functions
void addCharVertex(Graph &gr, const char n)
{
    string name("A");
    name[0] = n;
    gr.addVertex(name);
} // addCharVertex()

void addCharEdge(Graph &gr, const char n1, const char n2)
{
    string name1("A"), name2("A");
    name1[0] = n1;
    name2[0] = n2;
    gr.addEdge(name1, name2);
} // addCharEdge()

// The main loop of the program.
void mainLoop(Graph &gr)
{
    bool quit=false;
    char answer;
    while (!quit) {
        printMenu();
        cin >> answer;
        cout << endl << endl;
        quit = executeMenu(gr, answer);
        cout << endl;
    }
} // mainLoop()

// Prints the menu options.
void printMenu()
{
    cout << "You can perform the following actions:" << endl
         << "R : read the graph from a file" << endl
		 << "W : write the contents of graph to a file" << endl
		 << "I : input number of nodes and add edges to the graph" << endl
         << "P : print the graph" << endl
         << "B : print the graph in breadth-first order" << endl
         << "D : print the graph in depth-first order" << endl
         << "E : empty the graph" << endl
         << "Q : quit" << endl
         << endl << "Enter your choice: ";
} // printMenu()

// Executes the menu options.
bool executeMenu(Graph &gr, char option)
{
    char buffer[80];
    switch (option) {
    case 'r':
    case 'R':
        gr.makeEmpty();
        cout << "Enter the input file name" << endl;
        cin >> buffer;
        gr.read(buffer);
        break;
    case 'p':
    case 'P':
        gr.print();
        break;
    case 'w':
    case 'W':
	cout << "Enter the output file name" << endl;
	cin >> buffer;
	gr.write(buffer);
	break;
    case 'i':
    case 'I':
	gr.input();
	break;
    case 'b':
    case 'B':
        gr.printBf();
        break;
    case 'd':
    case 'D':
        gr.printDf();
        break;
    case 'e':
    case 'E':
        gr.makeEmpty();
        break;
    case 'q':
    case 'Q':
        return true;
    default:
        cout << "Unknown option, try again" << endl;
    }
    return false;
} // executeMenu()
