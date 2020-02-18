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
TREE_SIZE = 10000000 # Size of the tree for speed testing
TEST_AMOUNT = 500 # Amount of item that will be used for some testing.

# ---- Lists for testing setup ----
myList = [0] * TREE_SIZE
delTestList = [0] * TEST_AMOUNT
searchTestList = [0] * TEST_AMOUNT

def main():
    print("---- Data structure :", DATA_STRUCTURE_NAME,"----") # Print the data structure name


    myBSTree = TheBinarySearchTree()
    tree_test(myBSTree)

def tree_test(T:TheTree):
    populate_tree(T,20)
    print(T.height())
    #print(T.search_value(30314).successor())

    print(T.predecessor(T.search_value(30314)))

    T.inorder_walk_tree()

def populate_tree(T:TheTree, x:int):
    """
    Populate a tree with ascending values from 0 to x (exclusive)
    
    Keyword arguments:
    S:TheBinarySearchTree: the tree to populate
    x:int: the amount of element to add to the tree
    """
    print("Adding", x, "element(s) to the tree.")
    print("Added: ", end="")
    for i in range(0, x):
        k = random.randint(-100000,100000)
        if i != x - 1:
            print(k, end=",")
        else:
            print(k, "to the tree in that order.")
        T.insert_value(k)

def populate_list(A:list):
    """
    Populate a list with random numbers between -100,000 to 100,000
    
    Keyword arguments:
    A:list: the list to populate
    """
    for i in range(0, LIST_SIZE):
        A[i] = random.randint(-100000,100000)

""" Entry point """
if __name__ == "__main__":
    main()
