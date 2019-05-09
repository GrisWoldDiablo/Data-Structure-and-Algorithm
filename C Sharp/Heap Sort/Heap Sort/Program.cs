/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */
using System;

namespace Heap_Sort
{
    class Program
    {
        const string ALGORITHM_NAME = "Heap Sort"; // The name of the algorith used for sorting
        const int RANDOM_SEED = 2019; // Random Seed number to keep values constant.
        static Random randGen = new Random(RANDOM_SEED); // Get a random generator.
        const int ARRAY_SIZE = 50000; // Set the size of the array to 50,000.

        static void Main(string[] args)
        {
            int[] array = new int[ARRAY_SIZE]; // Declare an array.
            PopulateArray(array); // Fill the array with random numbers.

            //PrintArray(array); // Display array before sorting.

            long time = DateTime.Now.Ticks; // Get the current ticks.
            HeapSort(array); // Sort the array
            time = DateTime.Now.Ticks - time; // Get the time spent sorting.

            //PrintArray(array); // Display array after sorting.

            Console.WriteLine($"Sorting a {array.GetType()} array of {ARRAY_SIZE} elements."); // Print the type of the array and the amount of element in it.
            Console.WriteLine($"Algorithm: {ALGORITHM_NAME}"); // Print the name of the algorithm used.
            Console.WriteLine($"Total Seconds: {TimeSpan.FromTicks(time).TotalSeconds}"); // Print the time spent in seconds.
        }

        /// <summary>
        /// Sort the array using heap sort algorithm
        /// -----PSEUDO CODE-----
        /// (A is an Array with index 0..n)
        /// Heapsort(A)
        ///  BuildMaxHeap(A)
        ///  heapSize = lenght of A
        ///  for i = lenght of A - 1 to 1
        ///      swap A[0] and A[i]
        ///      heapSize = heapSize - 1
        ///      MaxHeapify(A,0,heapSize)
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array to be sorted</param>
        static void HeapSort<T>(T[] A) where T : IComparable
        {
            BuildMaxHeap(A);
            int heapSize = A.Length;
            for (int i = A.Length - 1; i >= 1; i--)
            {
                T temp = A[0];
                A[0] = A[i];
                A[i] = temp;
                heapSize--;
                MaxHeapify(A, 0, heapSize);
            }
        }

        /// <summary>
        /// Place the max element as the root of the heap
        /// run heapify on each nodes.
        /// -----PSEUDO CODE-----
        /// (A is an Array with index 0..n)
        /// BuildMaxHeap(A)
        ///  for i = FLOOR[(length of A) / 2] down to 0
        ///     MaxHeapify(A,i,length of A)   
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array to be max heaped</param>
        private static void BuildMaxHeap<T>(T[] A) where T : IComparable
        {
            for (int i = (A.Length) / 2; i >= 0; i--)
            {
                MaxHeapify(A, i, A.Length);
            }
        }

        /// <summary>
        /// Makes sure that the node is the biggest one out of its childrens
        /// -----PSEUDO CODE-----
        /// (A is an Array with index 0..n)
        /// (i is the index of the node to MaxHeapify)
        /// (heapSize is the size of the heap to MaxHeapify)
        /// MaxHeapify(A,i,heapSize)
        ///  l = Left(i)
        ///  r = Right(i)
        ///  if l < heapSize and A[l] > A[i]
        ///     largest = l
        ///  else
        ///     lasgest = i
        ///  if r < heapSize and A[r] > A[largest]
        ///     largest = r
        ///  if largest =/= i
        ///     swap A[i] and A[largest]
        ///     MaxHeapify(A,largest,heapSize)
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="A">array of the element to be heapified</param>
        /// <param name="i">index of the element to be heapified</param>
        /// <param name="heapSize">the size of the heap</param>
        static void MaxHeapify<T>(T[] A, int i, int heapSize) where T : IComparable
        {
            int l = Left(i);
            int r = Right(i);
            int largest;
            if (l < heapSize && A[l].CompareTo(A[i]) > 0)
            {
                largest = l;
            }
            else
            {
                largest = i;
            }
            if (r < heapSize && A[r].CompareTo(A[largest]) > 0)
            {
                largest = r;
            }
            if (largest != i)
            {
                T temp = A[largest];
                A[largest] = A[i];
                A[i] = temp;
                MaxHeapify(A, largest, heapSize);
            }
        }

        /// <summary>
        /// Return the Parent element's index of the request element at index i
        /// Not used for sorting.
        /// </summary>
        /// <param name="i">index of requested element</param>
        /// <returns>Parent's index of requested element</returns>
        static int Parent(int i)
        {
            return (i / 2);
        }

        /// <summary>
        /// Return the Left child element's index of the request element at index i
        /// </summary>
        /// <param name="i">index of requested element</param>
        /// <returns>Left child's index of requested element</returns>
        static int Left(int i)
        {
            return (2 * i);
        }

        /// <summary>
        /// Return the Right child element's index of the request element at index i
        /// </summary>
        /// <param name="i">index of requested element</param>
        /// <returns>Right child's index of requested element</returns>
        static int Right(int i)
        {
            return ((2 * i) + 1);
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
        /// <typeparam name="T">can be of any type, ToString() need to return key</typeparam>
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
