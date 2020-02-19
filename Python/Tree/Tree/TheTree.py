"""
Author: Alexandre Lepage
Date: February 2020
"""
from abc import ABC, abstractmethod

#region TheNode
class TheNode(ABC):
    """
    Custom abstract Tree Node class
    """

    def __init__(self,k):
        """
        Constructor of the Class
        Initialize left, right and parent node as None
        Initialize key as received
        -----PSEUDO CODE-----
        (k is the value of the node)
        Node(k)
         left = NIL
         right = NIL
         parent = NIL
         key = k
        -----PSEUDO CODE-----

        Keyword argument:
        k: the value of the node
        """
        self.left = None   # Node on the left of this one
        self.right = None  # Node on the right of this one
        self.parent = None # Node above/parent of this node
        self.key = k       # Key value this node is holding

    def predecessor(self): 
        """
        Get the predecessing node of the current node
        -----PSEUDO CODE-----
        (x is the current node)
        Predecessor(x)
         if x.left =/= NIL
            return TreeMaximum(x)
         y = x.parent
         while y =/= NIL and x == y.left
            x = y
            y = y.parent
         return y
        -----PSEUDO CODE-----

        Return:
        TheNode: found node or None
        """
        if self.left is not None:
            return TheTree.maximum_node(self.left)
        y = self.parent
        while y is not None and self is y.left:
            self = y
            y = y.parent
        return y

    def successor(self): 
        """
        Get the successing node of the current node
        -----PSEUDO CODE-----
        (x is the current node)
        Successor(x)
         if x.right =/= NIL
            return TreeMinimum(x)
         y = x.parent
         while y =/= NIL and x == y.right
            x = y
            y = y.parent
         return y
        -----PSEUDO CODE-----

        Return:
        TheNode: found node or None
        """
        if self.right is not None:
            return TheTree.minimum_node(self.right)
        y = self.parent
        while y is not None and self is y.right:
            self = y
            y = y.parent
        return y

    def __str__(self):
        """
        Implementing class string representation

        
        Return:
        str: formated represetation of the object variables
        """
        pk = "NIL"
        lk = "NIL"
        rk = "NIL"
        if self.parent is not None:
            pk = self.parent.key
        if self.left is not None:
            lk = self.left.key
        if self.right is not None:
            rk = self.right.key
        return 'Node:(' + str(self.key) + ', Parent=' + str(pk) + ', Left=' + str(lk) + ', Right=' + str(rk) + ')'
    
    def height(self):
        return self._height(self)

    def _height(self, x):
        """
        get the height of the node
        -----PSEUDO CODE-----
        (x is the node)
        Height(x)
         if x == NIL
            return -1
         l = Height(x.left) + 1
         r = Height(x.right) + 1
         if l > r
            return l
         else
            return r
        -----PSEUDO CODE-----

        Keyword argument:
        x:var: the node to get height of
        Return:
        int: the height of the node
        """
        if x is None:
            return -1

        leftHeight = self._height(x.left) + 1
        rightHeight = self._height(x.right) + 1

        if leftHeight > rightHeight:
            return leftHeight
        else:
            return rightHeight
#endregion TheNode class

#region TheTree
class TheTree(ABC):
    """
    Custom abstract Tree class
    """

    def __init__(self):
        """
        Constructor of the Class
        Initialize left, right and parent node as None
        Initialize key as received
        -----PSEUDO CODE-----
        Tree()
         root = NIL
        -----PSEUDO CODE-----
        """
        self.root = None # The node at the root of the tree

    @abstractmethod
    def insert_value(self, k):
        pass

    @abstractmethod
    def insert_node(self, z:TheNode):
        pass

    @abstractmethod
    def delete_value(self, k):
        pass

    @abstractmethod
    def delete_node(self, z:TheNode):
        pass

    def search_value(self, k):
        """
        Find a node with a specific value
        -----PSEUDO CODE-----
        (T is the Tree, k is the value to look for)
        Search(T,k)
         return Search(T.root,k)
        -----PSEUDO CODE-----
        
        Keyword argument:
        k:var: the value to search for
        Return:
        TheNode: found node or None
        """
        return self._search(k)

    def search_node(self, x:TheNode):
        """
        Find a node
        -----PSEUDO CODE-----
        (T is the Tree, x is the node to look for)
        Search(T,x)
         return Search(T.root,x.key)
        -----PSEUDO CODE-----
        
        Keyword argument:
        x:TheNode: the node to search for
        Return:
        TheNode: found node or None
        """
        if isinstance(x, TheNode) is False:
            raise TypeError("Wrong type provided")
        return self._search(x.key)

    def _search(self, k):
        """
        Find a node with a specific value
        -----PSEUDO CODE-----
        (T is the Tree, k is the value to look for)
        Search(T,k)
         return Search(T.root,k)
        -----PSEUDO CODE-----
        
        Keyword argument:
        k:var: the value to search for
        Return:
        TheNode: found node or None
        """
        # Here I have made 2 searching methods, 
        # one that uses recursive and the other iterative approach
        # return self.__search_recursive(self.root, k)
        return self._search_iterative(self.root, k)
    
    def _search_recursive(self, x:TheNode, k):
        """
        Find a node with a specific value,
        using the recursive approach.
        -----PSEUDO CODE-----
        (x is the starting point (root) of the search)
        (k is the value to look for)
        Search(x,k)
         if x == NIL or k == x.key
            return x
         if k < x.key
            return Search(x.left,k)
         else
            return Search(x.right,k)
        -----PSEUDO CODE-----

        Keyword argument:
        x:TheNode: the starting point (root) of the search
        k:var: is the value to look for
        Return:
        TheNode: found node or None
        """
        if x is None or k == x.key:
            return x
        if k < x.key:
            return self._search_recursive(x.left, k)
        else:
            return self._search_recursive(x.right, k)

    def _search_iterative(self, x:TheNode, k):
        """
        Find a node with a specific value,
        using the iterative approach.
        -----PSEUDO CODE-----
        (x is the starting point (root) of the search)
        (k is the value to look for)
        Search(x,k)
         while x =/= NIL and k =/= x.key
            if k < x.key
                x = x.left
            else
                x = x.right
         return x
        -----PSEUDO CODE-----

        Keyword argument:
        x:TheNode: the starting point (root) of the search
        k:var: is the value to look for
        Return:
        TheNode: found node or None
        """
        while x is not None and k != x.key:
            if k < x.key:
                x = x.left
            else:
                x = x.right
        return x

    def minimum(self):
        """
        Find the minimum node in the tree
        -----PSEUDO CODE-----
        (T is the Tree)
        Minimum(T)
         return Minimum(T.root)
        -----PSEUDO CODE-----

        Return:
        TheNode: minimum node of the tree
        """
        return self.minimum_node(self.root)

    @staticmethod
    def minimum_node(x:TheNode):
        """
        Find the minimum node starting from this root
        -----PSEUDO CODE-----
        (x is the starting root)
        Minimum(x)
         while x.left =/= NIL
            x = x.left
         return x
        -----PSEUDO CODE-----

        Keyword argument:
        x: the root to start to
        Return:
        TheNode: minimum node of this root
        """
        if isinstance(x, TheNode) is False:
            raise TypeError("Wrong type provided")
        while x.left is not None:
            x = x.left
        return x

    def maximum(self):
        """
        Find the maximum node in the tree
        -----PSEUDO CODE-----
        (T is the Tree)
        Maximum(T)
         return Maximum(T.root)
        -----PSEUDO CODE-----
        
        Return:
        TheNode: maximum node of the tree
        """
        return self.maximum_node(self.root)

    @staticmethod
    def maximum_node(x:TheNode):
        """
        Find the maximum node starting from this root
        -----PSEUDO CODE-----
        (x is the starting root)
        Maximum(x)
         while x.right =/= NIL
            x = x.right
         return x
        -----PSEUDO CODE-----

        Keyword argument:
        x: the root to start to
        Return:
        TheNode: maximum node of this root
        """
        if isinstance(x, TheNode) is False:
            raise TypeError("Wrong type provided")
        while x.right is not None:
            x = x.right
        return x

    @staticmethod
    def predecessor(x:TheNode):
        """
        Get the predecessor node of the current node
        -----PSEUDO CODE-----
        (x is the current node)
        Predecessor(x)
         if x.left =/= NIL
            return Maximum(x.left)
         y = x.parent
         while y =/= NIL and x == y.left
            x = y
            y = y.parent
         return y
        -----PSEUDO CODE-----

        Keyword argument:
        x:TheNode: the current node to look for its predecessor
        Return:
        TheNode: found node or None
        """
        if isinstance(x, TheNode) is False:
            raise TypeError("Wrong type provided")
        if x.left is not None:
            return TheTree.maximum_node(x.left)
        y = x.parent
        while y is not None and x == y.left:
            x = y
            y = y.parent
        return y

    @staticmethod
    def successor(x:TheNode):
        """
        Get the successor node of the current node
        -----PSEUDO CODE-----
        (x is the current node)
        Successor(x)
         if x.right =/= NIL
            return Minimum(x.right)
         y = x.parent
         while y =/= NIL and x == y.right
            x = y
            y = y.parent
         return y
        -----PSEUDO CODE-----

        Keyword argument:
        x:TheNode: the current node to look for its successor
        Return:
        TheNode: found node or None
        """
        if isinstance(x,TheNode) is False:
            raise TypeError("Wrong type provided")
        if x.right is not None:
            return TheTree.minimum_node(x.right)
        y = x.parent
        while y is not None and x == y.right:
            x = y
            y = y.parent
        return y

    def inorder_walk_tree(self):
        """
        Walks through all the nodes in a tree
        in order and print their keys
        -----PSEUDO CODE-----
        (T is the tree)
        InorderWalkTree(T)
         InorderWalk(T.root)
        -----PSEUDO CODE-----
        """
        self._inorder_walk(self.root)

    def _inorder_walk(self, x:TheNode):
        """
        Walks through all the nodes on the tree, starting
        at a speficic node in order and print their keys
        -----PSEUDO CODE-----
        (x is the root of the tree)
        InorderWalk(x)
         if x =/= NIL
            InorderWalk(x.left)
            Print x.key
            InorderWalk(x.right)
        -----PSEUDO CODE-----

        Keyword argument:
        x:TheNode: the root of the tree
        """
        if x is not None:
            self._inorder_walk(x.left)
            print(x)
            self._inorder_walk(x.right)
            
    def height(self):
        """
        get the height of the tree
        -----PSEUDO CODE-----
        (T is the tree)
        Height(T)
        -----PSEUDO CODE-----

        Return:
        int: the height of the tree 
        """
        return self.root.height()
#endregion TheTree class