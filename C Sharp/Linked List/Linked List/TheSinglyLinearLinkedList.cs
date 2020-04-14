/*
 * Author: Alexandre Lepage
 * Date: May 2019
 */
using System;

namespace Linked_List
{
    /// <summary>
    /// Custom linked list class,
    /// Linear and Singly
    /// </summary>
    /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
    class TheSinglyLinearLinkedList<T> : TheLinkedList<T> where T : IComparable
    {
        /// <summary>
        /// Class constructor
        /// -----PSEUDO CODE-----
        /// LinkedList()
        ///  head = NIL
        ///  size = 0
        /// -----PSEUDO CODE-----
        /// </summary>
        public TheSinglyLinearLinkedList()
        {
            head = null;
            size = 0;
        }

        /// <summary>
        /// Add a new value to the list
        /// -----PSEUDO CODE-----
        /// (L is the LinkedList, k is the value to be added)
        /// Insert(L,k)
        ///  y.key = k
        ///  Insert(L,y)
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <param name="k">value to be added</param>
        public override void Insert(T k)
        {
            Insert(new TSLNode<T>(k));
        }

        /// <summary>
        /// Add a new node to the list
        /// -----PSEUDO CODE-----
        /// (L is the LinkedList, x is the node to be added)
        /// Insert(L,x)
        ///  x.next = L.head
        ///  L.head = x
        ///  L.size = L.size + 1
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <param name="x">node to be added</param>
        public override void Insert(TheNode<T> x)
        {
            x.next = head;
            head = x;
            size++;
        }

        /// <summary>
        /// remove a node with a specific value from the list
        /// -----PSEUDO CODE-----
        /// (L is the LinkedList, k is the value of the node to be deleted)
        /// Delete(L,k)
        ///  y = Search(L,k)
        ///  Delete(L,y)
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <param name="k">value of the node to be removed</param>
        /// <returns>True if node was removed</returns>
        public override bool Delete(T k)
        {
            TheNode<T> y = Search(k);
            return Delete(y);
        }

        /// <summary>
        /// remove a node from the list
        /// -----PSEUDO CODE-----
        /// (L is the LinkedList, x is the node to be deleted)
        /// Delete(L,x)
        ///  y = Predecessor(L,x)
        ///  if y =/= NIL
        ///     y.next = y.next.next
        ///     L.size = L.size - 1
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <param name="x">node to be removed</param>
        /// <returns>True if node was removed</returns>
        public override bool Delete(TheNode<T> x)
        {
            TheNode<T> y = Predecessor(x);
            if (y != null)
            {
                y.next = y.next.next;
                size--;
                return true;
            }
            return false;
        }

        /// <summary>
        /// find the node preceding the node with a specific value
        /// -----PSEUDO CODE-----
        /// (L is the LinkedList, k is the value of the node to look at)
        /// Predecessor(L,k)
        ///  y.key = k
        ///  return Predecessor(L,y)
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <param name="k">value of the node to look at</param>
        /// <returns>the found node or null</returns>
        public override TheNode<T> Predecessor(T k)
        {
            return Predecessor(new TSLNode<T>(k));
        }

        /// <summary>
        /// find the node preceding the node
        /// -----PSEUDO CODE-----
        /// (L is the LinkedList, x is the value of the node to look at)
        /// Predecessor(L,x)
        ///  y = L.head
        ///  if y == NIL
        ///     return NIL
        ///  while y.next =/= NIL
        ///     if y.next == x
        ///         return y
        ///     y = y.next
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <param name="n">node to look at</param>
        /// <returns>the found node or null</returns>
        public override TheNode<T> Predecessor(TheNode<T> x)
        {
            TheNode<T> y = head;
            if (y == null)
            {
                return null;
            }
            while (y.next != null)
            {
                if (y.next.CompareTo(x) == 0)
                {
                    return y;
                }
                y = y.next;
            }
            return null;
        }

        /// <summary>
        /// find a node with a specific value
        /// -----PSEUDO CODE-----
        /// (L is the LinkedList, k is the value to be found)
        /// Search(L,k)
        ///  y.key = k
        ///  return Search(L,y)
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <param name="k">value of the node to find</param>
        /// <returns>the found node or null</returns>
        public override TheNode<T> Search(T k)
        {
            return Search(new TSLNode<T>(k));
        }

        /// <summary>
        /// find a node with a specific value
        /// -----PSEUDO CODE-----
        /// (L is the LinkedList, x is the node to find)
        /// Search(L,x)
        ///  y = L.head
        ///  while y =/= NIL and y =/= x
        ///     y = y.next
        ///  return y
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <param name="x">value of the node to find</param>
        /// <returns>the found node or null</returns>
        public override TheNode<T> Search(TheNode<T> x)
        {
            TheNode<T> y = head;
            while (y != null && y.CompareTo(x) != 0)
            {
                y = y.next;
            }
            return y;
        }

        /// <summary>
        /// check if the list contains a node with a specific value
        /// -----PSEUDO CODE-----
        /// (L is the LinkedList, k is the value to look for)
        /// Contains(L,k)
        ///  y.key = k
        ///  return Contains(L,y)
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <param name="n">the node to find</param>
        /// <returns>True if the list contain the node</returns>
        public override bool Contains(T k)
        {
            return Contains(new TSLNode<T>(k));
        }

        /// <summary>
        /// check if the list contains a node
        /// -----PSEUDO CODE-----
        /// (L is the LinkedList, x is the node to look for)
        /// Contains(L,x)
        ///  y = L.head
        ///  while y =/= NIL
        ///     if y == x
        ///         return True
        ///     y = y.next
        ///  return False
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <param name="n">the node to find</param>
        /// <returns>True if the list contain the node</returns>
        public override bool Contains(TheNode<T> x)
        {
            TheNode<T> y = head;
            while (y != null)
            {
                if (y.CompareTo(x) == 0)
                {
                    return true;
                }
                y = y.next;
            }
            return false;
        }

        /// <summary>
        /// Empty the list
        /// -----PSEUDO CODE-----
        /// (L is the LinkedList)
        /// Clear(L)
        ///  L.head = NIL
        ///  L.size = 0
        /// -----PSEUDO CODE-----
        /// </summary>
        public override void Clear()
        {
            head = null;
            size = 0;
        }
    } // End Class TheSinglyLinearLinkedList

    /// <summary>
    /// Custom node class for Singly Linear Linked List
    /// </summary>
    /// <typeparam name="T">can be of any type, needs to implement IComparable</typeparam>
    public class TSLNode<T> : TheNode<T> where T : IComparable
    {
        /// <summary>
        /// Class constructor
        /// -----PSEUDO CODE-----
        /// (k is the value of the node)
        /// TSLNode(k)
        ///  key = k
        /// -----PSEUDO CODE-----
        /// </summary>
        /// <param name="k">value of the node</param>
        public TSLNode(T k)
        {
            this.key = k;
        }

    } // End Class TSLNode

} //End Namespace
