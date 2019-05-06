﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Insertion_Sort
{
    class Program
    {
        const string ALGORITHM_NAME = "Insertion Sort"; // The name of the algorith used for sorting
        const int RANDOM_SEED = 2019; // Random Seed number to keep constant.
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

            long time = DateTime.Now.Ticks; // Get the current ticks.

            //Console.WriteLine(string.Join(",",array)); // Display array before sorting.
            InsertionSort(array); // Sort the array
            //Console.WriteLine(string.Join(",",array)); // Display array after sorting.

            time = DateTime.Now.Ticks - time; // Get the time spent sorting.
            Console.WriteLine($"Sorting a {array.GetType()} array of {ARRAY_SIZE} elements."); // Print the type of the array and the amount of element in it.
            Console.WriteLine($"Algorithm: {ALGORITHM_NAME}"); // Print the name of the algorithm used.
            Console.WriteLine($"Total Seconds:{TimeSpan.FromTicks(time).TotalSeconds}"); // Print the time spent in seconds.

        }

        /// <summary>
        /// Sort the array using insertion sort algorithm.
        /// -----PSEUDO CODE-----
        /// (A is an Array with index 0..n)
        /// InsertionSort(A)
        /// for j=1 to length of A - 1
        ///     key = A[j]
        ///     i = j - 1
        ///     while i >= 0 and A[i] > key
        ///         A[i+1] = A[i]
        ///         i = i + 1
        ///     A[i+1] = key
        /// -----PSEUDO CODE-----
        /// </summary>
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
    } // End Class
} // End Namespace