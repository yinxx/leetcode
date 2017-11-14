"""
The max histogram can be found in O(N^2) if we just measure the size of all possible sub-histograms.

However, we can do this in O(N) by a greedy approach:

Suppose we have heights h1,h2,...,hn. We will denote the max sum of histogram INCLUDING hi to be S(hi).

For example:
[5,4,3,2,1] - We add new minimums to consideration:
    [5]
    [5,4]

"""

def largestRectangleArea(self, heights):
    """
    :type heights: List[int]
    :rtype: int
    """
    maxsize = 0
    stk = [(0,-1)]
    heights.append(0)

    for i,h in enumerate(heights):
        new_i = i
        while h < stk[-1][0]:
            prevh, idx = stk.pop()
            maxsize = max(maxsize, prevh * (i-idx))
            new_i = min(i, idx)
        stk.append((h, new_i))
    return maxsize
