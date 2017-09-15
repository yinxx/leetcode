#include <iostream>
#include <vector>
#include <cmath>

using std::cout;
using std::endl;
using std::vector;

// Perfect squares:
// Find minimum number of perfect squares that add up to a number n.
//
// This is classic DP smell, since if we want something like 12, then we would ask:
// "What is the least # of perfect squares to get to {8,4}, {11,1}, {12,0}, {5,7}...?"
//
// That's an O(N^2) algorithm. Let's see if we get AC:
//
// OPT(0) = 0
// if i is a perfect square: 
//      OPT(i) = 1
// else:
//      Naive: OPT(i) = min{ OPT(k) + OPT(i-k) } forall k in 0,...,floor(i/2).
//      Optimized: OPT(i) = min{ OPT(k^2) + OPT(i-k^2) } forall k in 0,...,sqrt(i).

int num_squares(int n){
    vector<int> opt(n+1);
    for(int i = 1; i <= n; i++){
        int sq = std::sqrt(i);
        if(sq*sq == i){
            opt[i] = 1;
            continue;
        }

        // The max # of num squares needed is 1+1+1+1...
        int min_val = i;
        opt[i] = min_val;

        // Very clever optimization that I didn't think of:
        // I tried looping this til i/2, but TLE.
        //
        // The idea is that you're only ever going to be adding 1 square
        // at a time to the new problem, so your old subproblems can be considered
        // "Multiple squares added", and you only need to introduce a new square
        // being added at once.
        for(int k = 0; k <= std::sqrt(i); k++){
            min_val = std::min(min_val, opt[k*k] + opt[i-k*k]); 
        }
        opt[i] = min_val;
    }
    return opt[n];
}

int main(){
    cout << "ANSWER : " << num_squares(14) << endl;
    return 0;
}
