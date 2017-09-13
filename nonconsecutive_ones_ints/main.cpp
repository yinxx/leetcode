#include <iostream>
#include <vector>
#include <cmath>
/** ALGORITHM
 * There is a natural recurrence relation to this:
 * Base case: r(0) = 1, r(1) = 2
 *
 * r(i) = r(i-2) + r(i-1)
 *
 * Imperfect numbers are defined as numbers x such that 2^i < x < 2^{i+1} for some i >= 0.
 *
 * Imperfect numbers are hard to retrieve the answers of, as we need to prune iteratively:
 *
 * while residue != 0:
 *     cur_i = log_2(residue)
 *     count += r(cur_i)
 *     residue -= 2^cur_i 
 */

int find_integers(int num){
    // base cases
    if(num == 0)
        return 1;
    if(num == 1)
        return 2;
    
    // dp to handle recursion
    std::vector<int> dp(std::log2(num+1));
    dp[0] = 1;
    dp[1] = 2;
    for(int i = 2; i <= std::log2(num+1); i++){
        dp[i] = dp[i-2] + dp[i-1]; 
    }
    
    // now residue on num:
    auto trunc = [](int x) -> int{
        int radix = std::log2(x+1);
        return std::min(int(std::exp2(radix) + std::exp2(radix-1) - 1), x);
    };
    int residue = trunc(num);
    int count = 0;
    while(residue >= 0){
        int radix = std::log2(residue+1);
        count += dp[radix];
        residue -= std::exp2(radix);
        residue = trunc(residue);
    }
    return count;
}

int main(){
    std::cout << "ANSWER : " << find_integers(2525) << std::endl;
    return 0;
}
