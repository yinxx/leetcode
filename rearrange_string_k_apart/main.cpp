#include <iostream>
#include <vector>
#include <queue>
#include <map>
// Algorithm:
// 1. Sort letters by their frequency in the word.
// 2. In the previous string, S = [s1,s2,...,sn], we will interleave 
//     m(the frequency) of the i-th letters(c_i) so it looks like:
//     [s1,...,s_i, c_i, ..., s_2i, c_i, ..., s_3i, ..., c_i...].
//     The i-th letter will be at most i apart from each other.
//
// Proof for why it works:
//
// We want to maximize the distance from each letter.
//
// We denote l1,...,ln for letters, and s1,...,sn for their frequencies. s1 >= s2 ... >= sn.
//
// Lemma 1: l1 can only have max distance (s2...+sn)/(s1-1).
// Proof: For s1 letters, we have s1-1 gaps.
// For example, s1 = 3, l1 = a gives: a _ a _ a. There are (s1-1) gaps.
// It is trivially true that we need to uniformly distribute between these gaps, so we have
// floor((s2+...+sn)/(s1-1)) max.
//
// Because of Lemma 1, we need all letters to satisfy the max distance requirement. 
// If they do, then we have a valid string. 
// Otherwise, k is not a valid number so we have to return "".
//
// Lemma 2: To allow all letters li, i > 1, to satisfy the max distance requirement, 
// we will put 1 letter into each string slot. Each li's distance to its initial l1 in the period will be a fixed distance every time.
// Proof: Because we have a fixed distance for each li, we will yield the same guarrantee as lemma 1. 
// We will be able to satisfy this requirement inductively, but the rest of the proof is fairly straight forward.

using std::vector;
using std::priority_queue;
using std::map;
typedef std::string str;
typedef std::pair<char, int> letter;

static const int NUM_ALPHA = 26;
str rearrange_string(str s, int k){
    if(k <= 1)
        return s;
    if(s.empty()) return {};
    // PREPROCESSING
    // We want in decreasing order.
    auto cmp = [&](const letter& lhs, const letter& rhs){
        return lhs.second < rhs.second;
    };
    
    map<char, int> m;
    for(size_t i = 0; i < s.size(); i++)
        m[s[i]]++;
    priority_queue<letter, vector<letter>, decltype(cmp)> pq(cmp); 
    for(auto p : m)
        pq.push(p);

    vector<letter> leftover;
    str ans;
    while(!pq.empty()){
        leftover.clear();
        for(int i = 0; i < k; i++){
            if(pq.empty()) return {};
            auto p = pq.top(); 
            ans += p.first;
            // std::cout << p.first << " : " << p.second << std::endl;
            if(ans.size() == s.size()) return ans;
            pq.pop();
            leftover.emplace_back(p.first, p.second-1);
        }
        for(letter l : leftover){
            if(l.second > 0) pq.push(l);
        }
    }
    return ans;
}

int main(){
    std::cout << rearrange_string("aaabc", 3); 
}
