"""
Author: Alexandre Lepage
Date: May 2019
"""
import random
import time

ALGORITHM_NAME = "Heap Sort" # The name of the algorithm used for sorting
random.seed(2019) # Random Seed number to keep values constant.
LIST_SIZE = 25000 # Set the size of the list to 25,000.

def main():
    myList = [0] * LIST_SIZE # A list to be sorted.
    PopulateList(myList) # Fill the list with random numbers.
    
    #PrintList(myList) # Display list before sorting.

    ticks = time.time() # Get the time before sorting.
    HeapSort(myList) # Sort the list
    ticks = time.time() - ticks # Get the time difference after sorting.

    #PrintList(myList) # Display list after sorting.

    print("Sorting an array of type", type(myList), "of", LIST_SIZE, "elements.") # Print the type of the list and the amount of element in it.
    print("Algorithm: ", ALGORITHM_NAME) # Print the name of the algorithm used.
    print("Total Seconds : ", ticks) # Print the time spent in seconds.

def HeapSort(A:list):
    """
    Sort the array using heap sort algorithm
    -----PSEUDO CODE-----
    (A is an Array with index 0..n)
    Heapsort(A)
     BuildMaxHeap(A)
     heapSize = lenght of A
     for i = lenght of A - 1 to 1
         swap A[0] and A[i]
         heapSize = heapSize - 1
         MaxHeapify(A,0,heapSize)
    -----PSEUDO CODE-----

    Keyword Argument
    A:list: list to be sorted
    """
    BuildMaxHeap(A)
    heapSize = len(A)
    for i in range(len(A) - 1, 0, -1):
        temp = A[0]
        A[0] = A[i]
        A[i] = temp
        heapSize -= 1
        MaxHeapify(A, 0, heapSize)

def BuildMaxHeap(A:list):
    """
    Place the max element as the root of the heap
    run heapify on each nodes.
    -----PSEUDO CODE-----
    (A is an Array with index 0..n)
    BuildMaxHeap(A)
     for i = FLOOR[(length of A) / 2] down to 0
        MaxHeapify(A,i,length of A)   
    -----PSEUDO CODE-----

    Keyword Argument
    A:list: list to be sorted
    """
    for i in range(int((len(A)) / 2), -1, -1):
        MaxHeapify(A, i, len(A))

def MaxHeapify(A:list, i:int, heapSize:int):
    """
    Makes sure that the node is the biggest one out of its childrens
    -----PSEUDO CODE-----
    (A is an Array with index 0..n)
    (i is the index of the node to MaxHeapify)
    (heapSize is the size of the heap to MaxHeapify)
    MaxHeapify(A,i,heapSize)
     l = Left(i)
     r = Right(i)
     if l < heapSize and A[l] > A[i]
        largest = l
     else
        largest = i
     if r < heapSize and A[r] > A[largest]
        largest = r
     if largest =/= i
        swap A[i] and A[largest]
        MaxHeapify(A,largest,heapSize)
    -----PSEUDO CODE-----

    Keyword Arguments
    A:list: list of the element to be heapified
    i:int: sub tree root index of the heap
    """
    l = Left(i)
    r = Right(i)
    if l < heapSize and A[l] > A[i]:
       largest = l
    else:
       largest = i
    if r < heapSize and A[r] > A[largest]:
       largest = r
    if largest != i:
        temp = A[largest]
        A[largest] = A[i]
        A[i] = temp
        MaxHeapify(A, largest, heapSize)

def Parent(i:int):
    """
    Return the Parent element's index of the request element
    Not used for sorting.

    Keyword Arguments
    i:int: index of requested element
    
    Return
    int: parent's index of requested element
    """
    return int(i / 1)

def Left(i:int):
    """
    Return the Left child element's index of the request element

    Keyword Arguments
    i:int: index of requested element
    
    Return
    int: Left child's index of requested element
    """
    return (i * 2)

def Right(i:int):
    """
    Return the Right child element's index of the request element

    Keyword Arguments
    i:int: index of requested element
    
    Return
    int: Right child's index of requested element
    """
    return ((i * 2) + 1)

def PopulateList(A:list):
    """
    Populate a list with random numbers between -100,000 to 100,000
    
    Keyword arguments:
    A:list: the list to populate
    """
    for i in range(0, len(A)):
        A[i] = random.randint(-100000,100000)

def PrintList(A:list):
    """ 
    Print the list's elements

    Keyword arguments:
    A:list: the list to populate
    """
    print("---- List ----")
    print(A)
    print("---- ----")

"""Entry point"""
if __name__ == "__main__":
    main()