#include <iostream>
#include <vector>
#include <cmath>
using std::cout;
using std::endl;
using std::vector;

int brute_force(int n){
    if(n == 0)
        return 0;
    vector<bool> bulbs(n, true);
    for(int i = 2; i <= n; i++){ // i for multiples
        for(int j = i-1; j < n; j+=i){ // j for i*j idx
            bulbs[j] = ~bulbs[j]; 
        }
    }

    int count = 0;
    for(bool b : bulbs){
        count += b;
    }

    return count;
}

// I hate these puzzles. I realized this after I wrote the brute force:
// I actually discussed this with someone already and came up with this
// solution.
//
// For any number x between 0 and n, a lightbulb will be on if it has odd
// factors.
//
// However, think about that; Say 4: (1,4), (2,2), (4,1). Any number will have
// factors (f_i, f_j) and (f_j, f_i), except (f_j,f_j), which means it's a square.
// Therefore, it can only be on if it's a square.
//
// Any # of squares that are smaller than our current number will be on.

int smart(int n){
    return std::sqrt(n);
}

int main(){
    cout << "ANSWER : " << smart(2) << endl;
}
