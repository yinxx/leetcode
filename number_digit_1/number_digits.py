"""
Given an integer n, count # of 1's appearing.

Trickier than it sounds:

Define f(n) = Max # of 1's with n radices or less.

g(n, m) = Max # of 1's with n radices up to m as the n-th radix.

h(x) returns the solution.
"""
from math import log10
def f(n):
    if n < 0: return 0
    if n == 0: return 1
    return f(n-1) * 10 + 10**n

def g(n, m):
    a = f(n-1) * m
    if m > 1:
        a += 10**n
    return a

def h(x):
    if x <= 0: return 0

    c = x
    total = 0
    curmult = 1
    radixnum = 0
    while x:
        xi = x % 10
        if not xi: pass
        elif xi == 1:
            total += (c-(c//curmult*curmult)+1) + f(radixnum - 1)
        else:
            total += g(radixnum, xi)
        x //= 10
        curmult *= 10
        radixnum += 1
    return total

print(h(-1))
