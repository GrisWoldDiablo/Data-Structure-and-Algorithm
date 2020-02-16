"""
Author: Alexandre Lepage
Date: May 2019
"""

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
            
    def push(self, k):
        """
        Add an element to the top of the stack 
        -----PSEUDO CODE-----
        (S is the Stack, k is the element to be added to the stack)
        Push(S,k)
         S.top = S.top + 1
         if S.top == S.size
            IncreaseSize(S)
         S[S.top] = k
        -----PSEUDO CODE-----

        Keyword argument:
        k: the element to be added to the stack
        """
        self.__top += 1
        if self.__top == len(self.__keys):
            self.__increase_size()
        self.__keys[self.__top] = k

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
