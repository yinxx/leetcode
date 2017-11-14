"""
In this implementation, 
we have 
left = [early, early+latest/2), 
right = [early+latest/2, latest]
"""
class Node:
    def __init__(early, latest, count=1):
        self.early = early
        self.latest = latest
        self.count = count
        self.left = None
        self.right = None

def add(root, time):
    if time > root.latest:
        n = Node(root.early, time+1)
        n.left = root
        n.right = Node(root.latest, time)
        return n
    if time < root.early:
        n = Node(time, root.latest)
        n.right = root
        n.left = Node(time, latest)
        return n
    while root:
        root.count += 1
        if time < (root.early + root.latest) / 2:
            # Split here:
            if not root.left:
                root.left = Node(root.early,
        else:
            root = root.right
    return root 

"""
3 cases:
    1. is contained within 1 of the children(left or right)
    2. is contained within 2 of the children
    3. entire range
"""
def query(root, left, right):
    if left < (root.early + root.latest) / 2:
        if left
    if right >= (root.early + root.latest) / 2:

