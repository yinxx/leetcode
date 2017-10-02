#include <iostream>
#include <vector>
#include <queue>
using std::vector;
using std::queue;

// Algorithm:
//
// We want to do a floodfill algorithm from all "sources", which are the zeros.
//
// We guarrantee the existence of a zero from assumption.
//
// 1. Scan through matrix to find all zeros. Add coordinates to queue.
// 2. For the N+1-th layer, take the previous N-th layer queue and extract neighbors.
// Do #2 until the N+1th queue is empty.

vector<vector<int>> updateMatrix(vector<vector<int>>& matrix){
    typedef std::pair<int, int> coord;
    vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[0].size(), false));

    auto mark_emplace = [&matrix, &visited](queue<coord>& next, int x, int y){
        next.emplace(x,y);
        visited[x][y] = true;
    };

    auto populate = [&matrix, &visited, &mark_emplace](queue<coord>& next, const coord& c){
        int x = c.first;
        int y = c.second;
        int xend = matrix.size();
        int yend = matrix[0].size();
        if(y+1 < yend && !visited[x][y+1])
            mark_emplace(next, x,y+1);
        if(x+1 < xend && !visited[x+1][y])
            mark_emplace(next, x+1,y);
        if(y-1 >= 0 && !visited[x][y-1])
            mark_emplace(next, x,y-1);
        if(x-1 >= 0 && !visited[x-1][y])
            mark_emplace(next, x-1,y);
    };

    queue<coord> cur; 
    queue<coord> next; 
    int cur_level = 0;

    // Initial loading
    for(size_t i = 0; i < matrix.size(); i++){
        for(size_t j = 0; j < matrix[i].size(); j++){
            if(!matrix[i][j]){ 
                mark_emplace(cur, i,j);
            }
        }
    }
    
    do{ 
        while(!cur.empty()){
            coord c = cur.front();
            cur.pop();
            matrix[c.first][c.second] = cur_level;
            populate(next, c);
        } 
        
        cur = next;
        next = queue<coord>(); // empty
        cur_level++;
    } while(!cur.empty());
}

int main(){
    vector<vector<int>> v = { {0,1,0},
                              {1,1,1},
                              {0,1,0} };
    updateMatrix(v);

    for(auto v_ : v){
        for(int x : v_){
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
