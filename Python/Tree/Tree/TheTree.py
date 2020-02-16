from abc import ABC, abstractmethod

class TheNode(ABC):
    """
    Custom abstract Tree Node class
    """
    left:None
    right:None
    parent:None
    key:None

    def __init__(self,k):
        self.left = None
        self.right = None
        self.parent = None
        self.key = k

    @abstractmethod
    def predecessor(self, node=None):
        pass

    @abstractmethod
    def successor(self, node=None):
        pass

class TheTree(ABC):
    """
    Custom abstract Tree class
    """
    root:TheNode
    nodes:list

    def __init__(self):
        self.root = None

    @abstractmethod
    def insert_value(self, k):
        pass

    @abstractmethod
    def insert_node(self, z:TheNode):
        pass

    @abstractmethod
    def delete(self, key):
        pass

    def search(self, k):
        # return self.__search(self.root, k)
        return self.__search_iterative(self.root, k)
        pass
    
    def __search(self, x:TheNode, k):
        if x is None or k == x.key:
            return x
        if k < x.key:
            return self.__search(x.left, k)
        else:
            return self.__search(x.right, k)

    def __search_iterative(self, x:TheNode, k):
        while x is not None and k != x.key:
            if k < x.key:
                x = x.left
            else:
                x = x.right;
        return x

    def minimum(self):
        return __minimum(self.root)

    def __minimum(self, x:TheNode):
        while x.left is not None:
            x = x.left
        return x

    def maximum(self):
        return __maximum(self.root)
    
    def __maximum(self, x:TheNode):
        while x.right is not None:
            x = x.right
        return x
    
    def predecessor(self, x:TheNode):
        if x.left != None:
            return self.__maximum(x.left)
        y = x.parent
        while y is not None and x is y.left:
            x = y
            y = y.parent
        return y
    
    def successor(self, x:TheNode):
        if x.right != None:
            return self.__minimum(x.right)
        y = x.parent
        while y is not None and x is y.right:
            x = y
            y = y.parent
        return y

    def inorder_tree_walk(self, node:TheNode):
        """
        Walks through all the nodes in the tree and print their keys
        """
        if node != None:
            self.inorder_tree_walk(node.left)
            print(node.key)
            self.inorder_tree_walk(node.right)


