"""
We are trying to minimize the expected reading time.

If we start at any node n, the expected reading time can be defined recursively as:
    E[n] = n + (E[n.c1] + E[n.c2] ... + E[n.cm])/m
"""
import json
tree = "3 100 1 1\n1 2\n1 3\n1 4"
class Node():
    def __init__(self, value):
        self.val = value
        self.children = set()

def make_nodes(s):
    s = s.split("\n")
    ns = [Node(int(x)) for i, x in enumerate(s[0].split(" "))]
    for p in s[1:]:
        l, r = [int(x) for x in p.split(" ")]
        ns[l-1].children.add(ns[r-1])  
        ns[r-1].children.add(ns[l-1])
    return ns

def relatedquestions(nodes):
    """
    nodes is a list of nodes.
    """
    N = len(nodes)
    if N == 0: return 0
    # Arbitrary choose
    root = nodes[0]
    
    # Remove all back-edges 
    def remove_back(n, parent):
        if parent != None:
            n.children.remove(parent)
        for c in n.children:
            remove_back(c, n)
    remove_back(root, None)
   
    # Compute the subtree expected values:
    v = {}
    f = {}
    def expv(n):
        if not n: return 0
        v[n] = n.val + (sum([expv(c) for c in n.children])/len(n.children) if len(n.children) else 0)
        return v[n] 

    expv(root) 
    f[root] = v[root]
    # Now we should start at the root and pivot 1 at a time
    def expf(n, prev):
        if not n: return 0
        f[n] = n.val + 
        


nodes = make_nodes(tree)
relatedquestions(nodes)



