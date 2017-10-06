#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>

using std::vector;
typedef std::pair<int, int> val_t;

class Pick{
public:
    Pick(vector<int>);
    int pick(int);
private:
    int leftmost(int l, int r, int target);
    int rightmost(int l, int r, int target);
    vector<val_t> nums;
};

Pick::Pick(vector<int> _nums) {
    auto cmp = [](const val_t& lhs, const val_t& rhs){ return lhs.first < rhs.first; };
    for(size_t i = 0; i < _nums.size(); i++){
        nums.emplace_back(_nums[i], i);
    }
    std::sort(nums.begin(), nums.end(), cmp); 
}

// For us to find the leftmost element that is x, 
// we need to express the following:
//
// f(nums,l,r,target):
//     if l == r:
//         return nums[l]
//     if nums[(l+r)/2] <= target:
//         f(nums, l, (l+r)/2)
//     else:
//         f(nums, (l+r)/2 + 1, l)

int Pick::leftmost(int l, int r, int target){
    if(l == r)
        return l;
    if(nums[(l+r)/2].first >= target)
        return leftmost(l, (l+r)/2, target);
    else
        return leftmost((l+r)/2+1, r, target);
}

int Pick::rightmost(int l, int r, int target){
    if(l == r)
        return l;
    if(nums[(l+r+1)/2].first <= target)
        return rightmost((l+r+1)/2, r, target);
    else
        return rightmost(l, (l+r)/2, target);
}

int Pick::pick(int target){
    auto random = [](int num){ 
        if(num == 0)
            return 0;
        return rand() % num;
    };
    int left = leftmost(0, nums.size()-1, target), right = rightmost(0, nums.size()-1, target);
    return nums[left + random(right-left+1)].second; 
}

int main(){
    const int TRIALS = 100;
    vector<int> nums = {1,2,2,2,3,3,3,3,3,3,5,5,5};
    Pick picker(nums);
    for(size_t i = 0; i < TRIALS; i++){
        std::cout << picker.pick(3) << std::endl;
    }
}
