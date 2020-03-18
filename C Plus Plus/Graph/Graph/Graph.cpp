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

#define QUEUE_SIZE 10000000 // size of queue for speed testing
//template <typename T>
void testargs(initializer_list<int> args) {
    vector<int> test;
    for (auto a :args)
    {
        cout << a << endl;
        test.push_back(a);
	}
    cout << "find" << endl;
    int x = 3;
    auto found = find_if(test.begin(), test.end(), [x](int i) {return i == x; });
    //int s = *found;
    if (found != test.end())
    {
        cout <<  *found << endl;
    }
    else
    {
        cout << "not found" << endl;
    }
}

int main()
{
    testargs({ 2, 2, 5, 3, 3, 6 });
	//testargs({ "test", "testing" });
    auto test = ListGraph({ 2,3,4,5 });
    test.AddEdge(2, 3);
    test.AddEdge(3, 4);
    test.AddEdge(4, 5);
	test.AddEdge(2, 4);
	test.AddEdge(4, 2);
    test.BreadthFirstSearch(2);
    test.PrintPath(2, 5);
    test.BreadthFirstSearch(3);
    test.PrintPath(3, 2);
    test.PrintEdges();
}
