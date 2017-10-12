#include <iostream>
#include <vector>
using std::vector;

// Algorithm: Knapsack
//
// OPT(i,j) = i-th value, j-th candidate.
// 
// OPT(i,v_i*k) = OPT(i-1, v_i*(k-1)) + 1
// OPT(i,j) = OPT(i-1, j-v_i)

vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<vector<int>>> dp(candidates.size(), vector<int>(target+1)); 
    std::sort(candidates.begin(), candidates.end());
    for(int i = 0; i < candidates.size(); i++){
        int candidate = candidates[i];
        dp[candidate].push_back({candidate});
        for(int j = candidate+1; i <= target; i++){
            for(vector<int> v : dp[j-candidate]){
                v.push_back(candidate);
                dp[j].push_back(v);
            }
        }
    }
    return dp[target];
}

int main(){

}
