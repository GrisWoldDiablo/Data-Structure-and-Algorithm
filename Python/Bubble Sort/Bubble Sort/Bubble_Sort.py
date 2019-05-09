"""
Author: Alexandre Lepage
Date: May 2019
"""
import random
import time

ALGORITHM_NAME = "Bubble Sort" # The name of the algorithm used for sorting
random.seed(2019) # Random Seed number to keep values constant.
LIST_SIZE = 25000 # Set the size of the list to 25,000.

def main():
    myList = [0] * LIST_SIZE # A list to be sorted.
    PopulateList(myList) # Fill the list with random numbers.

    #print(myList) # Display list before sorting.

    ticks = time.time() # Get the time before sorting.
    BubbleSort(myList) # Sort the list
    ticks = time.time() - ticks # Get the time difference after sorting.

    #print(myList) # Display list after sorting.

    print("Sorting an array of type", type(myList),"of",LIST_SIZE,"elements.") # // Print the type of the list and the amount of element in it.
    print("Algorithm: ", ALGORITHM_NAME) # Print the name of the algorithm used.
    print("Total Seconds : ", ticks) # Print the time spent in seconds.


def BubbleSort(A:list):
    """
    Sort the list using bubble sort algorithm.
    -----PSEUDO CODE-----
    (A is an Array with index 0..n)
    BubbleSort(A)
     for i = 0 to length of A - 1
         for j = i - 1 to length of A - 1
             if A[j] < A[i]
                 swap A[j] and A[i]
    -----PSEUDO CODE-----
    
    Keyword arguments:
    A:list: the list to be sorted
    """
    for i in range(0, LIST_SIZE):
        for j in range(i + 1, LIST_SIZE):
            if (A[j] < A[i]):
                temp = A[j]
                A[j] = A[i]
                A[i] = temp

def PopulateList(arr:list):
    """
    Populate a list with random numbers between -100,000 to 100,000
    
    Keyword arguments:
    A:list: the list to populate
    """
    for i in range(0, LIST_SIZE):
        arr[i] = random.randint(-100000,100000)

"""Entry point"""
if __name__ == "__main__":
    main()