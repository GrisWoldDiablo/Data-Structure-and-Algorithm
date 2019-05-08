/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */
using System;

namespace Insertion_Sort
{
    class Program
    {
        const string ALGORITHM_NAME = "Insertion Sort"; // The name of the algorithm used for sorting
        const int RANDOM_SEED = 2019; // Random Seed number to keep values constant.
        static Random randGen = new Random(RANDOM_SEED); // Get a random generator.
        const int ARRAY_SIZE = 50000; // Set the size of the array to 50,000.

        /// <summary>
        /// Populate an int array with random numbers between -100,000 to 100,000
        /// </summary>
        /// <param name="arr">array to populate</param>
        static void PopulateArray(int[] arr)
        {
            for (int i = 0; i < arr.Length; i++)
            {
                arr[i] = randGen.Next(-100000, 100000);
            }
        }

        static void Main(string[] args)
        {
            int[] array = new int[ARRAY_SIZE]; // Declare an array.
            PopulateArray(array); // Fill the array with random numbers.

            //PrintArray(array); // Display array before sorting.

            long time = DateTime.Now.Ticks; // Get the current ticks.
            InsertionSort(array); // Sort the array
            time = DateTime.Now.Ticks - time; // Get the time spent sorting.

            //PrintArray(array); // Display array after sorting.

            Console.WriteLine($"Sorting a {array.GetType()} array of {ARRAY_SIZE} elements."); // Print the type of the array and the amount of element in it.
            Console.WriteLine($"Algorithm: {ALGORITHM_NAME}"); // Print the name of the algorithm used.
            Console.WriteLine($"Total Seconds: {TimeSpan.FromTicks(time).TotalSeconds}"); // Print the time spent in seconds.
        }

        /// <summary>
        /// Sort the array using insertion sort algorithm.
        /// -----PSEUDO CODE-----
        /// (A is an Array with index 0..n)
        /// InsertionSort(A)
        ///  for j = 1 to length of A - 1
        ///      key = A[j]
        ///      i = j - 1
        ///      while i >= 0 and A[i] > key
        ///          A[i + 1] = A[i]
        ///          i = i + 1
        ///      A[i+1] = key
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array to be sorted</param>
        static void InsertionSort<T>(T[] A) where T : IComparable
        {
            for (int j = 1; j < A.Length; j++)
            {
                T key = A[j];
                int i = j - 1;
                while (i >= 0 && A[i].CompareTo(key) > 0)
                {
                    A[i + 1] = A[i];
                    i--;
                }
                A[i + 1] = key;
            }
        }

        /// <summary>
        /// Print the array elements
        /// </summary>
        /// <typeparam name="T">can be of any type, ToString() need to return key</typeparam>
        /// <param name="array">array to be printed</param>
        static void PrintArray<T>(T[] array)
        {
            Console.WriteLine($"---- Array of {array.GetType()} ----");
            for (int i = 0; i < array.Length; i++)
            {
                if (i != array.Length - 1)
                {
                    Console.Write(array[i] + ",");
                    continue;
                }
                else
                {
                    Console.Write(array[i]);
                }
            }
            Console.WriteLine();
            Console.WriteLine("---- ----");
        }
    } // End Class
} // End Namespace
