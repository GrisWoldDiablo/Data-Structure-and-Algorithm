"""
Author: Alexandre Lepage
Date: February 2020
"""

from abc import ABC, abstractmethod
class Test(ABC):

    test = None
    def __init__(self):
        self.test = "hello"

    @abstractmethod
    def over(self,node=None):
        pass

    def bored(self):
        print("parent bored");
        pass

class Tester(Test):

    def over(self):
        self.over(self)

    def over(self,node=None):
        if node is None:
            print("None Arg")
            self.over(self)
            return
        print(node.test)


import time
import random
from TheBinarySearchTree import TheBinarySearchTree
from TheTree import TheTree

DATA_STRUCTURE_NAME = "Tree" # The name of the data structure
random.seed(2019) # Random Seed number to keep values constant.
TREE_SIZE = 10000000 # size of the tree for speed testing

def main():
    
    print("---- Data structure :", DATA_STRUCTURE_NAME,"----") # Print the data structure name
    myBSTree = TheBinarySearchTree()
    tree_test(myBSTree)

def tree_test(T:TheTree):
    populate_tree(T,20)
    T.inorder_tree_walk(T.root)
    pass

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

def print_tree(T:TheTree):
    """
    print all the elements of a tree using a specific walk
    
    Keyword argument:
    T:TheBinarySearchTree: the tree to print
    """
    #print("There is", S.count(), "element(s) in the tree.")
    #print("Popping all the element(s) of the tree: ", end="")
    #while not T.empty():
    #    if T.count() != 1:
    #        print(T.pop(), end=",")
    #    else:
    #        print(T.pop())

""" Entry point """
if __name__ == "__main__":
    main()