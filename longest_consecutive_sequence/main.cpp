#include <iostream>
#include <vector>
#include <unordered_map>
using std::vector;
using std::unordered_map;
// Algorithm:
// Since unordered_map lookup and insert is O(1), we can
// achieve O(N) by the following:
//
// Create a pair mapping of index. Denote -1 for invalid.

int longest_consecutive(vector<int> nums){
    // Pair syntax: index : {num-1 index, num+1 index}
    unordered_map<int, std::pair<int, std::pair<int, int>> > m;
    if(nums.size() == 0)
        return 0;
    int longest = 1;

    auto get_length = [&m, &nums](int idx) -> int{
        int count = 1;
        // Assumes nums[idx] is already a member of m
        // (Which it should be)
        while(m[nums[idx]].second.second != -1){
            idx = m[nums[idx]].second.second;
            count++;
        }
        return count;
    };
    
    for(size_t i = 0; i < nums.size(); i++){
        int num = nums[i];
        
        // new initialization
        if(m.find(num) == m.end())
            m[num].second = {-1, -1};

        m[num].first = i;
        if(m.find(num-1) != m.end()){
            m[num].second.first = m[num-1].first;
            m[num-1].second.second = m[num].first;
        }
        if(m.find(num+1) != m.end()){
            m[num].second.second = m[num+1].first;
            m[num+1].second.first = m[num].first;
        }
    } 

    for(auto p : m){
        auto link = p.second;
        // Found a tail. start recursing
        if(link.second.first == -1 && link.second.second != -1){
            longest = std::max(longest, get_length(link.first));
        }
    }

    return longest;
}

int main(){
    std::cout << "ANSWER : " << longest_consecutive( { 4,6,9,5,2,7,8,3,10,15,16,17,12,19,20 } ) << std::endl;
}
