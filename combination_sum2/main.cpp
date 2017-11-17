#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

void addSum(const vector<int>& nums, int idx, int cursum, vector<int>& cur, vector<vector<int>>& sol, int target){
    if(cursum == target){
        sol.push_back(cur);
        return;
    } 
    if(idx == (int)nums.size() || nums[idx] > target)
        return;
    int endidx = idx;
    while(endidx < (int)nums.size() && nums[endidx] == nums[idx]) endidx++;
    // endidx will be either the end of the array OR the element after this duplicate element.
    int num_added = 0;
    addSum(nums, endidx, cursum, cur, sol, target);
    do{
        cursum += nums[idx];
        if(cursum > target) break;
        cur.push_back(nums[idx]);
        addSum(nums, endidx, cursum, cur, sol, target);
        num_added++;
        idx++;
    } while(idx < (int)nums.size() && nums[idx] == nums[idx-1]);

    while(num_added--)
        cur.pop_back();
}

vector<vector<int>> comsum(vector<int> nums, int target){
    vector<vector<int>> ans;
    std::sort(nums.begin(), nums.end());
    vector<int> v;
    addSum(nums, 0, 0, v, ans, target);
    return ans;
}

int main(){
    auto ans = comsum({2, 4}, 10);
    for(auto v : ans){
        for(int i : v){
            cout << i << " ";
        }
        cout << endl;
    }
    return 0;
}
