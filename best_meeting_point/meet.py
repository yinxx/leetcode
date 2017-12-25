"""
We are given a map m, and 1's mark houses.

This problem could be done by finding the median, since that's the expected value of
manhattan distance.

Finding the median is pretty simple:
Minimize the following equation:
    min \sum_i |x_i - x|, where x is the median.
    We solve this by sweeping and finding x.

In a 1-dimensional setting, we have [1,0,0,1,0,1] -> [8, 7, 6, 5, 6, 7]
The minimum can be solved by taking the derivative.

We can start at the center of the grid, and then use partial derivatives to find the solution.
"""
import bisect

def meet(m):
    N,M = len(m), len(m[0])
    houses = [(i,j) for i in range(N) for j in range(M) if m[i][j]]
    # Find the bisect point:    
    hx = sorted([x[0] for x in houses])
    hy = sorted([x[1] for x in houses])
    med = lambda hx : (hx[len(hx)//2-1] + hx[len(hx)//2]) // 2 if not len(hx)%2 else hx[len(hx)//2]
    mx, my = med(hx), med(hy)
    dist = 0
    for h in houses:
        dist += abs(h[0]-mx) + abs(h[1]-my)
    return dist

print(meet([[1,0,0,0,1],[0,0,0,0,0],[0,0,1,0,0]]))
