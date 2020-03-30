/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */
#include <iostream>
#include <chrono>
#include <random>
#include <typeinfo>
using namespace std;

#define ALGORITHM_NAME ("Heap Sort") // The name of the algorithm used for sorting
#define RANDOM_SEED 2019 // Random Seed number to keep values constant.
#define ARRAY_SIZE 50000 // Set the size of the array to 50,000.
mt19937 gen(RANDOM_SEED); // Seed the mersenne twister random number generator
uniform_int_distribution<int> dist(-100000, 100000); // Set the random number distribution between -100,000 and 100,000 inclusive.

template<typename T>
void HeapSort(T A[]);
template<typename T>
void BuildMaxHeap(T A[]);
template<typename T>
void MaxHeapify(T A[], int i, int heapSize);
int Parent(int i);
int Left(int i);
int Right(int i);
template<typename T>
void PopulateArray(T A[]);
template<typename T>
void PrintArray(T A[]);

int main()
{
	int myArray[ARRAY_SIZE]; // An array to be sorted.
	PopulateArray(myArray); // Fill the array with random numbers.

	//PrintArray(myArray); // Display array before sorting.

	cout << "Sorting an array of type " << typeid(myArray).name() << " elements." << endl; // Print the type of the array and the amount of element in it.
	cout << "Algorithm: " << ALGORITHM_NAME << endl; // Print the name of the algorithm used.
	auto startTime = chrono::system_clock::now(); // Get the time before sorting.
	HeapSort(myArray); // Sort the array
	auto endTime = chrono::system_clock::now(); // Get the time after sorting.

	//PrintArray(myArray); // Display array after sorting.

	std::chrono::duration<double> diff = endTime - startTime; // Get the difference from start to end time

	cout << "Total Seconds : " << diff.count() << endl; // Print the time spent in seconds.
}



/// <summary>
/// Sort the array using heap sort algorithm
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n)
/// Heapsort(A)
///  BuildMaxHeap(A)
///  heapSize = lenght of A
///  for i = lenght of A - 1 to 1
///      swap A[0] and A[i]
///      heapSize = heapSize - 1
///      MaxHeapify(A,0,heapSize)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array to be sorted</param>
template<typename T> // can be of any type, custom types needs to implement GreaterThan operator '>'
void HeapSort(T A[])
{
	BuildMaxHeap(A);
	int heapSize = ARRAY_SIZE;
	for (int i = ARRAY_SIZE - 1; i >= 1; i--)
	{
		T temp = A[0];
		A[0] = A[i];
		A[i] = temp;
		heapSize--;
		MaxHeapify(A, 0, heapSize);
	}
}

/// <summary>
/// Place the max element as the root of the heap
/// run heapify on each nodes.
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n)
/// BuildMaxHeap(A)
///  for i = FLOOR[(length of A) / 2] down to 0
///     MaxHeapify(A,i,length of A)   
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array to be sorted</param>
template<typename T> // can be of any type, custom types needs to implement GreaterThan operator '>'
void BuildMaxHeap(T A[])
{
	for (int i = (ARRAY_SIZE) / 2; i >= 0; i--)
	{
		MaxHeapify(A, i, ARRAY_SIZE);
	}
}

/// <summary>
/// Makes sure that the node is the biggest one out of its childrens
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n)
/// (i is the index of the node to MaxHeapify)
/// (heapSize is the size of the heap to MaxHeapify)
/// MaxHeapify(A,i,heapSize)
///  l = Left(i)
///  r = Right(i)
///  if l < heapSize and A[l] > A[i]
///     largest = l
///  else
///     largest = i
///  if r < heapSize and A[r] > A[largest]
///     largest = r
///  if largest =/= i
///     swap A[i] and A[largest]
///     MaxHeapify(A,largest,heapSize)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array of the element to be heapified</param>
/// <param name="i">sub tree root index of the heap</param>
/// <param name="heapSize">the size of the heap</param>
template<typename T> // can be of any type, custom types needs to implement GreaterThan operator '>'
void MaxHeapify(T A[], int i, int heapSize)
{
	int l = Left(i);
	int r = Right(i);
	int largest;
	if (l < heapSize && A[l] > A[i])
	{
		largest = l;
	}
	else
	{
		largest = i;
	}
	if (r < heapSize && A[r] > A[largest])
	{
		largest = r;
	}
	if (largest != i)
	{
		T temp = A[largest];
		A[largest] = A[i];
		A[i] = temp;
		MaxHeapify(A, largest, heapSize);
	}
}

/// <summary>
/// Return the Parent element's index of the request element
/// Not used for sorting.
/// </summary>
/// <param name="i">index of requested element</param>
/// <returns>Parent's index of requested element</returns>
int Parent(int i)
{
	return (i / 2);
}

/// <summary>
/// Return the Left child element's index of the request element
/// </summary>
/// <param name="i">index of requested element</param>
/// <returns>Left child's index of requested element</returns>
int Left(int i)
{
	return (i * 2) + 1;
}

/// <summary>
/// Return the Right child element's index of the request element
/// </summary>
/// <param name="i">index of requested element</param>
/// <returns>Right child's index of requested element</returns>
int Right(int i)
{
	return (i * 2) + 2;
}

/// <summary>
/// Populate an array with random numbers between -100,000 to 100,000
/// </summary>
/// <param name="A">array to populate</param>
template<typename T> // can be of any type, custom types needs to implement explicit conversion to integer
void PopulateArray(T A[])
{
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		A[i] = dist(gen);
	}
}

/// <summary>
/// Print the array's elements
/// </summary>
/// <param name="A">array to be printed</param>
template<typename T> // can be of any type, custom type needs to overload Bitwise Left Shift '<<' operator
void PrintArray(T A[])
{
	cout << "---- Array of " << typeid(A).name() << " ----" << endl;
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (i != ARRAY_SIZE - 1)
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
