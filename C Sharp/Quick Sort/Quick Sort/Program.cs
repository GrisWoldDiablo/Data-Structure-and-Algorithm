/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */
using System;
namespace Quick_Sort
{
    class Program
    {
        const string ALGORITHM_NAME = "Quick Sort"; // The name of the algorithm used for sorting
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
            int[] array2 = new int[ARRAY_SIZE];
            Array.Copy(array, array2, array.Length);
            //PrintArray(array); // Display array before sorting.

            long time = DateTime.Now.Ticks; // Get the current ticks.
            QuickSort(array); // Sort the array
            time = DateTime.Now.Ticks - time; // Get the time spent sorting.

            //PrintArray(array); // Display array after sorting.

            Console.WriteLine($"Sorting a {array.GetType()} array of {ARRAY_SIZE} elements."); // Print the type of the array and the amount of element in it.
            Console.WriteLine($"Algorithm: {ALGORITHM_NAME}"); // Print the name of the algorithm used.
            Console.WriteLine($"Total Seconds: {TimeSpan.FromTicks(time).TotalSeconds}"); // Print the time spent in seconds.

            time = DateTime.Now.Ticks; // Get the current ticks.
            QuickSortRandomized(array2); // Sort the array
            time = DateTime.Now.Ticks - time; // Get the time spent sorting.

            //PrintArray(array); // Display array after sorting.
            Console.WriteLine();
            Console.WriteLine($"Sorting a {array2.GetType()} array of {ARRAY_SIZE} elements."); // Print the type of the array and the amount of element in it.
            Console.WriteLine($"Algorithm: {ALGORITHM_NAME} Randomized version"); // Print the name of the algorithm used.
            Console.WriteLine($"Total Seconds: {TimeSpan.FromTicks(time).TotalSeconds}"); // Print the time spent in seconds.
        }

        /// <summary>
        /// Sort the array using quick sort algorithm
        /// this overload version is to setup the array properly
        /// </summary>
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array to be sorted</param>
        private static void QuickSort<T>(T[] A) where T : IComparable
        {
            QuickSort(A, 0, A.Length - 1);
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
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array to be sorted</param>
        /// <param name="p">the start index of the array</param>
        /// <param name="r">the end index of the array</param>
        static void QuickSort<T>(T[] A, int p, int r) where T : IComparable
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
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array to be sorted</param>
        /// <param name="p">the start index of the array</param>
        /// <param name="r">the end index of the array</param>
        /// <returns>the new pivot's index</returns>
        static int Partition<T>(T[] A, int p, int r) where T : IComparable
        {
            T x = A[r];
            int i = p - 1;
            for (int j = p; j <= r - 1; j++)
            {
                if (A[j].CompareTo(x) <= 0)
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
        /// Sort the array using quick sort algorithm with a random pivot
        /// this overload version is to setup the array properly
        /// </summary>
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array to be sorted</param>
        private static void QuickSortRandomized<T>(T[] A) where T : IComparable
        {
            QuickSortRandomized(A, 0, A.Length - 1);
        }

        /// <summary>
        /// Sort the array using quick sort algorithm
        /// -----PSEUDO CODE-----
        /// (A is an Array with index 0..n)
        /// (p is the start index of the Array)
        /// (r is the end index of the array)
        /// QuickSortRandomized(A,p,r)
        ///  if p < r
        ///     q = PartitionRadomized(A,p,r)
        ///     QuickSortRandomized(A,p,q-1)
        ///     QuickSortRandomized(A,q+1,r)
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array to be sorted</param>
        /// <param name="p">the start index of the array</param>
        /// <param name="r">the end index of the array</param>
        static void QuickSortRandomized<T>(T[] A, int p, int r) where T : IComparable
        {
            if (p < r)
            {
                int q = PartitionRadomized(A, p, r);
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
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array to be sorted</param>
        /// <param name="p">the start index of the array</param>
        /// <param name="r">the end index of the array</param>
        /// <returns>the new pivot's index</returns>
        static int PartitionRadomized<T>(T[] A, int p, int r) where T : IComparable
        {
            int i = randGen.Next(p, r);
            T temp = A[r];
            A[r] = A[i];
            A[i] = temp;
            return Partition(A, p, r);
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
