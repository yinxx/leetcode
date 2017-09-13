#include <iostream>
#include <vector>
#include <queue>
#include <set>

using std::cout;
using std::endl;
using std::vector;
using std::queue;
using std::set;
using std::pair;

// This is pretty much a topological sorting problem.
// The way to tackle it is simple with an adjacency list, but with a list,
// we have to do some extra preprocessing so it becomes an adjacency list.

vector<set<int>> transform_adjacency(int num_courses, const vector<pair<int, int>>& edges){
    vector<set<int>> adj(num_courses);
    for(auto p : edges){
        adj[p.second].insert(p.first);
    }
    return adj;
}

vector<int> transform_count(int num_courses, const vector<pair<int, int>>& edges){
    vector<int> count(num_courses);
    for(auto p : edges){
        count[p.first]++;
    }
    return count;
}

vector<int> find_leaves(const vector<set<int>> adj){
    vector<bool> visited(adj.size(), true);
    vector<int> leaves;
    for(size_t i = 0; i < adj.size(); i++){
        for(int x : adj[i]){
            visited[x] = false;
        }
    }

    for(size_t i = 0; i < visited.size(); i++){
        if(visited[i])
            leaves.push_back(i);
    }
    return leaves;
}

vector<int> find_order(int num_courses, const vector<pair<int, int>>& prereqs){
    auto adj = transform_adjacency(num_courses, prereqs);
    auto count = transform_count(num_courses, prereqs);
    auto leaves = find_leaves(adj); 
    for(size_t i = 0; i < adj.size(); i++){
        count.push_back(adj.size());
    }

    // The answer in here
    vector<int> order;
    
    queue<int> q;
    for(int leaf : leaves){
        q.push(leaf);
    }

    while(!q.empty()){
        int leaf = q.front(); 
        q.pop();
        for(int neighbor : adj[leaf]){
            // remove the leaf from its neighbor's list
            count[neighbor]--; 
            // its neighbor is now also a leaf
            if(count[neighbor] == 0){
                q.push(neighbor);
            }
        }
        order.push_back(leaf);
    }

    if(order.size() != (size_t) num_courses)
       return {}; 
    return order;
}

int main(){
    auto v = find_order(7, {{0,2},{3,1},{4,3},{5,3},{6,5},{0,5},{0,1}});
    for(int x : v){
        cout << x << endl;
    }
    return 0;
}
