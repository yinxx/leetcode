#include <iostream>
#include <vector>

using std::vector;
typedef std::string str;

// The problem is pretty simple:
// 1. Turn the hours:minutes into ints.
// 2. Sort the ints.
// 3. Go through and compute deltas for each one.
    // 3.5. For times that wrap around, compute (earliest + 3600) - latest.
// 4. Return smallest delta.

static const int MAX_MINUTES = 24*60;

// Step 1
vector<int> convert_times(const vector<str>& v){
    auto convert_time = [](const str& s) -> int{
        // Assuming time is always denoted as xx:xx
        return atoi(s.substr(0, 2).c_str()) * 60 + atoi(s.substr(3,2).c_str()); 
    };
    vector<int> ans;
    for(const str& s : v)
        ans.push_back(convert_time(s)); 
    return ans;
}

int find_min_difference(vector<str>& timePoints){
    vector<int> times = convert_times(timePoints); 
    std::sort(times.begin(), times.end());
    int min_delta = (1 << 31) - 1;
    // guarranteed 2 items in the array
    for(size_t i = 1; i < times.size(); i++){
        min_delta = std::min(min_delta, times[i] - times[i-1]);
    }
    min_delta = std::min(min_delta, times[0] + MAX_MINUTES - times[times.size()-1]);
    return min_delta;
}

int main(){
    vector<str> v = {"23:59","00:00"};
    std::cout << "ANSWER : " << find_min_difference(v) << std::endl;
}
