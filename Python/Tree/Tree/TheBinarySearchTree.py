"""
Author: Alexandre Lepage
Date: February 2020
"""
from TheTree import TheTree, TheNode

#region TheBSTNode
class TheBSTNode(TheNode):
    """
    Custom Binary Search Tree Node class
    """

    def __init__(self,k):
        """
        Constructor of the Class
        Pass the key to the parent class
        -----PSEUDO CODE-----
        (k is the value of the node)
        BSTNode(k)
         Node(k)
        -----PSEUDO CODE-----

        Keyword argument:
        x: the value of the node
        """
        super().__init__(k)
#endregion TheBSTNode class

#region TheBSTNode
class TheBinarySearchTree(TheTree):
    """
    Custom Binary Search Tree class
    """

    def __init__(self):
        """
        Constructor of the Class
        -----PSEUDO CODE-----
        BinarySearchTree()
         Tree()
        -----PSEUDO CODE-----
        """
        super().__init__()

    def insert_value(self, k):
        """
        Add a new value to the tree
        -----PSEUDO CODE-----
        (T is the tree)
        (k is the value of the node)
        InsertValue(T,k)
         y.key = k
         InsertNode(T,y)
        -----PSEUDO CODE-----

        Keyword argument:
        x:var: the value to insert
        """
        self.insert_node(TheBSTNode(k))

    def insert_node(self, z:TheNode):
        """
        Add a new node to the tree
        -----PSEUDO CODE-----
        (T is the tree)
        (k is the node to be added)
        InsertNode(T,z)
         y = NIL
         x = T.root
         while x =/= NIL
            y = x
            if z.key < x.key
                x = x.left
            else
                x = x.right
         z.parent = y
         if y == NIL
            T.root = z
         else if z.key < y.key
            y.left = z
         else
            y.right = z
        -----PSEUDO CODE-----

        Keyword argument:
        x:TheNode: the node to insert
        """
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
    
    def delete(self, z:TheNode):
        """
        Delete a node from the tree
        -----PSEUDO CODE-----
        (T is the tree, z is the node to be deleted) 
        Delete(T,z)
         if z.left == NIL
            Transplant(T, z, z.right)
        else if z.right == NIL
            Transplant(T, z, z.left)
        else
            y = Minimum(T, z.right)
            if y.parent =/= z
                Transplant(T, y, y.right)
                y.right = z.right
                y.right.parent = y
            Transplant(T, z, y)
            y.left = z.left
            y.left.parent = y
        -----PSEUDO CODE-----

        Keyword argument:
        z:TheNode: the node to delete
        """
        if z.left is None:
            self.__transplant(z, z.right)
        elif z.right is None:
            self.__transplant(z, z.left)
        else:
            y = self.minimum_node(z.right)
            if y.parent != z:
                self.__transplant(y, y.right)
                y.right = z.right
                y.right.parent = y
            self.__transplant(z, y)
            y.left = z.left
            y.left.parent = y

    def __transplant(self, u:TheNode, v:TheNode):
        """
        Replace the subtree rooted at node u
        with the subtree rooted a node v
        -----PSEUDO CODE-----
        (T is the tree, u root of subtree to replace, v root of replacement subtree) 
        Transplant(T,u,v)
         if u.parent == NIL
            T.root = v
         else if u == u.parent.left
             u.parent.left = v
         else
             u.parent.right = v
         if v =/= NIL
             v.parent = u.parent
        -----PSEUDO CODE-----

        Keyword argument:
        u:TheNode: root of subtree to replace
        v:TheNode: root of replacement subtree
        """
        if u.parent is None:
            self.root = v
        elif u == u.parent.left:
            u.parent.left = v
        else:
            u.parent.right = v
        if v is not None:
            v.parent = u.parent
#endregion TheBinarySearchTree class
