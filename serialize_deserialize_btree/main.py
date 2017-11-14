from collections import deque
class TreeNode(object):
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
class Codec:
    NULL = "x"
    DELIM = ","
    def serialize(self, root):
        """Encodes a tree to a single string.
        
        :type root: TreeNode
        :rtype: str
        """
        s = ""
        q = deque([root])
        while len(q):
            n = q.popleft()
            if n is None:
                s += Codec.NULL + Codec.DELIM
            else:
                s += str(n.val) + Codec.DELIM
                q.append(n.left)
                q.append(n.right)
        return s[:-1]

    def deserialize(self, data):
        """Decodes your encoded data to tree.
        
        :type data: str
        :rtype: TreeNode
        """
        nodes = data.split(Codec.DELIM)
        create_node = lambda s : TreeNode(int(s)) if s != 'x' else None
        if nodes[0] == 'x':
            return None
        root = TreeNode(int(nodes[0]))
        q = deque([root]) 
        ctr = 1
        while len(q):
            n = q.popleft()
            if n is None:
                continue
            else:
                n.left = create_node(nodes[ctr])
                ctr += 1
                n.right = create_node(nodes[ctr])
                ctr += 1
                q.append(n.left)
                q.append(n.right)
        return root
