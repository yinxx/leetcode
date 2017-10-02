#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map>

using std::deque;
using std::unordered_map;
// The objective is to return the sum of unique elements in each window.
//
// I.e.: f([1,2,1,3,3], 3) will give
// [1 2 1] -> 1
// [2 1 3] -> 3
// [1 3 3] -> 1
// So the sum would be 5.
//
// I think a naive unordered_map<int, int> would be the easiest way.
// 
// Algorithm:
// deque d, map m
// uniq
// for (i : nums)
//     m[d.pop]--;
//     m[i]++;
//     if m[d.pop] == 1:
//         uniq++;
//     else 
//         uniq--;
//     if m[i] == 1:
//         uniq++;
//     else
//         uniq--;

int sliding_window_unique_sum(std::vector<int> nums, int k){
    deque<int> d;
    unordered_map<int, int> m;
    // returns the delta
    auto insert = [&d, &m, &k](int x) -> int{
        int delta = 0;
        d.push_back(x);
        m[x]++;
        if(m[x] == 1) delta++;
        else if(m[x] == 2) delta--;
       
        if(d.size() > size_t(k)){ 
            int popped = d.front();
            d.pop_front();
            m[popped]--;
            if(m[popped] == 1) delta++;
            else if(m[popped] == 0) delta--;
        }
        return delta;
    }; 
    int cur = 0;
    int total = 0;
    for(int i = 0; i < std::min(k, int(nums.size())); i++){
        cur += insert(nums[i]);
    }
    total += cur;
    
    for(size_t i = k; i < nums.size(); i++){
        cur += insert(nums[i]);
        total += cur;
    }
    return total;
}

int main(){
    std::cout << "ANSWER : " << 
        sliding_window_unique_sum(
            {1,2,1,3,3}, 3
        ) << std::endl;
}
