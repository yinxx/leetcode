"""
This question is **really** annoying.

We have to take care of the 4 sides. We only need:
    x[n-3], x[n-2], x[n-1] and x[n] to decide whether there is an intersection.

All 4 cases can be generalized as:
    x[n] intersects with x[n-3]: x[n] >= x[n-2], x[n-1] <= x[n-3]

However, for examples like [1,1,2,2,1,1], our plan fails because we intersect the beginning with the end.
    There is a long term dependency that we need to capture.

We actually have 2 more cases:
    x[n] intersects with x[n-5]: x[n] <= x[n-2], x[n-1] <= x[n-3], x[n-1] + x[n-5] >= x[n-3]

"""
from collections import deque
def cross(paths):
    if len(paths) < 4: return False
    d = deque()
    for i in range(3):
        d.append(paths[i])
    for path in paths[3:]:
        d.append(path)
        if d[-1] >= d[-3] and d[-2] <= d[-4]:
            print("direct collision")
            return True
        if len(d) >= 5:
            if d[-2] == d[-4] and d[-1] + d[-5] >= d[-3] and d[-3] >= d[-5]:
                print("len 5 collision")
                return True
        if len(d) >= 6:
            if (d[-4]-d[-6]) <= d[-2] <= d[-4] and d[-1] + d[-5] >= d[-3] and d[-3] >= d[-5]:
                print("len 6 collision")
                return True
        if len(d) > 6:
            d.popleft()
    return False
       

print(cross([1,1,2,2,3,3,4,4,10,4,4,3,3,2,2,1,1]))
