#http://code.activestate.com/recipes/286239/

class Node():
    left,right,data = None, None, 0

    def __init__(self, data):
        self.data = data

class BST():
    def __init__(self):
        self.root = None

    def addNode(self, data):
        return Node(data)

    def insert(self, root, data):
        if root == None:
            return self.addNode(data)
        else:
            if data <= root.data:
                root.left = self.insert(root.left, data)
            else:
                root.right = self.insert(root.right, data)

        return root

    def lookup(self, root, target):
        if root == None:
            return 0
        else:
            if target == root.data:
                return 1
            else:
                if target < root.data:
                    return self.lookup(root.left, target)
                else:
                    return self.lookup(root.right, target)
    
    def minValue(self, root):
        while(root.left != None):
            root = root.left
        return root.data

    def maxDepth(self, root):
        if root == None:
            return 0
        else:
            ldepth = self.maxDepth(root.left)
            rdepth = self.maxDepth(root.right)
            return max(ldepth, rdepth) + 1

    def size(self, root):
        if root == None:
            return 0
        else:
            return self.size(root.left) + self.size(root.right) + 1

    def printTree(self, root):
        if root == None:
            pass
        else:
            self.printTree(root.left)
            print root.data
            self.printTree(root.right)

if __name__ == "__main__":
    bst = BST()
    root = bst.addNode(0)
    
    for i in range(0,5):
        data = int(raw_input("insert the node value nr %d: " % i ))
        bst.insert(root,data)

    print
    
    bst.printTree(root)

    data = int(raw_input("insert val to find:"))
    if bst.lookup(root, data):
        print "found"
    else:
        print "not found"

    print bst.minValue(root)
    print bst.maxDepth(root)
    printbst.size(root)
    
