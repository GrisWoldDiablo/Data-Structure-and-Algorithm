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

#define	DATA_STRUCTURE_NAME ("Graph Search") // The name of the data structure
#define RANDOM_SEED 2019 // Random Seed number to keep values constant.
mt19937 gen(RANDOM_SEED); // Seed the mersenne twister random number generator
uniform_int_distribution<int> dist(-100000, 100000); // Set the random number distribution between -100,000 and 100,000 inclusive.

#define GRAPH_SIZE 100000 // size of graph for speed testing

int main()
{
    auto test = ListGraph({ 1,2,3,4,5,6,7 });
    test.AddEdge(2, 3);
    test.AddEdge(3, 4);
    test.AddEdge(4, 5);
	test.AddEdge(2, 4);
	test.AddEdge(4, 2);
	test.AddEdge(2, 1);
	test.AddEdge(1, 6);
	test.AddEdge(7, 1);

    //test.PrintVertices();
    test.BreadthFirstSearch(2);
    test.PrintVertices();
    test.PrintPath(2, 5);
	test.BreadthFirstSearch(3);
	test.PrintVertices(); 
    test.PrintPath(3, 2);
    test.PrintPath(3, 6);
    test.BreadthFirstSearch(7);
    test.PrintPath(7, 6);
	test.PrintVertices();
    test.PrintEdges();
    //test.PrintVertices();

}
