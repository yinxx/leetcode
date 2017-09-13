#include <iostream>
#include <vector>
using std::vector;
// Returns # of times a subsequence of s equals t.
// Algorithm:
// OPT(i,j) denotes the # of subsequences of s[:i] == t[:j].
// if there were x matches of i subsequence of t string, then

int num_distinct(std::string s, std::string t){
    vector<vector<int> > opt(t.size()+1, vector<int>(s.size()+1));
    for(size_t i = 0; i <= s.size(); i++){
        opt[0][i] = 1; 
    } 
    
    auto f = [&](int ti, int si) -> int{
        if(s[si-1] == t[ti-1]){
            return opt[ti-1][si-1];
        }
        else
            return 0;
    };

    for(size_t i = 1; i <= t.size(); i++){
        for(size_t j = 1; j <= s.size(); j++){
            opt[i][j] = opt[i][j-1] + f(i,j);
        }
    }

    return opt[t.size()][s.size()];
}

int main(){
    std::cout << "ANSWER : " << num_distinct("aabccbcc", "abc") << std::endl;
}
