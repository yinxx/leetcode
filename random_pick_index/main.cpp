#include <iostream>
#include <vector>
#include <cstdlib>
using std::vector;

class Pick{
public:
    Pick(vector<int>);
    int pick(int);
private:
    vector<int> nums;
};

Pick::Pick(vector<int> _nums) : nums(_nums) {}

// Resevoir sampling
// At each iteration, you assign the probability of the new element to be 1/N,
// and the rest of the elements to be {N-1}/N.
// That way, you have each element has probability:
//
// 1/1 * 1/2 * 2/3 * 3/4 * 4/5 ... = 1/N
int Pick::pick(int target){
    // To achieve randomness, need to uniformly sample from 0,...,N - 1
    // where |V| = N.
    auto random = [](int num){ 
        return rand() % num;
    };
    int total = 0, cur = -1;
    for(size_t i = 0; i < nums.size(); i++){
        if(nums[i] == target){
            total++;
            if(random(total) == 0)
                cur = i;
        }
    }
    return cur;
}



int main(){
    const int TRIALS = 100;
    vector<int> nums = {1,2,3,3,3};
    Pick picker(nums);
    for(size_t i = 0; i < TRIALS; i++){
        std::cout << picker.pick(3) << std::endl;
    }
}
