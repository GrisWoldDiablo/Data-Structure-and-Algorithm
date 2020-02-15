/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */
using System;

namespace Merge_Sort
{
   
    class Program
    {
        const string ALGORITHM_NAME = "Merge Sort"; // The name of the algorithm used for sorting
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
            MergeSort(array); // Sort the array
            time = DateTime.Now.Ticks - time; // Get the time spent sorting.

            //PrintArray(array); // Display array after sorting.

            Console.WriteLine($"Total Seconds: {TimeSpan.FromTicks(time).TotalSeconds}"); // Print the time spent in seconds.
        }

        /// <summary>
        /// Sort the array using merge sort algorithm,
        /// this overload version is to setup the array properly
        /// </summary>
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array to be sorted</param>
        static void MergeSort<T>(T[] A) where T : IComparable
        {
            MergeSort(A, 0, A.Length - 1);
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
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array to be sorted</param>
        /// <param name="p">start index of array</param>
        /// <param name="r">end index of array</param>
        static void MergeSort<T>(T[] A, int p, int r) where T : IComparable
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
        ///  L[n1] = INFINITY
        ///  R[n2] = INFINITY
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
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array to be sorted</param>
        /// <param name="p">start index of first portion of the array</param>
        /// <param name="q">end index of first portion of the array</param>
        /// <param name="r">end index of second portion of the array</param>
        static void Merge<T>(T[] A, int p, int q, int r) where T : IComparable
        {
            int n1 = q - p + 1;
            int n2 = r - q;
            T[] L = new T[n1 + 1];
            T[] R = new T[n2 + 1];
            for (int i = 0; i < n1; i++)
            {
                L[i] = A[p + i];
            }
            for (int j = 0; j < n2; j++)
            {
                R[j] = A[q + j + 1];
            }
            L[n1] = (dynamic)int.MaxValue; // To be refine for more complex generic type
            R[n2] = (dynamic)int.MaxValue; // To be refine for more complex generic type
            int x = 0;
            int y = 0;
            for (int k = p; k <= r; k++)
            {
                if (L[x].CompareTo(R[y]) <= 0)
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
        /// Print the array's elements
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
