#include <iostream>
#include <vector>
using std::vector;

// This smells of DP:
// OPT(i,j) = min_k{OPT(i-1, k) where k != j} + c_ij
//
// We can even do this in place!
// However, this takes O(NK^2) time.

int min_cost(vector<vector<int>>& opt){
    if(opt.size() == 0)
        return 0;
    for(int i = 1; i < opt.size(); i++){
        for(size_t j = 0; j < opt[i].size(); j++){
            int c_ij = opt[i][j];
            int cur_best = (1 << 31) - 1;
            for(size_t k = 0; k < opt[i-1].size(); k++){
                if(k == j) continue;
                cur_best = std::min(cur_best, opt[i-1][k] + c_ij);
            } 
            opt[i][j] = cur_best;
        }
    } 

    int best_score = (1 << 31) - 1;
    for(size_t i = 0; i < opt[opt.size()-1].size(); i++){
        best_score = std::min(best_score, opt[opt.size()-1][i]); 
    }
    return best_score;
}

int main(){
    vector<vector<int>> in = {{1,2,3}};
    std::cout << "ANSWER : " << min_cost(in) << std::endl;
    return 0;
}
