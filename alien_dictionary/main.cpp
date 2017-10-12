#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
typedef std::string str;

static const int NUM_LETTERS = 26;

// Algorithm:
// 
// Create a graph G where for each string we have comparison of the first letter that's not the same.
// If a string is "w" and then "cab", then w->c.
// 
// We will represent the above with a map<char, vector<char>> m,
//    where v[c] = set of characters c is bigger than.
// 
// The algorithm will be a topological sorting, i.e.:
// vector<int> counts (|m.keys()|) (initialize it with the # of incoming edges)
// queue<char> q <-- takes in the characters that drop to 0 count.
// while !q.empty:
//     c = q.front
//     ordering += c
//     for all c's outgoing edges, decrement count
//         if count is 0:
//             put into q
// 
// if counts not all 0, then return false(loop)
// else return ordering

str alien_order(vector<str>& words){
    auto find_noncommon = [](const str& lhs, const str& rhs) -> int{
        if(lhs == rhs)
            return 0;
        for(size_t i = 0; i < std::min(lhs.size(), rhs.size()); i++){
            if(lhs[i] != rhs[i])
                return i;
        }
        return std::min(lhs.size(), rhs.size());
    }; 

    vector<vector<int>> m(NUM_LETTERS); 
    // -1 means never saw a letter of such kind.
    // 0 means saw it, but it is a tail.
    // > 0 means saw it, and something is less than it.
    vector<int> count(NUM_LETTERS, -1);
    // We want to compare each string with the next string and find out a relationship.
    
    for(size_t i = 0; i < words.size()-1; i++){
        const str& cur = words[i];
        const str& next = words[i+1]; 
        int idx = find_noncommon(cur, next);
        int next_c = next[idx] - 'a';
        if(idx >= cur.size()){
            count[next_c] = std::max(count[next_c], 0);
            continue;
        }
        int cur_c = cur[idx] - 'a';
        count[cur_c] = std::max(count[cur_c], 0);
        if(next != cur){
            m[cur_c].push_back(next_c); 
            count[next_c] = std::max(count[next_c], 0) + 1;
        }
    } 
  
    queue<int> q;
    
    for(size_t i = 0; i < count.size(); i++){
        if(!count[i])
            q.push(i);
    }  
    
    str ans("");

    while(!q.empty()){
        int c = q.front();
        q.pop();
        ans += char(c+'a');

        for(int child : m[c]){
            count[child]--;
            if(!count[child])
                q.push(child);
        }
    }

    for(int freq : count)
        if(freq > 0)
            return "";

    return ans;
}

int main(){
    vector<str> v = {
        "z",
        "za"
    };
    std::cout << "ANSWER : " << alien_order(v) << std::endl;
}
