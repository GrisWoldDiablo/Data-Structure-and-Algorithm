"""
Author: Alexandre Lepage
Date: May 2019
"""
import time

DATA_STRUCTURE_NAME = "Stack" # The name of the data structure
STACK_SIZE = 10000000 # size of stack for speed testing

def main():
    print("---- Data structure :", DATA_STRUCTURE_NAME,"----") # Print the data structure name
    myStack = TheStack() # Create a new stack
    print("Declared a",type(myStack),".") # Print the name of the class of the stack
    populate_stack(myStack, 10) # Populate the stack with x elements
    myList = myStack.to_list() # Convert the stack to a list
    print("stack to list:", myList) # Print the list
    print("Peeking stack, key:", myStack.peek(), "is on top of the stack.") # Peek the stack
    print_stack(myStack) # Print all the elements of the stack

    # ---- Class Speed Test portion -----
    print("\nTesting stack speed with",STACK_SIZE,"elements.") # Print the annoucement of the testing portion
    myStack.clear() # Reinitialize the stack
    
    # Speed test: Push STACK_SIZE elements to the stack
    print("- Pushing elements -")
    ticks = time.time() # Get the time before pushing.
    for i in range(0, STACK_SIZE): # Push STACK_SIZE elements to the stack
        myStack.push(i) # Push i to the stack
    ticks = time.time() - ticks # Get the time difference after pushing.
    total_ticks = ticks # Get the time spent for pushing
    print("Total Seconds :", ticks) # Print the time spent in seconds.
    
    # Speed test: Convert the stack to a list
    print("- Converting stack to list -")
    ticks = time.time() # Get the time before converting to list.
    myList = myStack.to_list() # Convert the stack to a list
    ticks = time.time() - ticks # Get the time difference after converting to list.
    total_ticks += ticks # Add the time spent for converting
    print("Total Seconds :", ticks) # Print the time spent in seconds.

    # Speed test: Pop all elements from the stack
    print("- Popping all elements -")
    ticks = time.time() # Get the time before popping.
    while not myStack.empty(): # Pop all the elements from the stack
        myStack.pop() # Pop an element from the stack
    ticks = time.time() - ticks # Get the time difference after popping.
    total_ticks += ticks # Add the time spent for popping
    print("Total Seconds :", ticks) # Print the time spent in seconds.
    
    print("- Class Speed for all 3 tests -")
    print("Total Seconds :", total_ticks) # Print the time spent in seconds for all test combined

class TheStack:
    """ 
    Custom stack class
    """
    __keys:list # The array holding the keys
    __intitial_size:int = 8 # The size of the array holding the stack
    def __init__(self):
        """
        Contructor of the Class
        Initialized the list and top,
        initinial size of the list is 8.
        -----PSEUDO CODE-----
        Stack()
         Let S[0..7] be a new array
         S.top = -1
        -----PSEUDO CODE-----
        """
        self.__keys = [0] * self.__intitial_size
        self.__top = -1
            
    def push(self, key):
        """
        Add an element to the top of the stack 
        -----PSEUDO CODE-----
        (S is the Stack, key is the element to be added to the stack)
        Push(S,k)
         S.top = S.top + 1
         if S.top == S.size
            IncreaseSize(S)
         S[S.top] = k
        -----PSEUDO CODE-----

        Keyword argument:
        key: the element to be added to the stack
        """
        self.__top += 1
        if self.__top == len(self.__keys):
            self.__increase_size()
        self.__keys[self.__top] = key

    def pop(self):
        """
        Remove an element from the top of the stack
        -----PSEUDO CODE-----
        (S is the Stack)
        Pop(S)
         if S.top < 0
            Throw Error
         else
            S.top = S.top - 1
            return S[S.top + 1]
        -----PSEUDO CODE-----

        Return:
        var: the element at the top of the stack
        """
        if self.__top < 0:
            raise Exception("Cannot pop: Stack is empty!")
        else:
            self.__top -= 1
            return self.__keys[self.__top + 1]

    def count(self):
        """
        Return the amount of elements in the stack
        -----PSEUDO CODE-----
        (S is the Stack)
        Count(S)
         return S.top + 1
        -----PSEUDO CODE-----

        Return:
        int: the amount of the element in the stack
        """
        return self.__top + 1
    
    def empty(self):
        """
        Return true if the stack has 0 element
        -----PSEUDO CODE-----
        (S is the Stack)
        Empty(S)
         if S.top - 1 < 0
            return True
         else
            return False
        -----PSEUDO CODE-----

        Return:
        bool: True if stack is empty
        """
        return self.__top < 0

    def __increase_size(self):
        """
        Increase the size of the list holding the elements
        -----PSEUDO CODE-----
        (S is the Stack)
        IncreaseSize(S)
         let T[0..(length of S * 2)] be a new array
         Copy all S's element over to T
         S = T
        -----PSEUDO CODE-----
        """
        T = [0] * (len(self.__keys) * 2)
        for i in range(0,len(self.__keys)):
            T[i] = self.__keys[i]
        self.__keys = T

    def to_list(self):
        """
        Return a list of all the element in the stack, 
        in the same order pop would have returned it.
        -----PSEUDO CODE-----
        (S is the Stack)
        ToList(S)
         let T[0..(S.top + 1)] be a new array
         for i = S.top down to 0
            T[i] = S[S.top - i]
         return T
        -----PSEUDO CODE-----

        Return:
        list: the stack in a list form
        """
        T = [0] * (self.__top + 1)
        for i in range(self.__top, -1, -1):
            T[i] = self.__keys[self.__top - i]
        return T

    def peek(self):
        """
        Return the element on top of the stack,
        without removing it.
        -----PSEUDO CODE-----
        (S is the Stack)
        Peek(S)
         if S.top < 0
            Throw Error
         return S[S.top]
        -----PSEUDO CODE-----

        Return:
        var: the element on top of the stack
        """
        if self.__top < 0:
            raise Exception("Cannot peek: Stack is empty!")
        return self.__keys[self.__top]

    def clear(self):
        """
        Remove all elements from the stack,
        and initialized the list and top,
        initinial size of the list is 8.
        -----PSEUDO CODE-----
        (S is the Stack)
        Clear(S)
         let S[0..7]
         S.top = -1
        -----PSEUDO CODE-----
        """
        self.__keys = [0] * self.__intitial_size
        self.__top = -1

def populate_stack(S:TheStack, x:int):
    """
    Populate a stack with ascending values from 0 to x (exclusive)
    
    Keyword arguments:
    S:TheStack: the stack to populate
    x:int: the amount of element to add to the stack
    """
    print("Adding", x, "element(s) to the stack.")
    print("Added: ", end="")
    for i in range(0, x):
        if i != x - 1:
            print(i, end=",")
        else:
            print(i, "to the stack in that order.")
        S.push(i)

def print_stack(S:TheStack):
    """
    Emtpy the stack and print all its elements
    
    Keyword argument:
    S:TheStack: the stack to print
    """
    print("There is", S.count(), "element(s) in the stack.")
    print("Popping all the element(s) of the stack: ", end="")
    while not S.empty():
        if S.count() != 1:
            print(S.pop(), end=",")
        else:
            print(S.pop())

""" Entry point """
if __name__ == "__main__":
    main()
