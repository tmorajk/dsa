#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& G) {
        int startRow, startCol, cellsToVisit = 0;
        for(int i = 0; i < size(G); i++)
            for(int j = 0; j < size(G[0]); j++) 
                if(G[i][j] == 1) startRow = i, startCol = j;
                else if(G[i][j] != -1) cellsToVisit++;
        int ans = 0;
        dfs(G, startRow, startCol, cellsToVisit, ans);
        return ans;
    }
private:
    int dir[5] {0, 1, 0, -1, 0};  // <- a common way to make 4-way exploration in dfs concise
    
    // checks if cell is valid. If none of 3 points mentioned in post is satisfied, it is a valid cell
    bool isValidCell(vector<vector<int>>& G, int i, int j) {
        return i >= 0 && j >= 0 && i < size(G) && j < size(G[0]) && G[i][j] != -1 && G[i][j] != 3;
    }
    
    void dfs(vector<vector<int>>& G, int i, int j, int cellsToVisit, int &ans) {
        if(not isValidCell(G, i, j)) return;   // return if cell is invalid
        if(G[i][j] == 2) {                     // reached end cell
            if(cellsToVisit == 0) ans++;       // if all cells are visited, increment valid path count
            return;                            // no further exploration possible after reaching end cell
        }
        G[i][j] = 3;                           // mark cell as visited
        for(int k = 0; k < 4; k++)             // explore path futher 4-directionally
            dfs(G, i + dir[k], j + dir[k+1], cellsToVisit - 1, ans);    
        G[i][j] = 0;                           // backtrack
    }        
};

int main()
{
    Solution s;
    vector<vector<int>> A = {{1, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 2, -1}};
    // vector<vector<int>> A = {{0,1}, {2,0}};
    int ans = s.uniquePathsIII(A);
    printf("%d\n", ans);
    return 0;
}