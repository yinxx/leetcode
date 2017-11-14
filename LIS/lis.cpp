#include <iostream>
#include <vector>
#include <set>
using namespace std;

/**
 * The optimized LIS version is by using DP, but not on the
 * previous indices optimal answers, but rather on the
 * answer itself.
 *
 * I.e. Before we had OPT(n) = max_i{OPT(i) + 1}, nums[i] < nums[n].
 *
 * Now, we have OPT(n) = OPT(lower_bound(n)) + 1
 */

int lis(vector<int>& nums){
    set<int> dp;
    for(int n : nums){
        auto it = lower_bound(dp.begin(), dp.end(), n);
        // The first element that's greater than this number
        // can be replaced by this number.
        if(it != dp.end())
            dp.erase(it);
        dp.insert(n); 
    }
    return dp.size();
}
