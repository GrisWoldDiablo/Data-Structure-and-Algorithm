/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */
using System;

namespace Counting_Sort
{
    class Program
    {
        const string ALGORITHM_NAME = "Counting Sort"; // The name of the algorithm used for sorting
        const int RANDOM_SEED = 2019; // Random Seed number to keep values constant.
        static Random randGen = new Random(RANDOM_SEED); // Get a random generator.
        const int ARRAY_SIZE = 50000; // Set the size of the array to 50,000.

        static void Main(string[] args)
        {
            int[] array = new int[ARRAY_SIZE]; // Declare an array.
            PopulateArray(array); // Fill the array with random numbers.

            //PrintArray(array); // Display array before sorting.

            Console.WriteLine($"Sorting a {array.GetType()} array of {ARRAY_SIZE} elements."); // Print the type of the array and the amount of element in it.
            Console.WriteLine($"Algorithm: {ALGORITHM_NAME}"); // Print the name of the algorithm used.
            long time = DateTime.Now.Ticks; // Get the current ticks.
            CountingSort(array); // Sort the array
            time = DateTime.Now.Ticks - time; // Get the time spent sorting.

            //PrintArray(array); // Display array after sorting.

            Console.WriteLine($"Total Seconds: {TimeSpan.FromTicks(time).TotalSeconds}"); // Print the time spent in seconds.
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
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array to be sorted</param>
        static void CountingSort<T>(T[] A) where T : IComparable
        {
            int k = FindRangeAndMinValue(A, out int minValue);
            
            int[] C = new int[k];

            for (int i = 0; i < A.Length; i++)
            {
                C[(dynamic)A[i] - minValue]++; // To be refine for more complex generic type
            }

            for (int i = 1; i < C.Length; i++)
            {
                C[i] += C[i - 1];
            }

            T[] B = new T[A.Length];
            for (int i = A.Length - 1; i >= 0; i--)
            {
                /* This way uses variable for clarity.
                int valueOfA = (dynamic)A[i] - minValue; // To be refine for more complex generic type
                int valueOfC = C[valueOfA] - 1;
                B[valueOfC] = (dynamic)A[i]; // To be refine for more complex generic type
                C[valueOfA]--;*/
                
                B[C[(dynamic)A[i] - minValue] - 1] = (dynamic)A[i]; // To be refine for more complex generic type
                C[(dynamic)A[i] - minValue]--; // To be refine for more complex generic type
            }
            
            Array.Copy(B, A, A.Length);
        }

        /// <summary>
        /// Finds the range of values in an array and set a minimum value
        /// </summary>
        /// <typeparam name="T">can be of any type</typeparam>
        /// <param name="A">array to search</param>
        /// <param name="minValue">the minimum value found</param>
        /// <returns>The range of the values, max - min + 1(to be inclusive)</returns>
        static int FindRangeAndMinValue<T>(T[] A, out int minValue)
        {
            int maxValue = int.MinValue;
            minValue = int.MaxValue;
            foreach (var item in A)
            {
                if (maxValue.CompareTo(item) < 0)
                {
                    maxValue = (dynamic)item; // To be refine for more complex generic type
                }
                if (minValue.CompareTo(item) > 0)
                {
                    minValue = (dynamic)item; // To be refine for more complex generic type
                }
            }
            return maxValue - minValue + 1;
        }
        
        /// <summary>
        /// Populate an int array with random numbers between -100,000 to 100,000
        /// </summary>
        /// <param name="A">array to populate</param>
        static void PopulateArray(int[] A)
        {
            for (int i = 0; i < A.Length; i++)
            {
                A[i] = randGen.Next(-100000, 100000);
            }
        }

        /// <summary>
        /// Print the array elements
        /// </summary>
        /// <typeparam name="T">can be of any type, ToString() needs to return key</typeparam>
        /// <param name="A">array to be printed</param>
        static void PrintArray<T>(T[] A)
        {
            Console.WriteLine($"---- Array of {A.GetType()} ----");
            for (int i = 0; i < A.Length; i++)
            {
                if (i != A.Length - 1)
                {
                    Console.Write(A[i] + ",");
                }
                else
                {
                    Console.Write(A[i]);
                }
            }
            Console.WriteLine();
            Console.WriteLine("---- ----");
        }
    } // End Class
} // End Namespace
