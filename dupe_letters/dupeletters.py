"""
Here's a revised try.
"""
from collections import defaultdict
def dupeletters(sequence):
    s = ['$']
    visit = set()
    freq = defaultdict(int)
    for c in sequence:
        freq[c] += 1 
    for c in sequence:
        freq[c] -= 1
        if c in visit:
            continue
        # Then we can remove the previous elements until c is
        # At top of the stack.
        while s[-1] > c:
            if not freq[s[-1]]: break
            visit.remove(s.pop())
        visit.add(c)
        s.append(c)
    return "".join(s)[1:]

s = "badecfabfeba"
print(s)
print(dupeletters(s))
