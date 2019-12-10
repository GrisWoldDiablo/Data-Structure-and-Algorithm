/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */
#include <iostream>
#include <chrono>
#include <random>
#include <typeinfo>
using namespace std;

#define ALGORITHM_NAME ("Bubble Sort") // The name of the algorithm used for sorting
#define RANDOM_SEED 2019 // Random Seed number to keep values constant.
#define ARRAY_SIZE 50000 // Set the size of the array to 50,000.
mt19937 gen(RANDOM_SEED); // Seed the mersenne twister random number generator
uniform_int_distribution<int> dist(-100000, 100000); // Set the random number distribution between -100,000 and 100,000 inclusive.

template<typename T>
void BubbleSort(T A[]);
template<typename T>
void PopulateArray(T A[]);
template<typename T>
void PrintArray(T A[]);

int main()
{
	int myArray[ARRAY_SIZE]; // An array to be sorted.
	PopulateArray(myArray); // Fill the array with random numbers.

	//PrintArray(myArray); // Display array before sorting.

	auto startTime = chrono::system_clock::now(); // Get the time before sorting.
	BubbleSort(myArray); // Sort the array
	auto endTime = chrono::system_clock::now(); // Get the time after sorting.

	//PrintArray(myArray); // Display array after sorting.

	std::chrono::duration<double> diff = endTime - startTime; // Get the difference from start to end time

	cout << "Sorting an array of type " << typeid(myArray).name() << " elements." << endl; // Print the type of the array and the amount of element in it.
	cout << "Algorithm: " << ALGORITHM_NAME << endl; // Print the name of the algorithm used.
	cout << "Total Seconds : " << diff.count() << endl; // Print the time spent in seconds.
}

/// <summary>
/// Sort the array using bubble sort algorithm.
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n)
/// BubbleSort(A)
///  for i = 0 to length of A - 1
///      for j = i + 1 to length of A - 1
///          if A[j] < A[i]
///              swap A[j] and A[i]
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array to be sorted</param>
template<typename T> // can be of any type, needs to implement LessThan operator '<'
void BubbleSort(T A[])
{
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		for (int j = i + 1; j < ARRAY_SIZE; j++)
		{
			if (A[j] < A[i])
			{
				T temp = A[j];
				A[j] = A[i];
				A[i] = temp;
			}
		}
	}
}

/// <summary>
/// Populate an array with random numbers between -100,000 to 100,000
/// </summary>
/// <param name="A">array to populate</param>
template<typename T> // can be of any type, custom type needs to implement explicit conversion to integer
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
