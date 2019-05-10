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

#define ALGORITHM_NAME ("Merge Sort") // The name of the algorithm used for sorting
#define RANDOM_SEED 2019 // Random Seed number to keep values constant.
#define ARRAY_SIZE 50000 // Set the size of the array to 50,000.
mt19937 gen(RANDOM_SEED); // Seed the mersenne twister random number generator
uniform_int_distribution<int> dist(-100000, 100000); // Set the random number distribution between -100,000 and 100,000 inclusive.

template<typename T>
void MergeSort(T A[]);
template<typename T>
void MergeSort(T A[], int p, int r);
template<typename T>
void Merge(T A[], int p, int q, int r);
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
	MergeSort(myArray); // Sort the array
	auto endTime = chrono::system_clock::now(); // Get the time after sorting.

	//PrintArray(myArray); // Display array after sorting.

	std::chrono::duration<double> diff = endTime - startTime; // Get the difference from start to end time

	cout << "Sorting an array of type " << typeid(myArray).name() << " elements." << endl; // Print the type of the array and the amount of element in it.
	cout << "Algorithm: " << ALGORITHM_NAME << endl; // Print the name of the algorithm used.
	cout << "Total Seconds : " << diff.count() << endl; // Print the time spent in seconds.
}



/// <summary>
/// Sort the array using merge sort algorithm,
/// this overload version is to setup the array properly
/// </summary>
/// <param name="A">array to be sorted</param>
template<typename T> // can be of any type, needs to implement LessThan operator '<'
void MergeSort(T A[])
{
	MergeSort(A, 0, ARRAY_SIZE - 1);
}

/// <summary>
/// Sort the array using merge sort algorithm
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n)
/// (p and r are indexes) 
/// MergeSort(A,p,r)
///  if p < r
///      q =  FLOOR[(p + r) / 2]
///      MergeSort(A,p,q)
///      MergeSort(A,q+1,r)
///      Merge(A,p,q,r)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array to be sorted</param>
/// <param name="p">start index of array</param>
/// <param name="r">end index of array</param>
template<typename T> // can be of any type, needs to implement LessThan operator '<'
void MergeSort(T A[], int p, int r)
{
	if (p < r)
	{
		int q = (p + r) / 2;
		MergeSort(A, p, q);
		MergeSort(A, q + 1, r);
		Merge(A, p, q, r);
	}
}

/// <summary>
/// Merge the 2 array portions together.
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n)
/// (p, q and r are indexes)
/// Merge(A,p,q,r)
///  n1 = q - p + 1
///  n2 = r - q
///  let L[0..n1+1] and R[0..n2+1] be new arrays
///  for i = 0 to n1 - 1
///      L[i] = A[p + i]
///  for j = 0 to n2 - 1
///      R[j] = A[q + j + 1]
///  L[n1 + 1] = INFINITY
///  R[n2 + 1] = INFINITY
///  x = 0
///  y = 0
///  for k = p to r
///      if L[x] <= R[y]
///          A[k] = L[x]
///          x = x + 1
///      else
///          A[k] = R[y]
///          y = y + 1
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array to be sorted</param>
/// <param name="p">start index of first portion of the array</param>
/// <param name="q">end index of first portion of the array</param>
/// <param name="r">end index of second portion of the array</param>
template<typename T> // can be of any type, needs to implement LessThanOrEqualTo operator '<='
void Merge(T A[], int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	T* L = new T[n1 + 1];
	T* R = new T[n2 + 1];
	for (int i = 0; i < n1; i++)
	{
		L[i] = A[p + i];
	}
	for (int j = 0; j < n2; j++)
	{
		R[j] = A[q + j + 1];
	}
	L[n1] = numeric_limits<T>::max(); // To be refine for more complex generic type
	R[n2] = numeric_limits<T>::max(); // To be refine for more complex generic type
	int x = 0;
	int y = 0;
	for (int k = p; k <= r; k++)
	{
		if (L[x] <= R[y])
		{
			A[k] = L[x];
			x++;
		}
		else
		{
			A[k] = R[y];
			y++;
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
