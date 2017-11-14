"""
Max rectangle and max square are 2 very different beasts.
We cannot use max square algorithm on this.

Just by inspecting by eye, we can see that if we do a left->right sweep,
we can gather a vector of cumsums:

e.x.:
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

gives:

[1,1,1,1] -> sum = 4
[0,0,2,0] -> sum = 2
[1,1,3,0] -> sum = 1+1+1 = 3
[0,2,3,1] -> sum = 1+1+1 = 3
[0,3,5,0] -> sum = 3+3 = 6
"""

def maxrectangle(matrix):
    """
    :type matrix: List[List[str]]
    :rtype: int
    """
    matrix = [[int(v) for v in l] for l in matrix]
    if not len(matrix) or not len(matrix[0]): return 0
    N, M = len(matrix), len(matrix[0])
    cumsums = [0]*M
    maxsum = 0
    
    def largestHistogram(heights):
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

    for x in range(N):
        # Do max non-segmented sum at the same time:
        for y in range(M):
            if not matrix[x][y]: 
                cumsums[y] = 0
            else: 
                cumsums[y] += 1
        maxsum = max(maxsum, largestHistogram(list(cumsums)))
        
    return maxsum
