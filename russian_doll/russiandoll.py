"""
Russian doll:

given di = (wi, hi), find the maximum # of dolls nested.

1. Obviously need to sort this. Say we sort by w.
And then, for any wi == wj, we evict di if hi < hj.
This way, we can say w1 > w2 > w3 ... > wn.

2. Then, we can say for sure that we need to consider [d1,..,dn] before choosing dn+1.

3. Then, we need to choose a subsequence of dolls that are monotonically lesser:
    h1 > h2 > h3 ... > hm.

The resulting set is Sm, our answer.
"""
from collections import defaultdict as ddict
from bisect import bisect_left, bisect_right
import sys

def russian_doll(dolls):
    N = len(dolls)
    if N == 0: return 0
    if N == 1: return 1
    # Now, all widths follow w1 >= w2 >= w3 ... >= wn.
    dolls = sorted(dolls, key=lambda x : x[1])
    print(dolls) 
    # Now that we know all the dolls are monotonically increasing in width,
    # We need to perform maximum increasing subsequence on this.
    # We should use the NlogN algorithm on bisect().
    dp = [] 

    # We want it so that we can get groups of dolls of the same width:
    i = 0
    while i < N:
        group = [dolls[i][0]]
        i += 1
        while i < N:
            if dolls[i][1] == dolls[i-1][1]:
                group.append(dolls[i][0])
                i += 1
            else:
                break
        # Process the group. 
        # We want it such that we want to find the index of bisects,
        # and only update the ones with least size for same bisect.
        buckets = ddict(lambda : sys.maxsize)
        for width in group:
            to_insert = bisect_left(dp, width)
            buckets[to_insert] = min(width, buckets[to_insert])
        print(buckets)
        for idx in buckets:
            v = buckets[idx]
            if idx == len(dp):
                dp.append(v)
            else:
                dp[idx] = v
    print(dp)
    return len(dp)
if __name__ == "__main__":
    print(russian_doll([[2,1],[4,1],[6,2],[8,3],[10,5],[12,8],[14,13],[16,21],[18,34],[20,55]]))
