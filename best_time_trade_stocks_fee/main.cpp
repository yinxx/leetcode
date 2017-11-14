#include <iostream>
#include <vector>
using std::vector;

// The algorithm is:
// OPT(n) = max(OPT(k) + {p_n - p_k+1 - fee}, 0)
int max_profit(vector<int>& prices, int fee){
    vector<int> dp(prices.size()+1);
    for(size_t i = 1; i < dp.size(); i++){
        int price = prices[i-1];
        std::cout << price << std::endl;
        int max_val = 0;
        for(size_t k = 0; k < i; k++){
            max_val = std::max(max_val, dp[k] + std::max(0, (price - prices[k] - fee)));
        }
        dp[i] = max_val;
    }    
    return dp[prices.size()];
}

int main(){
    vector<int> v = {1, 3, 2, 8, 4, 9};
    std::cout << max_profit(v, 2);
    return 0;
}
