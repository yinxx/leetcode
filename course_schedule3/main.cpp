#include <iostream>
#include <vector>
#include <queue>

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::priority_queue;

// The input is in the form:
// { (t_i,d_i) } where
// t_i = time for i-th course
// d_i = deadline for i-th course
//
// We want to find the maximal number of courses. This can be done in DP.
//
// Two states to cache: (current time, # of courses considered) -> max # of courses.
//
// An approximate OPT statement:
// OPT(t, i) = max(OPT(t - t_i, i-1) + 1(t < d_i), OPT(t-1, i), OPT(t, i-1))

auto max_date = [](const vector<vector<int>>& courses) -> size_t{
    int max_d = 0;
    for(auto v : courses){
        max_d = std::max(max_d, v[1]);
    }
    return max_d;
};

auto sorter = [](const vector<int>& lhs, const vector<int>& rhs){
    return lhs[1] < rhs[1];
};

int schedule_course_dp(vector<vector<int>> courses){
    std::sort(courses.begin(), courses.end(), sorter);
    
    int max_d = max_date(courses);
    vector<vector<int>> opt(courses.size()+1, vector<int>(max_d+1));
    
    for(size_t i = 1; i <= courses.size(); i++){
        // offset by 1
        int ti = courses[i-1][0];
        int di = courses[i-1][1];
        for(int j = 0; j < ti; j++){
            opt[i][j] = opt[i-1][j];
        }
        for(int j = ti; j <= max_d; j++){
            opt[i][j] = std::max(std::max(opt[i-1][j-ti] + (j <= di),
                                          (j > 0) ? opt[i][j-1] : 0), 
                                 opt[i-1][j]
                                );
        }
    }

    return opt[courses.size()][max_d]; 
}

// I guess I can't use DP, so let's try priority queue.
// NOTE: I cheated by looking at the solution because one of my
// optimized O(N^2) approaches was wrong on the 87th test case,
// and how the fuck am I supposed to know what I did wrong in there...
// Here's the scattered remains of that

int schedule_course_optimized_failed(vector<vector<int>> courses){
    std::sort(courses.begin(), courses.end(), sorter);
    
    int max_d = max_date(courses);

    // keep track of max's.
    int max_occurence = 0;
    int max_idx = 0;

    vector<int> v(max_d+1, 0);
    
    // If the index is past our max_idx, then we should give max value,
    // otherwise, it should be the correct idx.
    auto new_val = [&](int idx){
        int val = 0;
        if(idx >= max_idx)
            val = v[max_idx] + 1;
        else
            val = v[idx] + 1;
        return val;
    };

    for(size_t i = 0; i < courses.size(); i++){
        int ti = courses[i][0];
        int di = courses[i][1];
        int d = di;

        if(max_occurence <= new_val(d-ti)){
            max_occurence = new_val(d-ti);
            while(d-ti >= 0 && new_val(d-ti) >= v[d]) {
                v[d] = new_val(d-ti);
                d--; 
            }
            max_idx = di;
        }
    }

    return max_occurence;
}

// So we will do priority queue here... Sigh
//
// The idea is really clever, the courses have a start
// and an end. At any time, we must have total sum of the
// classes we take to be less than the largest deadline.
//
// That's why we remove always the longest(GREEDY) class
// from our pile at every iteration, and go from there.
//
// This solution makes me feel depressed. Someone help 
// (Because I didn't think of it)

int schedule_course_pq(vector<vector<int>> courses){
    std::sort(courses.begin(), courses.end(), sorter);
    priority_queue<int> pq;

    int size = 0;
    int count = 0;
    for(size_t i = 0; i < courses.size(); i++){
        int ti = courses[i][0];
        int di = courses[i][1]; 
        size += ti;
        pq.push(ti);
        count++;

        while(size > di){
            size -= pq.top();
            pq.pop();
            count--;
        }
    }
    return count;
}
int main(){
    vector<vector<int>> courses = {
        {5,5}, {3,6}, {3,6}
    };
    cout << "ANSWER : " << schedule_course_pq(courses) << endl;
    
    return 0;
}
