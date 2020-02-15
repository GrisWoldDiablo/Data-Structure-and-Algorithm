"""
Author: Alexandre Lepage
Date: May 2019
"""
import time
import TheStack

DATA_STRUCTURE_NAME = "Stack" # The name of the data structure
STACK_SIZE = 10000000 # size of stack for speed testing

def main():
    print("---- Data structure :", DATA_STRUCTURE_NAME,"----") # Print the data structure name
    myStack = TheStack.TheStack() # Create a new stack
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
