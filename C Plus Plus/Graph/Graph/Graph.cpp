/*
 * Author: Alexandre Lepage
 * Date: March 2020
 */
#include <iostream>
#include <chrono>
#include <random>
#include <typeinfo>
#include "ListGraph.h"

using namespace std;

void PopulateArray(int A[], int size);
void PopulateArrayRandom(int A[], int arraySize, int randomRangeMin, int randomRangeMax);
void AddEdges(AbstractGraph& G, int A[], int B[], int amount, int minWeight, int maxWeight);

#define	DATA_STRUCTURE_NAME ("Graph Search") // The name of the data structure
#define RANDOM_SEED 2019 // Random Seed number to keep values constant.
mt19937 gen(RANDOM_SEED); // Seed the mersenne twister random number generator

#define GRAPH_SIZE_LARGE 25000 // size of graph for speed testing
#define AMOUNT_OF_EDGES_LARGE GRAPH_SIZE_LARGE * 3 // The amount of edges for testing
#define GRAPH_SIZE_SMALL 3000 // size of graph for speed testing
#define AMOUNT_OF_EDGES_SMALL GRAPH_SIZE_SMALL * 2 // The amount of edges for testing


//#define DEBUG
#ifdef DEBUG
void BFSTest()
{
	cout << "---BFS---" << endl;
	auto test = ListGraph({ 1,2,3,4,5,6 });
	test.AddEdge(1, 2);
	test.AddEdge(1, 4);
	test.AddEdge(2, 5);
	test.AddEdge(3, 5);
	test.AddEdge(3, 6);
	test.AddEdge(4, 2);
	test.AddEdge(5, 4);
	test.AddEdge(6, 6);
	test.BreadthFirstSearch(1);
	test.PrintPath(1, 5);
	test.PrintVertices();
	test.PrintEdges();
	test.PrintTimestamps();

	//test.PrintVertices();
	//test.PrintEdges();
	//test.PrintVertices();
	//test.PrintPath(2, 5);
	//test.BreadthFirstSearch(3);
	//test.PrintVertices();
	//test.PrintPath(3, 2);
	//test.PrintPath(3, 6);
	//test.BreadthFirstSearch(7);
	//test.PrintVertices();
	//test.PrintEdges();
	//test.PrintPath(7, 6);
	//test.PrintVertices();
	cout << "---BFS---" << endl;
}
void DFSTest()
{
	cout << "---DFS---" << endl;
	//int myArray[GRAPH_SIZE_ITERATIVE];
	//int myArraySource[AMOUNT_OF_EDGES_ITERATIVE];
	//int myArrayDestination[AMOUNT_OF_EDGES_ITERATIVE];
	//PopulateArray(myArray, GRAPH_SIZE_ITERATIVE);
	//PopulateArrayRandom(myArraySource, AMOUNT_OF_EDGES_ITERATIVE, 0, GRAPH_SIZE_ITERATIVE - 1);
	//PopulateArrayRandom(myArrayDestination, AMOUNT_OF_EDGES_ITERATIVE, 0, GRAPH_SIZE_ITERATIVE - 1);

	//ListGraph test = ListGraph(myArray, GRAPH_SIZE_ITERATIVE);
	ListGraph test = ListGraph({ 1,2,3,4,5,6 });
	//AddEdges(test, myArraySource, myArrayDestination, AMOUNT_OF_EDGES_ITERATIVE);
	test.AddEdge(1, 2);
	test.AddEdge(1, 4);
	test.AddEdge(2, 5);
	test.AddEdge(3, 5);
	test.AddEdge(3, 6, 2);
	test.AddEdge(4, 2);
	test.AddEdge(5, 4);
	test.AddEdge(6, 6);
	//test.PrintPath(1, 4);
	test.DepthFirstSearch();
	//test.PrintVertices();
	//system("pause");
	//system("cls");
	test.PrintEdges();
	test.PrintTimestamps();
	cout << "---" << endl;
	test.DepthFirstSearchKey(1);
	//test.DepthFirstSearchIterative(1);
	test.PrintTimestamps();
	cout << "---DFS---" << endl;
}
void BLFTest()
{
	ListGraph test = ListGraph({ 1,2,3,4,5 });
	//AddEdges(test, myArraySource, myArrayDestination, AMOUNT_OF_EDGES_ITERATIVE);
	test.AddEdge(1, 2, 6);
	test.AddEdge(1, 4, 7);
	test.AddEdge(2, 3, 5);
	test.AddEdge(2, 4, 8);
	test.AddEdge(2, 5, -4);
	test.AddEdge(3, 2, -2);
	test.AddEdge(4, 3, -3);
	test.AddEdge(4, 5, 9);
	test.AddEdge(5, 1, 2);
	test.AddEdge(5, 3, 7);

	//cout << test.BellmanFord(1) << endl;
	cout << (test.BellmanFord(1) == true ? "TRUE" : "FALSE") << endl;

	test.PrintPath(1, 5);
}
void DIJKTest() {
	ListGraph test = ListGraph({ 1,2,3,4,5 });
	//AddEdges(test, myArraySource, myArrayDestination, AMOUNT_OF_EDGES_ITERATIVE);
	test.AddEdge(1, 2, 10);
	test.AddEdge(1, 4, 5);
	test.AddEdge(2, 3, 1);
	test.AddEdge(2, 4, 2);
	test.AddEdge(3, 5, 4);
	test.AddEdge(4, 2, 3);
	test.AddEdge(4, 3, 9);
	test.AddEdge(4, 5, 2);
	test.AddEdge(5, 1, 7);
	test.AddEdge(5, 3, 6);
	test.Dijkstra(1);
	test.PrintPath(1, 3);
}
#endif // DEBUG

class MyCompare {
public:
	//template<typename T>
	bool operator()(int* a, int* b) {
		return (*a) < (*b);
	}
};

int main()
{
#ifdef DEBUG
	//BFSTest();
	//DFSTest();
	//BLFTest();
	DIJKTest();
	return 1;
#endif // DEBUG

	cout << "---- Data structure : " << DATA_STRUCTURE_NAME << " ----" << endl; // Print the data structure name
	// ---- Class Speed Test portion -----

	// Speed test: declaring a ListGraph.
	cout << "\nTesting graph speed with " << GRAPH_SIZE_LARGE << " vertices and " << AMOUNT_OF_EDGES_LARGE << " edges." << endl;
	int myArray[GRAPH_SIZE_LARGE];
	int myArraySource[AMOUNT_OF_EDGES_LARGE];
	int myArrayDestination[AMOUNT_OF_EDGES_LARGE];
	PopulateArray(myArray, GRAPH_SIZE_LARGE);
	PopulateArrayRandom(myArraySource, AMOUNT_OF_EDGES_LARGE, 0, GRAPH_SIZE_LARGE - 1);
	PopulateArrayRandom(myArrayDestination, AMOUNT_OF_EDGES_LARGE, 0, GRAPH_SIZE_LARGE - 1);


	cout << "- Declaring a ListGraph test -" << endl;
	auto startTime = chrono::system_clock::now(); // Get the time before declaration.
	ListGraph myListGraph(myArray, GRAPH_SIZE_LARGE);
	auto endTime = chrono::system_clock::now(); // Get the time after declaration.
	std::chrono::duration<double> diff = endTime - startTime; // Get the difference from start to end time
	auto totalDiff = diff; // Get the time spent for declaring.
	cout << "Total seconds : " << diff.count() << endl; // Print the time spent in seconds

	// Speed test: adding an edge to each vertices.
	cout << "- Adding edges -" << endl;
	startTime = chrono::system_clock::now(); // Get the time before adding the edges.
	AddEdges(myListGraph, myArraySource, myArrayDestination, AMOUNT_OF_EDGES_LARGE, 1, 100);
	endTime = chrono::system_clock::now(); // Get the time after adding the edges.
	diff = endTime - startTime; // Get the difference from start to end time
	totalDiff += diff; // Get the time spent adding the edges.
	cout << "Total seconds : " << diff.count() << endl; // Print the time spent in seconds

	// Speed test: performing breadth first search.
	cout << "- Breadth First Search -" << endl;
	startTime = chrono::system_clock::now(); // Get the time before BFS.
	myListGraph.BreadthFirstSearch(0); // Perform the search
	endTime = chrono::system_clock::now(); // Get the time after BFS.
	diff = endTime - startTime; // Get the difference from start to end time
	totalDiff += diff; // Get the time spent doing BFS.
	cout << "Total seconds : " << diff.count() << endl; // Print the time spent in seconds

	// Speed test: performing depth first search iterative.
	cout << "- Depth First Search Iterative -" << endl;
	startTime = chrono::system_clock::now(); // Get the time before BFS.
	myListGraph.DepthFirstSearchIterative(); // Perform the search
	endTime = chrono::system_clock::now(); // Get the time after BFS.
	diff = endTime - startTime; // Get the difference from start to end time
	totalDiff += diff; // Get the time spent doing BFS.
	cout << "Total seconds : " << diff.count() << endl; // Print the time spent in seconds

														// Speed test: performing depth first search single source iterative.
	cout << "- Depth First Search Single Source Iterative -" << endl;
	startTime = chrono::system_clock::now(); // Get the time before BFS.
	myListGraph.DepthFirstSearchIterativeKey(0); // Perform the search
	endTime = chrono::system_clock::now(); // Get the time after BFS.
	diff = endTime - startTime; // Get the difference from start to end time
	totalDiff += diff; // Get the time spent doing BFS.
	cout << "Total seconds : " << diff.count() << endl; // Print the time spent in seconds

	// Speed test: performing dijkstra's search.
	cout << "- Dijkstra's -" << endl;
	startTime = chrono::system_clock::now(); // Get the time before BFS.
	myListGraph.Dijkstra(0); // Perform the search
	endTime = chrono::system_clock::now(); // Get the time after BFS.
	diff = endTime - startTime; // Get the difference from start to end time
	totalDiff += diff; // Get the time spent doing BFS.
	cout << "Total seconds : " << diff.count() << endl; // Print the time spent in seconds

	cout << "\nTesting graph speed with " << GRAPH_SIZE_SMALL << " vertices and " << AMOUNT_OF_EDGES_SMALL << " edges." << endl;
	int myArray2[GRAPH_SIZE_SMALL];
	int myArraySource2[AMOUNT_OF_EDGES_SMALL];
	int myArrayDestination2[AMOUNT_OF_EDGES_SMALL];
	PopulateArray(myArray2, GRAPH_SIZE_SMALL);
	PopulateArrayRandom(myArraySource2, AMOUNT_OF_EDGES_SMALL, 0, GRAPH_SIZE_SMALL - 1);
	PopulateArrayRandom(myArrayDestination2, AMOUNT_OF_EDGES_SMALL, 0, GRAPH_SIZE_SMALL - 1);

	cout << "- Declaring a ListGraph for test -" << endl;
	startTime = chrono::system_clock::now(); // Get the time before declaration.
	ListGraph myListGraph2(myArray2, GRAPH_SIZE_SMALL);
	endTime = chrono::system_clock::now(); // Get the time after declaration.
	diff = endTime - startTime; // Get the difference from start to end time
	totalDiff += diff; // Get the time spent for declaring.
	cout << "Total seconds : " << diff.count() << endl; // Print the time spent in seconds

	// Speed test: adding an edge to each vertices.
	cout << "- Adding edges -" << endl;
	startTime = chrono::system_clock::now(); // Get the time before adding the edges.
	AddEdges(myListGraph2, myArraySource2, myArrayDestination2, AMOUNT_OF_EDGES_SMALL, -100, 100);
	endTime = chrono::system_clock::now(); // Get the time after adding the edges.
	diff = endTime - startTime; // Get the difference from start to end time
	totalDiff += diff; // Get the time spent adding the edges.
	cout << "Total seconds : " << diff.count() << endl; // Print the time spent in seconds

	// Speed test: performing breadth first search recursive.
	cout << "- Depth First Search Recursive -" << endl;
	startTime = chrono::system_clock::now(); // Get the time before BFS.
	myListGraph2.DepthFirstSearch(); // Perform the search
	endTime = chrono::system_clock::now(); // Get the time after BFS.
	diff = endTime - startTime; // Get the difference from start to end time
	totalDiff += diff; // Get the time spent doing BFS.
	cout << "Total seconds : " << diff.count() << endl; // Print the time spent in seconds

	// Speed test: performing breadth first search recursive.
	cout << "- Depth First Search Recursive Single Source-" << endl;
	startTime = chrono::system_clock::now(); // Get the time before BFS.
	myListGraph2.DepthFirstSearchKey(0); // Perform the search
	endTime = chrono::system_clock::now(); // Get the time after BFS.
	diff = endTime - startTime; // Get the difference from start to end time
	totalDiff += diff; // Get the time spent doing BFS.
	cout << "Total seconds : " << diff.count() << endl; // Print the time spent in seconds

	// Speed test: performing Bellman-Ford search.
	cout << "- Bellman-Ford Search -" << endl;
	startTime = chrono::system_clock::now(); // Get the time before BFS.
	bool bfResult = myListGraph2.BellmanFord(0); // Perform the search
	endTime = chrono::system_clock::now(); // Get the time after BFS.
	diff = endTime - startTime; // Get the difference from start to end time
	totalDiff += diff; // Get the time spent doing BFS.
	cout << "Result: " << (bfResult == true ? "TRUE" : "FALSE") << endl;
	cout << "Total seconds : " << diff.count() << endl; // Print the time spent in seconds

	cout << "\n- Class Speed for all tests -" << endl;
	cout << "Total seconds : " << totalDiff.count() << endl; // Print the time spent in seconds for all test combined
}

/// <summary>
/// Populate an array
/// </summary>
/// <param name="A">array to populate</param>
/// <param name="size">size of the array</param>
void PopulateArray(int A[], int size)
{
	for (int i = 0; i < size; i++)
	{
		A[i] = i;
	}
}

/// <summary>
/// Populate an array with random numbers with a specific range
/// </summary>
/// <param name="A">array to populate</param>
/// <param name="arraySize">size of the array</param>
/// <param name="randomRangeMin">lower random boundary</param>
/// <param name="randomRangeMax">higher random boudary</param>
void PopulateArrayRandom(int A[], int arraySize, int randomRangeMin, int randomRangeMax)
{
	uniform_int_distribution<int> dist(randomRangeMin, randomRangeMax); // Set the random number distribution between randomRangeMin and randomRangeMax inclusively.

	for (int i = 0; i < arraySize; i++)
	{
		A[i] = dist(gen);
	}
}

/// <summary>
/// Add edges to a graph
/// </summary>
/// <param name="G">Grap to add edges to</param>
/// <param name="A">array containing the edge's source key</param>
/// <param name="B">array containing the edge's destination key </param>
/// <param name="amount">the quantity of edges to add</param>
void AddEdges(AbstractGraph& G, int A[], int B[], int amount, int minWeight, int maxWeight)
{
	uniform_int_distribution<int> dist(minWeight, maxWeight); // Set the random number distribution between minWeight and maxWeight inclusively.

	for (int i = 0; i < amount; i++)
	{
		G.AddEdge(A[i], B[i], dist(gen));
	}
}
