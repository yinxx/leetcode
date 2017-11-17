"""
The main take-away from this is that we have a set of symbols s1,s2,s3,...,sn = S
where there's a comparison measure on each. We'll do some swapping.

Given some orientation: x1,x2,...,xn, we want to find the next arrangement.

We swapped the highest number @ the peak with the smallest number right after it.

3 2 3 1 4 | 5 4 3 2

3 2 3 1 4 | 2 3 4 5

Promote:
3 2 3 1 | 5 2 3 4 4

Let's try it with duplicates:

3 2 | 3 3 3 2 1

3 2 | 1 2 3 3 3

3 | 3 1 2 2 3 3
"""

def nextperm(nums):
    N = len(nums)
    peak = 0
    for i in range(1, N):
        # Then it's a peak.
        if nums[N-i] > nums[N-i-1]:
            peak = N-i
            break
    
    for i in range(0, (N-peak)//2):
        # Reflect half of array
        nums[peak+i], nums[N-i-1] = nums[N-i-1], nums[peak+i]
    
    # We are guarranteed that nums[peak] > nums[peak-1]
    if not peak:
        return nums
    
    # promote the number by swapping incrementally
    for i in range(peak, N):
        # Find the first element greater than it.
        if nums[peak-1] < nums[i]:
            nums[peak-1], nums[i] = nums[i], nums[peak-1]

    return nums

if __name__ == "__main__":
    print(nextperm([3,2,3,2,1]))




