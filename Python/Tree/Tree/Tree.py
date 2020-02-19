"""
Author: Alexandre Lepage
Date: February 2020
"""
import time
import random
from TheBinarySearchTree import TheBinarySearchTree, TheBSTNode
from TheTree import TheTree, TheNode

DATA_STRUCTURE_NAME = "Tree" # The name of the data structure
random.seed(2019) # Random Seed number to keep values constant.
TREE_SIZE = 1000000 # Size of the tree for speed testing
TEST_AMOUNT = 50000 # Amount of item that will be used for some testing.
f = "{:,d}" # string formating for numbers
""" Lists for testing setup """
valueList:list = [0] * TREE_SIZE
delTestList:list = []
searchTestList:list = []

def main():
    print("---- Data structure :", DATA_STRUCTURE_NAME,"----") # Print the data structure name

    """ Setting up the values for testing """
    print("- Inititializing test values and lists -")
    populate_list(valueList, TREE_SIZE) # Getting a series of values to insert in the tree
    get_random_values(valueList, delTestList, TEST_AMOUNT) # Getting a series of values to delete from the tree from the valueList
    get_random_values(valueList, searchTestList, TEST_AMOUNT) # Getting a series of values to search from the tree from the valueList

    print("\n- Starting tests -")
    myBSTree = TheBinarySearchTree() # Creating a Binary Search Tree object
    tree_test(myBSTree) # Sending the tree to get tested

def tree_test(T:TheTree):
    """
    Perform a series of test for the tree
    """
    
    print("---",type(T),"---")
    #region INSERT_TEST
    print("- Inserting",f.format(TREE_SIZE),"elements -")
    ticks = time.time() # Get the time before inserting.
    for i in range(TREE_SIZE):
        T.insert_value(valueList[i]) # Inserting values into the Tree.
    ticks = time.time() - ticks # Get the time difference after inserting.
    totalTime = ticks # Get the time spend for this test.
    print("\tTotal Seconds:", ticks) # Print the time spent in seconds.
    #endregion

    #region DELETE_VALUE_TEST
    print("- Deleting", f.format(TEST_AMOUNT), "values -")
    ticks = time.time() # Get the time before deleting.
    for i in range(TEST_AMOUNT):
        T.delete_value(delTestList[i]) # Deleting values from the tree.
    ticks = time.time() - ticks # Get the time difference after deleting.
    totalTime += ticks # Add the time spend for this test.
    print("\tTotal Seconds:", ticks) # Print the time spent in seconds.
    #endregion

    #region SEARCH_VALUE_TEST
    print("- Searching for", f.format(TEST_AMOUNT), "values -")
    foundNodes:list = []
    ticks = time.time() # Get the time before searching.
    for i in range(TEST_AMOUNT):
        x = T.search_value(searchTestList[i])
        if x is not None:
            foundNodes.append(x) # Adds the node found to the list
    ticks = time.time() - ticks # Get the time difference after searching.
    totalTime += ticks # Add the time spend for this test.
    print("Found",f.format(len(foundNodes)), "nodes. -")
    print("\tTotal Seconds:", ticks) # Print the time spent in seconds.
    #endregion

    #region DELETE_NODE_FOUND_TEST
    print("- Deleting", f.format(len(foundNodes)), "nodes -")
    ticks = time.time() # Get the time before deleting.
    for i in range(len(foundNodes)):
        T.delete_value(foundNodes[i].key) # Deleting found nodes from the tree.
    ticks = time.time() - ticks # Get the time difference after deleting.
    totalTime += ticks # Add the time spend for this test.
    print("\tTotal Seconds:", ticks) # Print the time spent in seconds.
    #endregion

    #region GET_MINIMUM_TEST
    print("- Get Mininmum node -")
    ticks = time.time() # Get the time before retreiving minimum node.
    print(T.minimum()) # Prints the Minimum node
    ticks = time.time() - ticks # Get the time difference after retreiving minimum node.
    totalTime += ticks # Add the time spend for this test.
    print("\tTotal Seconds:", ticks) # Print the time spent in seconds.
    #endregion

    #region GET_MAXIMUM_TEST
    print("- Get Maximum node -")
    ticks = time.time() # Get the time before retreiving maximum node.
    print(T.maximum()) # Prints the Maximum node
    ticks = time.time() - ticks # Get the time difference after retreiving maximum node.
    totalTime += ticks # Add the time spend for this test
    print("\tTotal Seconds:", ticks) # Print the time spent in seconds.
    #endregion

    #region GET_HEIGHT_TEST
    print("- Get Tree height -")
    ticks = time.time() # Get the time before retreiving maximum node.
    print("The tree has a height of", T.height(),".") # Prints the tree height
    ticks = time.time() - ticks # Get the time difference after retreiving maximum node.
    totalTime += ticks # Add the time spend for this test
    print("\tTotal Seconds:", ticks) # Print the time spent in seconds.
    #endregion

    print("- Class Speed for all tests -")
    print("\tTotal Seconds:", totalTime,"\n")

def populate_tree(T:TheTree, x:int):
    """
    Populate a tree with ascending values from 0 to x (exclusive)
    
    Keyword arguments:
    S:TheBinarySearchTree: the tree to populate
    x:int: the amount of element to add to the tree
    """
    print("Adding", x, "element(s) to the tree.")
    print("Added: ", end="")
    for i in range(x):
        k = random.randint(-100000,100000)
        if i != x - 1:
            print(k, end=",")
        else:
            print(k, "to the tree in that order.")
        T.insert_value(k)

def populate_list(A:list, x:int):
    """
    Populate a list with numbers between -x/2 to x/2
    Then shuffle the list
    Keyword arguments:
    A:list: the list to populate
    x:int: size of the list and range
    """
    size = int(x/2)
    for i in range(-size, size):
        A[i] = i
    random.shuffle(A)
    
def get_random_values(A:list, B:list, x:int):
    """ 
    Fill list B with random values from list A.

    Keyword arguments:
    A:list: the list to get values from
    B:list: the list to fill
    x:int: the amount of values to get from list A
    """
    B.extend(random.choices(A, k=x))

def print_list(A:list):
    """ 
    Print the list's elements

    Keyword arguments:
    A:list: the list to populate
    """
    print("---- List ----")
    print(A)
    print("---- ----")

""" Entry point """
if __name__ == "__main__":
    main()
