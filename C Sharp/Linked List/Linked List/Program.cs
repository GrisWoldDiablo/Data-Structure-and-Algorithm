/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */
using System;

namespace Linked_List
{
    class Program
    {
        const string DATA_STRUCTURE_NAME = "Linked Lists"; // The name of the data structure
        const int RANDOM_SEED = 2019; // Random Seed number to keep values constant.
        static Random randGen = new Random(RANDOM_SEED); // Get a random generator.
        const int LIST_SIZE = 1000000; // Set the size of the list to 1,000,000.
        const int TEST_AMOUNT = 500; // Amount of item that will be used for some testing.

        // ---- Array for testing setup ----
        static int[] myArray = new int[LIST_SIZE];
        static int[] delTestArray = new int[TEST_AMOUNT];
        static int[] searchTestArray = new int[TEST_AMOUNT];
        static int[] containTestArray = new int[TEST_AMOUNT];
        
        static void Main(string[] args)
        {
            Console.WriteLine($"---- Data structure : {DATA_STRUCTURE_NAME} ----");

            // ---- Setting up the values for testing ----
            PopulateArray(myArray);
            GetRandomValues(myArray, delTestArray);
            GetRandomValues(myArray, searchTestArray);
            GetRandomValues(myArray, containTestArray);

            // ---- Classes Speed Test portion ----
            Console.WriteLine($"---- Testing list speed. ----");

            // ---- Singly Linear Linked List ----
            Console.WriteLine($"\n---- Class type : Singly Linear Linked List ----");
            TheSinglyLinearLinkedList<int> mySLLList = new TheSinglyLinearLinkedList<int>();
            LinkedListTest(mySLLList);

        }

        /// <summary>
        /// Perform a series of test to a linked list class and calculate its time.
        /// Test are: Inserting, Deleting values, searching values and deleting found nodes.
        /// </summary>
        /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
        /// <param name="testList">the linked list to be tested</param>
        private static void LinkedListTest<T>(TheLinkedList<T> testList) where T : IComparable
        {
            #region INSERT_TEST
            // Speed test: Insert LIST_SIZE elements to the list
            Console.Write($"- Inserting {LIST_SIZE} elements -");
            long time = DateTime.Now.Ticks; // Get the current ticks.
            for (int i = 0; i < myArray.Length; i++)
            {
                testList.Insert((dynamic)myArray[i]);
            }
            time = DateTime.Now.Ticks - time; // Get the time spent inserting.
            long totalTime = time; // Get the time spend for this test.
            Console.WriteLine($"- {testList.Count} elements inserted. -");
            Console.WriteLine($"\tTotal Seconds: {TimeSpan.FromTicks(time).TotalSeconds}"); // Print the time spent in seconds.
            #endregion

            #region DELETE_VALUE_TEST
            // Speed test: Delete TEST_AMOUNT elements from the list
            Console.Write($"- Deleting {TEST_AMOUNT} values. -");
            time = DateTime.Now.Ticks; // Get the current ticks.
            for (int i = 0; i < delTestArray.Length; i++)
            {
                testList.Delete((dynamic)delTestArray[i]); // Delete using value
            }
            time = DateTime.Now.Ticks - time; // Get the time spent Deleting.
            totalTime += time; // Add the time spend for this test
            Console.WriteLine($"- {testList.Count} nodes left. -");
            Console.WriteLine($"\tTotal Seconds: {TimeSpan.FromTicks(time).TotalSeconds}"); // Print the time spent in seconds.
            #endregion

            #region SEARCH_VALUE_TEST
            // Speed test: Search TEST_AMOUNT elements from the list
            TheNode<int>[] theFoundNodes = new TheNode<int>[TEST_AMOUNT]; // Found nodes from this test
            Console.Write($"- Searching {TEST_AMOUNT} values. -");
            time = DateTime.Now.Ticks; // Get the current ticks.
            for (int i = 0; i < searchTestArray.Length; i++)
            {
                theFoundNodes[i] = testList.Search((dynamic)searchTestArray[i]); // The found nodes are placed in an array for further testing.
            }
            time = DateTime.Now.Ticks - time; // Get the time spent Searching.
            totalTime += time; // Add the time spend for this test
            int foundNodes = 0;
            foreach (var item in theFoundNodes) // Check the found nodes
            {
                if (item != null) // Count how many nodes are null meaning not found.
                {
                    foundNodes++;
                }
            }
            Console.WriteLine($"- {foundNodes} nodes found. -");
            Console.WriteLine($"\tTotal Seconds: {TimeSpan.FromTicks(time).TotalSeconds}"); // Print the time spent in seconds.
            #endregion

            #region DELETE_NODE_TEST
            // Speed test: Deleting TEST_AMOUNT node from the list
            Console.Write($"- Deleting {foundNodes} nodes. -");
            time = DateTime.Now.Ticks; // Get the current ticks.
            for (int i = 0; i < theFoundNodes.Length; i++)
            {
                testList.Delete((dynamic)theFoundNodes[i]); // Delete using nodes.
            }
            time = DateTime.Now.Ticks - time; // Get the time spent Searching.
            totalTime += time; // Add the time spend for this test
            Console.WriteLine($"- {testList.Count} nodes left  -");
            Console.WriteLine($"\tTotal Seconds: {TimeSpan.FromTicks(time).TotalSeconds}"); // Print the time spent in seconds.
            #endregion

            Console.WriteLine("- Class Speed for all tests -");
            Console.WriteLine($"\tTotal seconds : {TimeSpan.FromTicks(totalTime).TotalSeconds}"); // Print the time spent in seconds for all tests combined 
        }

        /// <summary>
        /// Fill array B with random values from array A.
        /// </summary>
        /// <param name="A"></param>
        /// <param name="B"></param>
        static void GetRandomValues(int[] A, int[] B)
        {
            for (int i = 0; i < B.Length; i++)
            {
                B[i] = A[randGen.Next(A.Length)];
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
                A[i] = randGen.Next(-100000,100000);
            }
        }
    } // End class
} // End namespace
