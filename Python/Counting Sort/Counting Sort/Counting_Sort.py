"""
Author: Alexandre Lepage
Date: May 2019
"""
import random
import time

ALGORITHM_NAME = "Counting Sort" # The name of the algorithm used for sorting
random.seed(2019) # Random Seed number to keep values constant.
LIST_SIZE = 50000 # Set the size of the list to 25,000.

def main():
    myList = [0] * LIST_SIZE # A list to be sorted.
    PopulateList(myList) # Fill the list with random numbers.
    
    #PrintList(myList) # Display list before sorting.

    ticks = time.time() # Get the time before sorting.
    CountingSort(myList) # Sort the list
    ticks = time.time() - ticks # Get the time difference after sorting.

    #PrintList(myList) # Display list after sorting.

    print("Sorting an array of type", type(myList), "of", LIST_SIZE, "elements.") # Print the type of the list and the amount of element in it.
    print("Algorithm: ", ALGORITHM_NAME) # Print the name of the algorithm used.
    print("Total Seconds : ", ticks) # Print the time spent in seconds.

def CountingSort(A:list):
    """
    Sort the array of integer using counting sort algorithm
    This version can take negative integer
    -----PSEUDO CODE-----
    (A is an Array with index 0..n, with keys be integer)
    CountingSort(A)
     minValue = the minimun key's value in A
     let C[0..k] be a new array, k is the keys' values range
     initialize C's elements to 0
     for i = 0 to length of A - 1
        C[A[i] - minValue] = C[A[i] - minValue] + 1
     for i = 1 to length of C - 1
        C[i] = C[i] + C[i - 1]
     let B[0..(length of A)] be a new array
     for i = length of A - 1 down to 0
        B[C[A[i] - minValue] - 1] = A[i]
        C[A[i] - minValue] = C[A[i] - minValue] - 1
     A = B
    -----PSEUDO CODE-----
    
    Keyword arguments:
    A:list: the list to sort
    """
    k, minValue = FindRangeAndMinValue(A)
    C = [0] * k

    for i in range(0, len(A)):
       C[A[i] - minValue] = C[A[i] - minValue] + 1

    for i in range(1, len(C)):
       C[i] = C[i] + C[i - 1]
    B = [0] * len(A)

    for i in range(len(A) - 1, -1, -1):
       B[C[A[i] - minValue] - 1] = A[i]
       C[A[i] - minValue] = C[A[i] - minValue] - 1
    
    A[:] = B[:]

def FindRangeAndMinValue(A:list):
    """
    Finds the range of values in an array and the minimum value

    Keyword arguments:
    A:list: array to search

    Return
    int: The range of the values, max - min + 1(to be inclusive)
    int: The minimum value found of the list
    """
    maxValue = -float("Infinity")
    minValue = float("Infinity")

    for i in range(0,len(A)):
    	if (maxValue < A[i]):
    		maxValue = A[i]
    	if (minValue > A[i]):
    		minValue = A[i]

    return (maxValue - minValue + 1), minValue

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