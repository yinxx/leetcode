#include <iostream>
#include <vector>

using namespace std;

static const int RIGHTMOST = 1 << 7;
auto accept = [](int x) -> int{
    int ctr = 0;
    while(x){
        if((x & RIGHTMOST) == 0)
            return ctr; 
        ctr++;
        x <<= 1;
    }
    return ctr;
};
bool valid(vector<int> data){
    int to_accept = 0;
    for(int x : data){
        int cur = accept(x);
        if(cur > 4) return false;
        else if(!to_accept){
            to_accept = cur;
            if(to_accept == 1) return false;
            if(to_accept == 0) to_accept = 1;
        }
        else if(cur != 1){
            return false;
        }
        to_accept--;
    }
    return (to_accept == 0);
}

int main(){
    cout << valid({197, 130, 1}) << endl;
    return 0;
}
