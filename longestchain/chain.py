"""
Find longest chain, which just means find the longest # of intervals that don't overlap.

This is greedy interval scheduling but with no overlaps on the rhs.
"""

def longest_chain(pairs):
    # Sort by end time
    if not len(pairs): return 0
    pairs = sorted(pairs, key = lambda x : x[1])
    old = pairs[0]
    count = 1
    print(old)
    for p in pairs[1:]:
        # The idea is to greedily choose the first pair we see, and then update to new pair
        # as long as new[0] > old[1].
        if p[0] <= old[1]: continue
        old = p
        print(old)
        count += 1
    return count

if __name__ == "__main__":
    longest_chain([[1,2], [2,3], [3,4]])
