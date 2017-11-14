class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Codec:
    DELIM = ","
    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        def preorder(n, s):
            if not n: return s
            s += n.v + Codec.DELIM
            s = preorder(n.left, s)
            s = preorder(n.right, s)
            return s
        return preorder(root, "")[:-1]

    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """
        ordering = [int(x) for x in data.split(Codec.DELIM)]
        # Do the old divide and conquer:
        sorted_ordering = sorted(ordering)
        d = {(v, k) for k, v in enumerate(sorted_ordering)}

        def make(idx, order, stop):
            """
            makes the tree using the sorted ordering.
            """
            if d[idx] >= stop: return None
            n = TreeNode(order[idx])
            n.left = make(idx + 1, order, d[order[idx]])
            n.right = make(d[order[idx]]+1, order, stop)
            return n
        return make(0, ordering, len(ordering))

        
def deserialize(data):
    """Decodes your encoded data to tree.
    
    :type data: str
    :rtype: TreeNode
    """
    order = [int(x) for x in data.split(Codec.DELIM)]
    # Do the old divide and conquer:
    sorted_order = sorted(order)

    def make(idx, stopval):
        """
        makes the tree using the sorted ordering.
        It will keep on marching until the stop value.
        """
        if idx >= len(order) or order[idx] > stopval:
            return None, idx
        n = TreeNode(order[idx])
        n.left, idx = make(idx+1, order[idx])
        n.right, idx = make(idx+1, stopval)
        return n, idx
    return make(0, sorted_order[-1])

if __name__ == "__main__":
    deserialize("2,1,3")
    
     
    
     
    
