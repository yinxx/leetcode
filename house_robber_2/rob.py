"""
We need 2 states here. As it is a cycle, we can have 2 optimal states:

    Case 1. We include the first house and NOT the last house.
    Case 2. We include the last house and NOT the first house.
    Case 3. We don't include either houses.

For these respective cases, we will need to shave off parts of the array:

E.x.: [1,2,5,3,2]

case 1: [5,3] + 1 = 6
case 2: [2,5] + 2 = 7
case 3: [2,5,3] = 5

The original problem is DP:

OPT(i,0) = The max value of robbing if we don't choose this house.
OPT(i,1) = The max value of robbing if we do choose this house.

OPT(i,0) = max(OPT(i-1,0), OPT(i-1,1))
OPT(i,1) = OPT(i-1,0) + vi
"""

def rob(nums):
    if len(nums) == 0: return 0
    if len(nums) == 1: return nums[0]

    def optcond(arr):
        N = len(arr)
        dp = [[0]*2 for _ in range(N+1)]
        for i in range(1,N+1):
            dp[i][0] = max(dp[i-1][0], dp[i-1][1])
            dp[i][1] = dp[i-1][0] + arr[i-1]
        return max(dp[N][0], dp[N][1])
    left = optcond(nums[2:-1]) + nums[0]
    right = optcond(nums[1:-2]) + nums[-1]
    mid = optcond(nums[1:-1])
    print(left, right, mid)

if __name__ == "__main__":
    print(rob([1,2,5,3,2]))

