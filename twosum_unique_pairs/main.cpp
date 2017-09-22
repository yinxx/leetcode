#include <iostream>
#include <vector>

int twosum_unique_pairs(std::vector<int>& nums, int target){
    if(nums.empty())
        return 0;
    int count = 0;
    std::sort(nums.begin(), nums.end());
    auto left = nums.begin();
    auto right = nums.end()-1;
    while(left < right){
        int leftv = *left;
        int rightv = *right;
        int val = *left + *right;
        if(val == target){
            while(*left == leftv && left != right) ++left;
            while(*right == rightv && left != right) --right;
            count++;
        }
        else if(val < target){
            while(*left + *right < target && left != right)
                ++left;
        }
        else{
            while(*left + *right > target && left != right)
                --right;
        }
    }
    return count;
}

int main(){
    std::vector<int> nums { 1,1,2,45,46,46 };
    std::cout << "ANSWER : " << twosum_unique_pairs(nums, 47) << std::endl;
    return 0;
}
