#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;
typedef pair<int, int> interval;

struct IntervalCmp{
    bool operator()(const interval& lhs, const interval& rhs){
        int l = lhs.second-lhs.first;
        int r = rhs.second-rhs.first;
        if(l == r){
            return lhs.first < rhs.first;
        }
        return l < r;
    }
};

struct StartCmp{
    bool operator()(const interval& lhs, const interval& rhs){
        return lhs.first < rhs.first;
    }
};

class Schedule{
public:
    Schedule(int N);
    void addStudent(int studentId);
    void removeStudent(int studentId);
    int largestInterval();
    void printIntervals();
private:
    unordered_map<int, int> m;
    set<interval, IntervalCmp> s;
    set<interval, StartCmp> ss;
};

Schedule::Schedule(int N){
    s.emplace(0,N);
    ss.emplace(0,N);
}

void Schedule::addStudent(int studentId){
    auto it = s.rbegin();
    int l = it->first;
    int r = it->second;
    int mid = (l+r)/2;
    s.erase(--it.base());
    ss.erase(ss.find({l, r}));
    s.emplace(l,mid);
    s.emplace(mid,r);
    ss.emplace(l,mid);
    ss.emplace(mid,r);
    m.emplace(studentId, mid);
}

void Schedule::removeStudent(int studentId){
    auto it = m.find(studentId);
    if(it == m.end())
        return;
    int mid = it->second;
    m.erase(it);
    // Find anything that's equal to it.
    auto ssit = ss.find({mid, 0}); 
    int r = ssit->second;
    int l = (--ssit)->first;
    ssit = ss.erase(ssit);
    ss.erase(ssit);
    s.erase(s.find({mid, r}));
    s.erase(s.find({l, mid}));
    ss.emplace(l, r);
    s.emplace(l, r);
}

int Schedule::largestInterval(){
    auto it = s.rbegin();
    int l = it->first;
    int r = it->second;
    return r-l;
}

void Schedule::printIntervals(){
    cout << "People:" << endl;
    for(const auto& p : m){
        cout << p.first << " : " << p.second << endl; 
    }
    cout << "Intervals:" << endl;
    for(const auto& p : ss){
        cout << "(" << p.first << ", " << p.second << ")" << endl;
    }
    cout << endl;
}

int main(){
    Schedule s(10);
    s.addStudent(0);
    s.printIntervals();
    s.addStudent(1);
    s.printIntervals();
    s.removeStudent(0);
    s.printIntervals();
    s.addStudent(2);
    s.printIntervals();
    s.addStudent(0);
    s.printIntervals();
}
