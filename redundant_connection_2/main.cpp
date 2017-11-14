#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using std::unordered_map;
using std::vector;
using std::set;

// NOTE: THIS SOL IS NOT COMPLETE. IT DOES NOT CHECK WHETHER THE EDGE IS
// THE LAST EDGE. IT FAILS THE TEST CASE 54/58.

// Algorithm:
// Use a "floodfill" algorithm. Flood it like the following:
// For every coordinate coming in c_i = (s_i, t_i)
// if s_i is "verified", and t_i is "not verified", then the edge is not legitimate.
// t_i then also becomes "verified" afterwards. We verify its children as well.
// 
// if s_i is "verified", and t_i is also "verified", then the edge is not legitimate.
// if s_i is not verified, then stop.

vector<int> find_redundant_connection(vector<vector<int>>& edges){
    // We should find the root first.
    auto find_root = [&]() -> int{
        vector<bool> source(edges.size(), true);
        int double_parent = -1;
        for(auto v : edges){
            if(!source[v[1]-1])
                double_parent = v[1];
            source[v[1]-1] = false;
        }
        for(int i = source.size()-1; i >= 0; i--){
            if(source[i]) return i+1;
        }
        return 0;
    };
    set<int> verified;
    int root = find_root();
    if(!root)
        edges.push_back({0,edges[0][0]});
    std::cout << root << std::endl;
    verified.insert(root); // the root is always verified.
    vector<bool> legitimate(edges.size(), false);
    // s -> (t, idx in edges)
    unordered_map<int, unordered_map<int, int>> g;

    std::function<void(int)> visit;
    visit = [&](int node){
        if(verified.find(node) == verified.end())
            return;
        for(auto p : g[node]){
            int t = p.first;
            int idx = p.second;
            if(verified.find(t) == verified.end()){
                legitimate[idx] = true;
                verified.insert(t);
                visit(t);
            }
        } 
    };

    for(size_t i = 0; i < edges.size(); i++){
        auto v = edges[i];
        int s = v[0], t = v[1];
        g[s].emplace(t, i);
        visit(s);
    }

    for(bool b : legitimate){
        std::cout << b << " ";
    }
    std::cout << std::endl;

    for(int i = legitimate.size()-1; i >= 0; i--){
        if(!legitimate[i])
            return edges[i];
    }
    return {};
}

int main(){
    // vector<vector<int>> v = {{4,2},{1,5},{5,2},{5,3},{2,4}};
    // vector<vector<int>> v = {{1,2}, {2,3}, {3,4}, {4,1}, {1,5}};
    // vector<vector<int>> v = {{2,1},{3,1},{4,2},{1,4}};
    // vector<vector<int>> v = {{1,2},{2,3},{3,4},{4,1},{1,5}};
    vector<vector<int>> v = {{5,2},{5,1},{3,1},{3,4},{3,5}};
    auto ans = find_redundant_connection(v);
    std::cout << ans[0] << " " << ans[1] << std::endl;
}
