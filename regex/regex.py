"""
1, If p.charAt(j) == s.charAt(i) :  dp[i][j] = dp[i-1][j-1];
2, If p.charAt(j) == '.' : dp[i][j] = dp[i-1][j-1];
3, If p.charAt(j) == '*': 
   here are two sub conditions:
               1   if p.charAt(j-1) != s.charAt(i) : dp[i][j] = dp[i][j-2]  //in this case, a* only counts as empty
               2   if p.charAt(i-1) == s.charAt(i) or p.charAt(i-1) == '.':
                              dp[i][j] = dp[i-1][j]    //in this case, a* counts as multiple a 
                           or dp[i][j] = dp[i][j-1]   // in this case, a* counts as single a
                           or dp[i][j] = dp[i][j-2]   // in this case, a* counts as empty
"""


"""
The core idea is to define a recurrence relation:

if S[:i] is correctly represented by regex R[:j], then that means S[:i+1] has a couple cases:
    1. R[j] = *, and S[i+1] = S[i], then we can match without advancing i: OPT(i,j) = OPT(i-1, j) if *. And we can do this for the entire i sequence until S[i+1] != S[i]
    1.5. Also, if R[j] = *, and OPT(i-1, j-1) was False, then we can validate it by OPT(i-1, j) = True. We do this BEFORE (1) executes.
    2. R[j+1] = ., then we can match any of S[i+1]: OPT(i,j) = OPT(i-1, j-1) if .
    3. R[j+1] = some character c, and S[i+1] = same c: OPT(i,j) = OPT(i-1, j-1)

Big comment about *:

There are 3 things a * can do:
Take away the current character. Then OPT(i-1, j-2) means previous character, without the *c. We want OPT(i-1, j) = OPT(i-1, j-2).
Keep the current character. Then OPT(i, j) = OPT(i, j-1).
Add any more characters that can match: Then OPT(i+k, j) = OPT(i+k-1, j), as long as s[i+k] == c
"""
import numpy as np
def regex(s, p):
    N, M = len(s), len(p)
    # We will also have a cell for empty strings, hence +1
    dp = [[False]*(M+1) for _ in range(N+1)]

    # Base case: dp[0][0] is true for sure.
    dp[0][0] = True
    for i in range(0,N+1):
        for j in range(1,M+1):
            # (1)
            if p[j-1] == '*':
                dp[i][j] = dp[i][j-2]
                if i == 0: continue

                k = 0
                while i+k-1 < N and (s[i+k-1] == p[j-2] or p[j-2] == '.'):
                    # We want to set this to true, but it can only be true if
                    # previous character also matches with previous pattern.
                    # So therefore, we need to check dp[i][j]
                    dp[i][j] = dp[i-1][j-1] or dp[i-1][j]
                    k += 1
                
            # (2)
            elif p[j-1] == '.' and i != 0:
                # Match just a single character
                dp[i][j] = dp[i-1][j-1]
            # (3)
            elif i != 0:
                if s[i-1] == p[j-1]:
                    dp[i][j] = dp[i-1][j-1]
    print(np.array(dp))
    return dp[N][M]
s = "abcd"
p = "d*"
print(s, p)
print(regex(s, p))
