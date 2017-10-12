#include <iostream>
#include <vector>

// Algorithm:
//
// dp[i] = (dp[i-2] + char-able(dp[i-1, i])) + (dp[i-1] + 1)

typedef std::string str;
using std::vector;

bool charable(const std::string& num){
    if(num[0] == '0' && num.size() > 1)
        return false;
    int x = atoi(num.c_str());
    std::cout << "Num : " << x << std::endl;
    if(x >= 1 && x <= 26){
        return true;
    }
    return false;
}

int num_decoding(str s){
    if(s.size() == 0)
        return 0;
    vector<int> v(s.size());
    if(s[0] == '0')
        return 0;
    v[0] = 1; 
    for(size_t i=1; i < s.size(); i++){
        if(charable(s.substr(i-1,2)))
            v[i] += (int(i)-2 < 0) ? 1 : v[i-2];
        if(s[i] != '0')
            v[i] += v[i-1];
    }

    return v[s.size()-1];
}

int main(){
    str s("101");
    std::cout << "ANSWER : " << num_decoding(s) << std::endl;
}
