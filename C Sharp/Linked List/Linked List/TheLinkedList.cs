/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */
using System;

namespace Linked_List
{
    /// <summary>
    /// Custom abstract linked list class
    /// </summary>
    /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
    public abstract class TheLinkedList<T> where T : IComparable
    {
        protected TheNode<T> head; // node at the head of the list
        protected int size; // quantity of node(s) are in the list

        public int Count { get => size; } // Return the size of the list

        public abstract void Insert(T k);
        public abstract void Insert(TheNode<T> n);
        public abstract bool Delete(T k);
        public abstract bool Delete(TheNode<T> n);
        public abstract TheNode<T> Predecessor(T k);
        public abstract TheNode<T> Predecessor(TheNode<T> n);
        public abstract TheNode<T> Search(T k);
        public abstract TheNode<T> Search(TheNode<T> n);
        public abstract bool Contains(T k);
        public abstract bool Contains(TheNode<T> n);
        public abstract void Clear();

        /// <summary>
        ///  Display all the element of the list
        /// -----PSEUDO CODE-----
        /// (L is the list)
        /// PrintList(L)
        ///  y = L.head
        ///  while y =/= NIL
        ///     print y.key
        ///     y = y.next
        /// -----PSEUDO CODE-----
        /// </summary>
        public void PrintList()
        {
            Console.WriteLine("---- The list elements ----");
            TheNode<T> y = head;
            if (y == null)
            {
                Console.Write("EMPTY");
            }
            while (y != null)
            {
                Console.Write($"{y}, ");
                y = y.next;
            }
            Console.WriteLine("\n---- ----");
        }
    } // End Class TheLinkedList

    /// <summary>
    /// Custom abstract node class for Linked List
    /// </summary>
    /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
    public abstract class TheNode<T> where T : IComparable
    {
        public T key; // value of the node
        public TheNode<T> next; // node after this one in the list
        protected TheNode<T> prev; // node before this one in the list

        /// <summary>
        /// compares this object to the argument one.
        /// </summary>
        /// <param name="obj">object to compare to</param>
        /// <returns>-1(SmallerThan), 0(EqualTo), 1(LargerThan) </returns>
        public int CompareTo(object obj)
        {
            if (obj == null) return 1;

            if (obj is TheNode<T> otherNode)
                return key.CompareTo(otherNode.key);
            else
                throw new ArgumentException($"Object is not a {typeof(TheNode<T>)}");
        }

        /// <summary>
        /// Overrides to return the key
        /// </summary>
        /// <returns>key value in string form</returns>
        public override string ToString()
        {
            return key.ToString();
        }
    }  // End Class TheNode
}
