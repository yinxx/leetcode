#include <iostream>
#include <vector>

// Algorithm:
//
// This one is also a pain in the ass. Here's a general guideline:
//
// OPT(i,...,j) = min_k |OPT(i,...,k) + OPT(k,...,j)|, or if entire string is a subsequence pattern.
// OPT(i,i) = s[i], and |s[i]| = 1 always.
//
// find_substring does the following:
// given S, constructed from characters or expressions c_1, ... , c_n, we will append to make:
// c_2, c_3, ... , c_n, c_1, ... , c_n-1
//
// Which is (S+S)[1:-1], or T[1:-1].
// T[1:-1]
// 
// Lemma: If we find S inside of T[1:-1], then S repeats.
// Proof:
// Suppose we have the previous expression:
// T[1:-1] = c_2, c_3, ... , c_n, c_1, ... , c_n-1 = x_1, x_2, ..., x_n-2
//
// We see that if S is inside of T[1:-1], then c_1 must exist somewhere(before the actual c_1).
// If c_1 exists, then c_1 = x_i where i < n (since c_1 = x_n).
// If c_1 = x_i = c_j, and c_2 = c_j+1, ...
//
// Now, if we can incrementally rotate around the ring(and recover to the same spot), then we can say that there are
// repeating substrings inside of S, since every N/period length sub-strings are equal to each other.

using std::vector;
typedef std::string str;

str find_substring(str s){
    int N = s.size();
    int idx = (s+s).find(s, 1);
    if(idx == N)
        return s;
    int period = idx;
    int freq = N / period;
    str compressed = std::to_string(freq) + "[" + s.substr(0, period) + "]";
    return (compressed.size() < s.size()) ? compressed : s;
}

str encode(str s){
    vector<vector<str>> dp(s.size(), vector<str>(s.size()));
    for(size_t len = 1; len <= dp.size(); len++){
        for(size_t i = 0; i <= dp.size() - len; i++){
            size_t end = i+len-1;
            dp[i][end] = find_substring(s.substr(i, len));
            for(size_t j = i; j < end; j++){
                str append_substring = find_substring(dp[i][j] + dp[j+1][end]);
                if(append_substring.size() < dp[i][end].size())
                    dp[i][end] = append_substring;
            }
        }
    }
    return dp[0][s.size()-1]; 
}

int main(){
    str s("abbbabbbcabbbabbbc");
    std::cout << "ANSWER OF " << s << " : " << encode(s) << std::endl;
}
