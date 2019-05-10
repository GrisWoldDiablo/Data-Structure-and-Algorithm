/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */
#include <iostream>
#include <chrono>
#include <random>
#include <typeinfo>
#include <limits>
using namespace std;

#define ALGORITHM_NAME ("Counting Sort") // The name of the algorithm used for sorting
#define RANDOM_SEED 2019 // Random Seed number to keep values constant.
#define ARRAY_SIZE 50000 // Set the size of the array to 50,000.
mt19937 gen(RANDOM_SEED); // Seed the mersenne twister random number generator
uniform_int_distribution<int> dist(-100000, 100000); // Set the random number distribution between -100,000 and 100,000 inclusive.

template<typename T>
void CountingSort(T A[]);
template<typename T>
int FindRangeAndMinValue(T A[], T &minValue);
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
	CountingSort(myArray); // Sort the array
	auto endTime = chrono::system_clock::now(); // Get the time after sorting.

	//PrintArray(myArray); // Display array after sorting.

	std::chrono::duration<double> diff = endTime - startTime; // Get the difference from start to end time

	cout << "Sorting an array of type " << typeid(myArray).name() << " elements." << endl; // Print the type of the array and the amount of element in it.
	cout << "Algorithm: " << ALGORITHM_NAME << endl; // Print the name of the algorithm used.
	cout << "Total Seconds : " << diff.count() << endl; // Print the time spent in seconds.
}



/// <summary>
/// Sort the array of integer using counting sort algorithm
/// This version can take negative integer
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n, with keys be integer)
/// CountingSort(A)
///  minValue = the minimun key's value in A
///  let C[0..k] be a new array, k is the keys' values range
///  initialize C's elements to 0
///  for i = 0 to length of A - 1
///     C[A[i] - minValue] = C[A[i] - minValue] + 1
///  for i = 1 to length of C - 1
///     C[i] = C[i] + C[i - 1]
///  let B[0..(length of A)] be a new array
///  for i = length of A - 1 down to 0
///     B[C[A[i] - minValue] - 1] = A[i]
///     C[A[i] - minValue] = C[A[i] - minValue] - 1
///  A = B
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array to be sorted</param>
template<typename T> // can be of any type, needs to implement explicit conversion to integer
void CountingSort(T A[])
{
	T minValue;
	int k = FindRangeAndMinValue(A, minValue);

	int* C = new int[k];
	for (int i = 0; i < k; i++)
	{
		C[i] = 0;
	}

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		C[(int)A[i] - (int)minValue]++;
	}

	for (int i = 1; i < k; i++)
	{
		C[i] += C[i - 1];
	}

	T* B = new T[ARRAY_SIZE];
	for (int i = ARRAY_SIZE - 1; i >= 0; i--)
	{
		/* This way uses variable for clarity.
		int valueOfA = (int)A[i] - (int)minValue;
		int valueOfC = C[valueOfA] - 1;
		B[valueOfC] = A[i];
		C[valueOfA]--;*/

		B[(int)C[(int)A[i] - (int)minValue] - 1] = (int)A[i];
		C[(int)A[i] - (int)minValue]--;
	}

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		A[i] = B[i];
	}
}

/// <summary>
/// Finds the range of values in an array and set a minimum value
/// </summary>
/// <param name="A">array to search</param>
/// <param name="minValue">the minimum value found</param>
/// <returns>The range of the values, max - min + 1(to be inclusive)</returns>
template<typename T> // can be of any type, needs to implement LessThan '<' and GreaterThan '>' operators and explicit conversion to integer
int FindRangeAndMinValue(T A[], T &minValue)
{
	T maxValue = numeric_limits<T>::min();
	minValue = numeric_limits<T>::max();

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		if (maxValue < A[i])
		{
			maxValue = A[i];
		}
		if (minValue > A[i])
		{
			minValue = A[i];
		}
	}
	
	return maxValue - minValue + 1;
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
