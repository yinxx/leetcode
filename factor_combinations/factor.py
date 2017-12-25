"""
A factor of x, y, must divide x. We can a DP table that caches what factors of x produces y.

We can create a table of size sqrt(N),

and find factors in increasing order:

    F(i) |= F(x) * F(y) such that x and y are factors of F(i).

It takes O(sqrtN) for each number, and we do this sqrtN number of times, so it takes O(N).
"""
import numpy as np
def product(l1, l2):
    """
    We have 2 lists, l1, l2 that contain lists of factors.
    We want to take any arbitrary f1 in l1 and any arbitrary f2 in l2 and
    create a result combination:
    """
    res = []
    for f1 in l1:
        for f2 in l2:
            res.append(f1+f2)
    return res

def gcd(a, b):
    """
    a = qb + y
    """
    if a < b:
        gcd(b, a)
    if a % b == 0:
        return b
    return gcd(b, a%b)

def findfactors(n, f):
    """
        If there exists x, y such that x*y = n,
        then add {x,y} into the set, as well as {factors(x) * y}, and {factors(y) * x}.
        However, the caveat is if x divides y, then don't do {factors(x) * y}, as we will
        result in duplicates.
    """
    sqrt = lambda x : int(x**(0.5))
    # Here, we guarrantee y >= x.
    for x in range(2,sqrt(n)+1): # Include sqrts
        if not (n%x): # is a factor
            y = n // x
            f[n].append((x,y))
            if gcd(x,y) != 1 and x != y:
                f[n] += product(f[y], [(x,)])
            f[n] += product(f[x], [(y,)])
            f[n] += product(f[y], f[x])

def factors(n):
    # Empty lists.
    f = [[] for _ in range(n+1)]
    for i in range(2,n+1):
        findfactors(i, f)
    return f

print(np.array(factors(24)))
#  print(gcd(8, 14))
