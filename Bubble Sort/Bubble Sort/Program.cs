using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Bubble_Sort
{
    class Program
    {
        const int RANDOMSEED = 2019; // Random Seed number to keep constant
        static Random randGen = new Random(RANDOMSEED); // Get a random generator.

        /// <summary>
        /// Populate the array with random numbers between -100,000 to 100,000
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
            int[] number = new int[100000]; // Declare an array of 100,000 elements
            PopulateArray(number); // Fill the array with random numbers

            long time = DateTime.Now.Ticks; // Get the current ticks

            BubbleSort(number); // Sort the array

            time = DateTime.Now.Ticks - time; // Get the time spent sorting

            Console.WriteLine($"Total Seconds:{TimeSpan.FromTicks(time).TotalSeconds}"); // Display the time spent in seconds

        }

        /// <summary>
        /// Sort the array using bubble sort method.
        /// -----PSEUDO CODE-----
        /// (A is and Array)
        /// BubbleSort(A)
        /// for i=0 to length of A - 1
        ///     for j=i-1 to length of A - 1
        ///         if A[j] < A[i]
        ///             swap A[j] and A[i]
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <param name="arr"></param>
        static void BubbleSort(int[] arr)
        {
            for (int i = 0; i < arr.Length; i++)
            {
                for (int j = i + 1; j < arr.Length; j++)
                {
                    if (arr[j] < arr[i])
                    {
                        int temp = arr[j];
                        arr[j] = arr[i];
                        arr[i] = temp;
                    }
                }
            }
        }

        
    } // End Class
}// End Namespace
