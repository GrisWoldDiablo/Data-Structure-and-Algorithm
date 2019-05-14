/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */
#include <iostream>
#include <chrono>
#include <typeinfo>
#include "TheQueue.h"
using namespace std;

template<class T>
void PopulateQueue(TheQueue<T>& Q, int x);
template<class T>
void PrintQueue(TheQueue<T>& Q);
template<typename T>
void PrintArray(T A[], int arraySize);

#define	DATA_STRUCTURE_NAME ("Queue") // The name of the data structure
#define QUEUE_SIZE 10000000 // size of queue for speed testing

int main()
{
	cout << "---- Data structure : " << DATA_STRUCTURE_NAME << " ----" << endl; // Print the data structure name
	TheQueue<int> myQueue; // Create a new queue
	cout << "Declared a " << typeid(myQueue).name() << "." << endl; // Print the name of the class of the stack
	PopulateQueue(myQueue, 10); // Populate the queue with x elements
	auto* myArray = myQueue.ToArray(); // Convert queue to array
	cout << "queue to array: " << endl;
	PrintArray(myArray, 10); // Print the array
	cout << "Peeking the queue, key: " << myQueue.Peek() << " is a the beginning of the queue." << endl; // Peek the queue
	PrintQueue(myQueue); // Print all the elements of the queue

	// ---- Class Speed Test portion -----
	cout << "\nTesting queue speed with " << QUEUE_SIZE << " elements." << endl;
	myQueue.Clear(); // Reinitialize the queue
	delete[] myArray; // Reinitialize the array

	// Speed test: Enqueue QUEUE_SIZE elements to the queue
	auto startTime = chrono::system_clock::now(); // Get the time before enqueuing.
	for (int i = 0; i < QUEUE_SIZE; i++) // Enqueue QUEUE_SIZE elements to the queue
	{
		myQueue.Enqueue(i); // Enqueue i to the queue
	}
	auto endTime = chrono::system_clock::now(); // Get the time after enqueuing.
	std::chrono::duration<double> diff = endTime - startTime; // Get the difference from start to end time
	auto totalDiff = diff; // Get the time spent for enqueuing
	cout << "- Enqueuing elements -" << endl;
	cout << "Total seconds : " << diff.count() << endl; // Print the time spent in seconds

	// Speed test: Convert the queue to an array
	startTime = chrono::system_clock::now(); // Get the time before converting.
	myArray = myQueue.ToArray();
	endTime = chrono::system_clock::now(); // Get the time after converting.
	diff = endTime - startTime; // Get the difference from start to end time
	totalDiff += diff; // Add the time spent for converting
	cout << "- Converting queue to array -" << endl;
	cout << "Total seconds : " << diff.count() << endl; // Print the time spent in seconds
	delete[] myArray; // Reinitialize the array

	// Speed test: Dequeue all elements from the queue
	startTime = chrono::system_clock::now(); // Get the time before dequeuing.
	while (!myQueue.Empty()) // Dequeue elements until the dequeue is empty
	{
		myQueue.Dequeue(); // Dequeue an element from the queue 
	}
	endTime = chrono::system_clock::now(); // Get the time after dequeuing.
	diff = endTime - startTime; // Get the difference from start to end time
	totalDiff += diff; // Add the time spent for dequeuing
	cout << "- Dequeuing all elements -" << endl;
	cout << "Total seconds : " << diff.count() << endl; // Print the time spent in seconds

	cout << "- Class Speed for all 3 tests -" << endl;
	cout << "Total seconds : " << totalDiff.count() << endl; // Print the time spent in seconds for all test combined
}

/// <summary>
/// Populate a queue with ascending values from 0 to x (exclusive)
/// </summary>
/// <param name="Q">queue to populate</param>
/// <param name="x">the amount of element(s) to add to the queue</param>
template<class T> // can be of any type, custom type needs to implement explicit conversion to integer
void PopulateQueue(TheQueue<T> &Q, int x)
{
	cout << "Enqueuing " << x << " element(s) to the queue." << endl;
	cout << "Added: ";
	for (int i = 0; i < x; i++)
	{
		if (i != x - 1)
		{
			cout << i << ",";
		}
		else
		{
			cout << i << " to the queue in that order." << endl;
		}
		Q.Enqueue(i);
	}
}

/// <summary>
/// Emtpy the queue and print all its elements
/// </summary>
/// <param name="Q">queue to be printed</param>
template<class T> // can be of any type, custom type needs to overload Bitwise Left Shift '<<' operator
void PrintQueue(TheQueue<T> &Q)
{
	cout << "There is " << Q.Count() << " element(s) in the queue." << endl;
	cout << "Dequeuing all the element(s) of the stack: ";
	while (!Q.Empty())
	{
		if (Q.Count() != 1)
		{
			cout << Q.Dequeue() << ",";
		}
		else
		{
			cout << Q.Dequeue() << endl;
		}
	}
}

/// <summary>
/// Print the array's elements
/// </summary>
/// <param name="A">array to be printed</param>
/// <param name="arraySize">size of the array</param>
template<typename T> // can be of any type, custom type needs to overload Bitwise Left Shift '<<' operator
void PrintArray(T A[], int arraySize)
{
	cout << "---- Array of " << typeid(A).name() << " ----" << endl;
	for (int i = 0; i < arraySize; i++)
	{
		if (i != arraySize - 1)
		{
			cout << A[i] << ",";
		}
		else
		{
			cout << A[i];
		}
	}
	cout << endl << "---- ----" << endl;
}