"""
Recurrence relation:

    Denote l = min(OPT(i-1,j), OPT(i,j-1), OPT(i-1,j-1))
    OPT(i,j) = l + 1
"""

def maxsquare(matrix):
    if not len(matrix) or not len(matrix[0]): return 0
    N, M = len(matrix), len(matrix[0])
    maxsize = 0
    for x in range(N):
        for y in range(M):
            if not matrix[x][y]: continue
            if not x or not y: continue
            l = min([matrix[x-1][y], matrix[x][y-1], matrix[x-1][y-1]])
            matrix[x][y] = l+1
            maxsize = max(maxsize, matrix[x][y])
    return maxsize

