"""
Author: Alexandre Lepage
Date: February 2020
"""

from TheTree import TheTree, TheNode

class TheBSTNode(TheNode):
    """
    Custom Binary Search Tree Node class
    """

    def __init__(self,k):
        super().__init__(k)

    def successor(self, x:TheNode): 
        """
        Method Override
        """
        if x.right is not None:
            return TheBinarySearchTree.get_min_node(x)
        y = x.parent
        while y is not None and x is y.right:
            x = y
            y = y.parent
        return y

    def predecessor(self, x:TheNode): 
        """
        Method Override
        """
        if x.left is not None:
            return TheBinarySearchTree.get_min_node(x)
        y = x.parent
        while y is not None and x is y.left:
            x = y
            y = y.parent
        return y

class TheBinarySearchTree(TheTree):
    """
    Custom Binary Search Tree class
    """

    def __init__(self):
        super().__init__()

    def insert_value(self, k):
        self.insert_node(TheBSTNode(k))

    def insert_node(self, z:TheNode):
        y = None
        x = self.root
        while x is not None:
            y = x
            if z.key < x.key:
                x = x.left
            else:
                x = x.right
        z.parent = y
        if y is None:
            self.root = z
        elif z.key < y.key:
            y.left = z
        else:
            y.right = z
    
    def delete(self, k):
        pass

