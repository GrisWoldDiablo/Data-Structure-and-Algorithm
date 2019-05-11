"""
Author: Alexandre Lepage
Date: May 2019
"""
import random
import time

ALGORITHM_NAME = "Quick Sort" # The name of the algorithm used for sorting
random.seed(2019) # Random Seed number to keep values constant.
LIST_SIZE = 25000 # Set the size of the list to 25,000.

def main():
    myList1 = [0] * LIST_SIZE # A list to be sorted.
    PopulateList(myList1) # Fill the list with random numbers.
    myList2 = list(myList1) # Declare a list for Quick Sort Randomized and use myList1 in order to use same values.
    
    #PrintList(myList1) # Display list before sorting.

    ticks = time.time() # Get the time before sorting.
    QuickSort(myList1) # Sort the list
    ticks = time.time() - ticks # Get the time difference after sorting.

    #PrintList(myList1) # Display list after sorting.

    print("Sorting an array of type", type(myList1), "of", LIST_SIZE, "elements.") # Print the type of the list and the amount of element in it.
    print("Algorithm: ", ALGORITHM_NAME) # Print the name of the algorithm used.
    print("Total Seconds : ", ticks) # Print the time spent in seconds.
    
    #------ Quick Sort Randomized portion ------
    
    #PrintList(myList2) # Display list before sorting.

    ticks = time.time() # Get the time before sorting.
    QuickSortRandomized(myList2) # Sort the list
    ticks = time.time() - ticks # Get the time difference after sorting.

    #PrintList(myList2) # Display list after sorting.
    print()
    print("Sorting an array of type", type(myList2), "of", LIST_SIZE, "elements.") # Print the type of the list and the amount of element in it.
    print("Algorithm: ", ALGORITHM_NAME, "Randomized version") # Print the name of the algorithm used.
    print("Total Seconds : ", ticks) # Print the time spent in seconds.

def QuickSort(A:list, p:int=None, r:int=None):
    """
    Sort the array using quick sort algorithm
    -----PSEUDO CODE-----
    (A is an Array with index 0..n)
    (p is the start index of the Array)
    (r is the end index of the array)
    QuickSort(A,p,r)
     if p < r
        q = Partition(A,p,r)
        QuickSort(A,p,q-1)
        QuickSort(A,q+1,r)
    -----PSEUDO CODE-----

    Keyword Arguments
    A:list: list to be sorted
    p:int: the start index of the list
    r:int: the end index of the list
    """
    if p == None or r == None:
        QuickSort(A, 0, LIST_SIZE - 1)
        return
    if p < r:
        q = Partition(A, p, r)
        QuickSort(A, p, q - 1)
        QuickSort(A, q + 1, r)

def Partition(A:list, p:int=None, r:int=None):
    """
    Partition the array, rearrange the array inplace based 
    on the element at index r used as pivot.
    -----PSEUDO CODE-----
    (A is an Array with index 0..n)
    (p is the start index of the array)
    (r is the end index and pivot of the array)
    Partition(A,p,r)
     x = A[r]
     i = p - 1
     for j = p to r - 1
        if A[j] <= x
            i = i + 1
            swap A[i] and A[j]
     swap A[i + 1] and A[r]
     return i + 1
    -----PSEUDO CODE-----

    Keyword Arguments
    A:list: list to be sorted
    p:int: the start index of the list
    r:int: the end index of the list

    Return
    int: the new pivot's index
    """
    x = A[r]
    i = p - 1
    for j in range(p, r):
        if A[j] <= x:
            i += 1
            temp2 = A[j]
            A[j] = A[i]
            A[i] = temp2
    temp = A[i + 1]
    A[i + 1] = A[r]
    A[r] = temp;
    return i + 1

def QuickSortRandomized(A:list, p:int=None, r:int=None):
    """
    Sort the array using quick sort algorithm
    -----PSEUDO CODE-----
    (A is an Array with index 0..n)
    (p is the start index of the Array)
    (r is the end index of the array)
    QuickSort(A,p,r)
     if p < r
        q = Partition(A,p,r)
        QuickSort(A,p,q-1)
        QuickSort(A,q+1,r)
    -----PSEUDO CODE-----

    Keyword Arguments
    A:list: list to be sorted
    p:int: the start index of the list
    r:int: the end index of the list
    """
    if p == None or r == None:
        QuickSortRandomized(A, 0, LIST_SIZE - 1)
        return
    if p < r:
        q = PartitionRandomized(A, p, r)
        QuickSortRandomized(A, p, q - 1)
        QuickSortRandomized(A, q + 1, r)

def PartitionRandomized(A:list, p:int=None, r:int=None):
    """
    Swap the pivot with a random element.
    -----PSEUDO CODE-----
    (A is an Array with index 0..n)
    (p is the start index of the Array)
    (r is the end index of the array)
    PartitionRadomized(A,p,r)
     i = Random(p,r)
     swap A[r] and A[i]
     return Partition(A,p,r)
    -----PSEUDO CODE-----

    Keyword Arguments
    A:list: list to be sorted
    p:int: the start index of the list
    r:int: the end index of the list
    
    Return
    int: the new pivot's index  
    """
    i = random.randint(p, r)
    temp = A[r]
    A[r] = A[i]
    A[i] = temp
    return Partition(A, p, r)

def PopulateList(A:list):
    """
    Populate a list with random numbers between -100,000 to 100,000
    
    Keyword arguments:
    A:list: the list to populate
    """
    for i in range(0, LIST_SIZE):
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