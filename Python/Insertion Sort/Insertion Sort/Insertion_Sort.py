"""
Author: Alexandre Lepage
Date: May 2019
"""
import random
import time

ALGORITHM_NAME = "Insertion Sort" # The name of the algorithm used for sorting
random.seed(2019) # Random Seed number to keep values constant.
LIST_SIZE = 50000 # Set the size of the list to 50,000.

def main():
    myList = [0] * LIST_SIZE # A list to be sorted.
    populate_list(myList) # Fill the list with random numbers.
    
    #print_list(myList) # Display list before sorting.

    ticks = time.time() # Get the time before sorting.
    insertion_sort(myList) # Sort the list
    ticks = time.time() - ticks # Get the time difference after sorting.

    #print_list(myList) # Display list after sorting.

    print("Sorting an array of type", type(myList), "of", LIST_SIZE, "elements.") # Print the type of the list and the amount of element in it.
    print("Algorithm:", ALGORITHM_NAME) # Print the name of the algorithm used.
    print("Total Seconds :", ticks) # Print the time spent in seconds.

def insertion_sort(A:list):
    """
    Sort the array using insertion sort algorithm.
    -----PSEUDO CODE-----
    (A is an Array with index 0..n)
    InsertionSort(A)
     for j = 1 to length of A - 1
         key = A[j]
         i = j - 1
         while i >= 0 and A[i] > key
             A[i + 1] = A[i]
             i = i + 1
         A[i+1] = key
    -----PSEUDO CODE-----
    
    Keyword arguments:
    A:list: the list to be sorted
    """
    for j in range(0, len(A)):
        key = A[j]
        i = j - 1
        while i >= 0 and A[i] > key:
        	A[i + 1] = A[i]
        	i -= 1
        A[i + 1] = key

def populate_list(A:list):
    """
    Populate a list with random numbers between -100,000 to 100,000
    
    Keyword arguments:
    A:list: the list to populate
    """
    for i in range(0, len(A)):
        A[i] = random.randint(-100000,100000)

def print_list(A:list):
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