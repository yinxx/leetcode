"""
Regex matching:

This is purely a DP problem, because OPT(i,j) = True if s[:i] can be expressed in p[:j].

We have a couple of recurrence relations here, based on p[j]:

1. p[j] is 'a-z':
    If s[i] == p[j], then OPT(i,j) = OPT(i-1,j-1).

2. p[j] is '.':
    This accepts any arbitrary pattern, so:
    OPT(i,j) = OPT(i-1,j-1).

3. p[j] is '*':
    This accepts any number of previous patterns(including 0 patterns).
    So we have 2 subcases based on p[j-1]:
    3.1: p[j-1] is 'a-z':
        We can match 0, 1, ..., N characters of p[j-1], so:
        OPT(i-1,j) = OPT(i-1, j-2) For 0 characters.
            e.x.:
                "a", "ab*" -> OPT(1,1) = True, OPT(1,2) = False, OPT(1,3) = True.
        OPT(i,j) = OPT(i, j-1) For 1 characters.
            e.x.:
                "a", "a*" -> OPT(1,1) = True, OPT(1,2) = True.
        OPT(i+k, j) = OPT(i+k-1, j) for the next k characters that are equal to s[i].
    3.2: p[j-1] is '.':
        We can match any string as long as it was previously valid:
        OPT(x, j) = True if OPT(i-1, j-1) is True.
            e.x.:
                "bbb", "a.*" -> OPT(1,x) = False, OPT(2,2) = False, OPT(3,3) = False.
"""
import numpy as np
def regex(s, p):
    s += '$'
    N, M = len(s), len(p) 
    dp = [[False] * (M+1) for _ in range(N+1)]
    dp[0][0] = True
    for i in range(1, N+1):
        for j in range(1, M+1):
            sc = s[i-1]
            pc = p[j-1]
            if pc.isalpha() and pc == sc:
                dp[i][j] |= dp[i-1][j-1] 
            elif pc == '*':
                prevc = p[j-2]
                dp[i-1][j] |= dp[i-1][j-2] # We can have 0 of pc
                if prevc == sc or prevc == '.':
                    dp[i][j] |= dp[i-1][j] # We can have 1 of pc
            elif pc == '.':
                dp[i][j] |= dp[i-1][j-1]
    print(np.array(dp))
    return dp[N-1][M]

s = "a"
p = "ab*"
print("String : ", s, " and pattern : ", p, regex(s, p))








