"""
Alien dictionary is pretty much a topo-sort question.

The words presented to us forms a graph, such that:

for any i-th index of 2 contiguous strings s1, and s2:
    s1[i] < s2[i].

We can take this to mean that s2[i] is in s1[i].child.

We can then perform a topological sorting to get the results.
"""

from collections import defaultdict as ddict
def alien_order(words):
    N = len(words)
    if N == 1:
        # There's nothing to compare.
        return words[0]

    order = ddict(list)
    # indegree is how many times this letter is > some other letter.
    # If a node has an indegree of 0, it must be the smallest letter.
    indegree = ddict(int)
    candidates = set()
    
    def insert_orders(lword, rword):
        M = min(len(lword), len(rword))
        for i in range(M):
            lc, rc = lword[i], rword[i]
            candidates.add(lc)
            candidates.add(rc)
            if lc == rc: continue
            order[lc].append(rc)
            indegree[rc] += (lc != rc)
            return
        if len(rword) > len(lword): lword = rword
        for c in lword[M:]:
            candidate.add(c)

    # Load up the graph, and in-degree vector.
    for i in range(N-1):
        curword = words[i]
        nextword = words[i+1]
        insert_orders(curword, nextword)
    
    # Perform topological sorting
    ans = ""
    leaves = [k for k in candidates if not indegree[k]]
    while leaves:
        leaf = leaves.pop() 
        ans += leaf
        for child in order[leaf]:
            indegree[child] -= 1
            if not indegree[child]:
                leaves.append(child)
    for k,v in indegree.items():
        if v: return ""
    return ans
