#include <iostream>
#include <vector>

using std::vector;

int change(int amount, vector<int> coins){
    std::sort(coins.begin(), coins.end(), std::greater<int>());
    vector<int> dp(amount+1, 0);
    dp[0] = 1;
    for(int coin : coins){
        for(int i = 1; i <= amount; i++){
            dp[i] += (i-coin >= 0) ? dp[i-coin] : 0;
        }
    }
    return dp[amount];
}

int main(){
    std::cout << "ANSWER : " << change(5, {1,2,5}) << std::endl;
}
