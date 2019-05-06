using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bubble_Sort
{
    class Program
    {
        const string ALGORITHM_NAME = "Bubble Sort";
        const int RANDOM_SEED = 2019; // Random Seed number to keep constant
        static Random randGen = new Random(RANDOM_SEED); // Get a random generator.
        const int ARRAY_SIZE = 50000; // Set the size of the array to 50,000

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
            int[] array = new int[ARRAY_SIZE]; // Declare an array
            PopulateArray(array); // Fill the array with random numbers

            long time = DateTime.Now.Ticks; // Get the current ticks

            //Console.WriteLine(string.Join(",",number)); // Display array before sorting
            BubbleSort(array); // Sort the array
            //Console.WriteLine(string.Join(",",number)); // Display array after sorting

            time = DateTime.Now.Ticks - time; // Get the time spent sorting

            Console.WriteLine($"Sorting an {array.GetType()} array of {ARRAY_SIZE} elements."); // Print the type of the array and the amount of element in it.
            Console.WriteLine($"Algorithm: {ALGORITHM_NAME}");// Print the name of the algorithm used.
            Console.WriteLine($"Total Seconds:{TimeSpan.FromTicks(time).TotalSeconds}"); // Print the time spent in seconds

        }

        /// <summary>
        /// Sort the array using bubble sort algorithm.
        /// -----PSEUDO CODE-----
        /// (A is an Array with index 0..n)
        /// BubbleSort(A)
        /// for i=0 to length of A - 1
        ///     for j=i-1 to length of A - 1
        ///         if A[j] < A[i]
        ///             swap A[j] and A[i]
        /// -----PSEUDO CODE-----
        /// </summary>
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

        
    } // End Class
}// End Namespace
