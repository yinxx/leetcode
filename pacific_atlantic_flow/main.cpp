#include <iostream>
#include <vector>
using std::vector;
using std::pair;
// The algorithm is pretty simple & elegant:
// We have water flow from both sides, meaning it does a floodfill of all nodes that are greater than it.
// We will set any visited node to -1, as it's an invalid, signaling visited.

// simple DFS will do.
void dfs(int i, int j, vector<vector<int>>& matrix){
    int val = matrix[i][j];
    if(val == -1)
        return;
    matrix[i][j] = -1;
    // do left, up, right, down
    auto check = [&matrix, &val](int i, int j) -> bool{
        return matrix[i][j] >= val && matrix[i][j] != -1;
    };
    if(i-1 >= 0 && check(i-1, j))
        dfs(i-1, j, matrix);
    if(j-1 >= 0 && check(i, j-1))
        dfs(i, j-1, matrix);
    if(i+1 < matrix.size() && check(i+1, j))
        dfs(i+1, j, matrix);
    if(j+1 < matrix[0].size() && check(i, j+1))
        dfs(i, j+1, matrix);
}

vector<pair<int, int>> pacific_atlantic(vector<vector<int>>& matrix){
    if(matrix.empty() || matrix[0].empty())
        return {};
    vector<vector<int>> pacific(matrix);
    vector<vector<int>> atlantic(matrix);
    // DFS on pacific side 
    for(int i = 0; i < matrix.size(); i++)
        dfs(i, 0, pacific);
    for(int j = 0; j < matrix[0].size(); j++)
        dfs(0, j, pacific);

    // DFS on the atlantic side
    for(int i = 0; i < matrix.size(); i++)
        dfs(i, matrix[0].size()-1, atlantic);
    for(int j = 0; j < matrix[0].size(); j++)
        dfs(matrix.size()-1, j, atlantic);

    vector<pair<int, int>> ans;
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[0].size(); j++){
            if(pacific[i][j] == -1 && atlantic[i][j] == -1)
               ans.emplace_back(i, j); 
        }
    }
    return ans;
}

int main(){
    vector<vector<int>> v = {
        {3,3,3},
        {3,1,3},
        {0,2,4}
    };
    auto pv = pacific_atlantic(v);
    for(auto p : pv){
        std::cout << p.first << " " << p.second << std::endl;
    }
}
