#include <iostream>
#include <vector>
#include <unordered_set>
using std::unordered_set;
using std::vector;
typedef std::string str;

// A word's anagram is a palindrome iff all of its letters have occurences of 2*k except for maybe 1.
// 
// S = [ c * n | occurence of c is n*2 ]
// 
// We now need to perform a permutation on S:
// permute(S, idx):
//     container.insert(consume(S))
//     for(int i = idx+1; i < |S|; i++){
//         if(S[idx] == S[i])
//             continue
//         swap(S[idx], S[i])
//         permute(S, idx+1)
//         swap(S[idx], S[i])
//     }

// auto print_list = [](vector<char>& v, int idx, int i){
    // std::cout << "Swapping " << idx << " with " << i << std::endl;
    // for(char c : v){
        // std::cout << c << " ";
    // }
    // std::cout << std::endl << "-------" << std::endl;
// };

void permute(vector<char>& S, int idx, unordered_set<str>& container, str root){
    using std::swap;
    auto consume = [&container](vector<char>& S, str root){
        for(char c : S){
            root = c + root + c;
        }
        container.insert(root);
    };
    if(idx >= int(S.size())-1){
        consume(S, root);
        return;
    }
    
    permute(S, idx+1, container, root);
    for(size_t i = idx+1; i < S.size(); i++){
        if(S[idx] == S[i])
            continue;
        swap(S[idx], S[i]);
        permute(S, idx+1, container, root);
        swap(S[idx], S[i]);
    }
}

vector<str> generate_palindromes(str s){
    vector<int> count(1<<8);
    vector<char> S;
    unordered_set<str> ans;
    str optional("");
    for(char c : s){
        count[c]++;
    }
    for(size_t i = 0; i < count.size(); i++){
        int freq = count[i];
        if(freq % 2 == 1){
            if(!optional.empty())
                return {}; // We can't have 2 letters w/ single frequency.
            else
                optional += char(i);
        }
        for(int j = 0; j < freq/2; j++){
            S.push_back(i);
        }
    }
    permute(S, 0, ans, optional);
    std::vector<str> res;
    std::copy(ans.begin(), ans.end(), std::back_inserter(res));
    return res; 
}

int main(){
    vector<str> ans = generate_palindromes("aabbcc");
    for(str s : ans)
        std::cout << s << std::endl;
    return 0;
}
