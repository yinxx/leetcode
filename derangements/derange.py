import numpy as np
def derange(nums):
    ans = []
    N = len(nums)
    def helper(idx, cur):
        if idx == N-1:
            ans.append(cur.copy()) 
        for i in range(idx, N):
            if cur[i] == cur[idx] or cur[idx] == nums[i] or cur[idx] == nums[i]: continue
            cur[idx],cur[i] = cur[i],cur[idx]
            helper(idx+1, cur)
            cur[idx],cur[i] = cur[i],cur[idx]
    helper(0, nums.copy())
    return ans


if __name__ == "__main__":
    print(np.array(derange([1,2,3,4])))
