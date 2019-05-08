/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */
using System;

namespace Bubble_Sort
{
    class Program
    {
        const string ALGORITHM_NAME = "Bubble Sort"; // The name of the algorithm used for sorting
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
            BubbleSort(array); // Sort the array
            time = DateTime.Now.Ticks - time; // Get the time spent sorting.

            //PrintArray(array); // Display array after sorting.

            Console.WriteLine($"Sorting a {array.GetType()} array of {ARRAY_SIZE} elements."); // Print the type of the array and the amount of element in it.
            Console.WriteLine($"Algorithm: {ALGORITHM_NAME}");// Print the name of the algorithm used.
            Console.WriteLine($"Total Seconds: {TimeSpan.FromTicks(time).TotalSeconds}"); // Print the time spent in seconds.
        }

        /// <summary>
        /// Sort the array using bubble sort algorithm.
        /// -----PSEUDO CODE-----
        /// (A is an Array with index 0..n)
        /// BubbleSort(A)
        ///  for i = 0 to length of A - 1
        ///      for j = i - 1 to length of A - 1
        ///          if A[j] < A[i]
        ///              swap A[j] and A[i]
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array to be sorted</param>
        static void BubbleSort<T>(T[] A) where T : IComparable
        {
            for (int i = 0; i < A.Length; i++)
            {
                for (int j = i + 1; j < A.Length; j++)
                {
                    if (A[j].CompareTo(A[i]) < 0)
                    {
                        T temp = A[j];
                        A[j] = A[i];
                        A[i] = temp;
                    }
                }
            }
        }

        /// <summary>
        /// Print the array's elements
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
