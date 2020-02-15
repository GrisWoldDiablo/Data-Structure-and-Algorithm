/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */
#include <iostream>
#include <chrono>
#include <random>
#include <typeinfo>
using namespace std;

#define ALGORITHM_NAME ("Quick Sort") // The name of the algorithm used for sorting
#define RANDOM_SEED 2019 // Random Seed number to keep values constant.
#define ARRAY_SIZE 50000 // Set the size of the array to 50,000.
mt19937 gen(RANDOM_SEED); // Seed the mersenne twister random number generator
uniform_int_distribution<int> dist(-100000, 100000); // Set the random number distribution between -100,000 and 100,000 inclusive.

template<typename T>
void QuickSort(T A[]);
template<typename T>
void QuickSort(T A[], int p, int r);
template<typename T>
int Partition(T A[], int p, int r);
template<typename T>
void QuickSortRandomized(T A[]);
template<typename T>
void QuickSortRandomized(T A[], int p, int r);
template<typename T>
int PartitionRandomized(T A[], int p, int r);
template<typename T>
void PopulateArray(T A[]);
template<typename T>
void PrintArray(T A[]);

int main()
{
	int myArray1[ARRAY_SIZE]; // An array to be sorted.
	PopulateArray(myArray1); // Fill the array with random numbers.
	int myArray2[ARRAY_SIZE]; // Declare an array for Quick Sort Randomized.
	copy(begin(myArray1), end(myArray1), begin(myArray2)); // Copy myArray1 into myArray2 in order to sort same values.
	//PrintArray(myArray1); // Display array before sorting.

	cout << "Sorting an array of type " << typeid(myArray1).name() << " elements." << endl; // Print the type of the array and the amount of element in it.
	cout << "Algorithm: " << ALGORITHM_NAME << endl; // Print the name of the algorithm used.
	auto startTime = chrono::system_clock::now(); // Get the time before sorting.
	QuickSort(myArray1); // Sort the array
	auto endTime = chrono::system_clock::now(); // Get the time after sorting.

	//PrintArray(myArray1); // Display array after sorting.

	std::chrono::duration<double> diff = endTime - startTime; // Get the difference from start to end time
	
	cout << "Total Seconds : " << diff.count() << endl; // Print the time spent in seconds.

	//------ Quick Sort Randomized portion ------
	
	//PrintArray(myArray2); // Display array before sorting.

	cout << "Sorting an array of type " << typeid(myArray2).name() << " elements." << endl; // Print the type of the array and the amount of element in it.
	cout << "Algorithm: " << ALGORITHM_NAME << " Randomized version."<< endl; // Print the name of the algorithm used.
	startTime = chrono::system_clock::now(); // Get the time before sorting.
	QuickSortRandomized(myArray2); // Sort the array
	endTime = chrono::system_clock::now(); // Get the time after sorting.

	//PrintArray(myArray2); // Display array after sorting.

	diff = endTime - startTime; // Get the difference from start to end time

	cout << endl;
	cout << "Total Seconds : " << diff.count() << endl; // Print the time spent in seconds.
}

/// <summary>
/// Sort the array using quick sort algorithm,
/// this overload version is to setup the array properly
/// </summary>
/// <param name="A">array to be sorted</param>
template<typename T> // can be of any type, needs to implement LessThanOrEqualTo operator '<='
void QuickSort(T A[])
{
	QuickSort(A, 0, ARRAY_SIZE - 1);
}

/// <summary>
/// Sort the array using quick sort algorithm
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n)
/// (p is the start index of the Array)
/// (r is the end index of the array)
/// QuickSort(A,p,r)
///  if p < r
///     q = Partition(A,p,r)
///     QuickSort(A,p,q-1)
///     QuickSort(A,q+1,r)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array to be sorted</param>
/// <param name="p">the start index of the array</param>
/// <param name="r">the end index of the array</param>
template<typename T> // can be of any type, needs to implement LessThanOrEqualTo operator '<='
void QuickSort(T A[], int p, int r)
{
	if (p < r)
	{
		int q = Partition(A, p, r);
		QuickSort(A, p, q - 1);
		QuickSort(A, q + 1, r);
	}
}

/// <summary>
/// Partition the array, rearrange the array inplace based 
/// on the element at index r used as pivot.
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n)
/// (p is the start index of the array)
/// (r is the end index and pivot of the array)
/// Partition(A,p,r)
///  x = A[r]
///  i = p - 1
///  for j = p to r - 1
///     if A[j] <= x
///         i = i + 1
///         swap A[i] and A[j]
///  swap A[i + 1] and A[r]
///  return i + 1
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array to be sorted</param>
/// <param name="p">the start index of the array</param>
/// <param name="r">the end index of the array</param>
/// <returns>the new pivot's index</returns>
template<typename T> // can be of any type, needs to implement LessThanOrEqualTo operator '<='
int Partition(T A[], int p, int r)
{
	T x = A[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; j++)
	{
		if (A[j] <= x)
		{
			i++;
			T temp2 = A[j];
			A[j] = A[i];
			A[i] = temp2;
		}
	}
	T temp = A[i + 1];
	A[i + 1] = A[r];
	A[r] = temp;
	return i + 1;
}

/// <summary>
/// Sort the array using quick sort algorithm,
/// this overload version is to setup the array properly
/// </summary>
/// <param name="A">array to be sorted</param>
template<typename T> // can be of any type, needs to implement LessThanOrEqualTo operator '<='
void QuickSortRandomized(T A[])
{
	QuickSortRandomized(A, 0, ARRAY_SIZE - 1);
}

/// <summary>
/// Sort the array using quick sort algorithm
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n)
/// (p is the start index of the Array)
/// (r is the end index of the array)
/// QuickSort(A,p,r)
///  if p < r
///     q = Partition(A,p,r)
///     QuickSort(A,p,q-1)
///     QuickSort(A,q+1,r)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array to be sorted</param>
/// <param name="p">the start index of the array</param>
/// <param name="r">the end index of the array</param>
template<typename T> // can be of any type, needs to implement LessThanOrEqualTo operator '<='
void QuickSortRandomized(T A[], int p, int r)
{
	if (p < r)
	{
		int q = PartitionRandomized(A, p, r);
		QuickSortRandomized(A, p, q - 1);
		QuickSortRandomized(A, q + 1, r);
	}
}

/// <summary>
/// Swap the pivot with a random element.
/// -----PSEUDO CODE-----
/// (A is an Array with index 0..n)
/// (p is the start index of the Array)
/// (r is the end index of the array)
/// PartitionRadomized(A,p,r)
///  i = Random(p,r)
///  swap A[r] and A[i]
///  return Partition(A,p,r)
/// -----PSEUDO CODE-----
/// </summary>
/// <param name="A">array to be sorted</param>
/// <param name="p">the start index of the array</param>
/// <param name="r">the end index of the array</param>
/// <returns>the new pivot's index</returns>
template<typename T> // can be of any type, needs to implement LessThanOrEqualTo operator '<='
int PartitionRandomized(T A[], int p, int r)
{
	int i = dist(gen, decltype(dist)::param_type(p, r));
	T temp = A[r];
	A[r] = A[i];
	A[i] = temp;
	return Partition(A, p, r);
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
