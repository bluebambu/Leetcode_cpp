#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}


class Solution {
public:
    //////////// leetcode passed ///////////////////////////
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<int>> cord;
        vector<int> path;
        solve(n, 0, path, cord);

        return draw(cord);
    }

    void solve(int n, int cur, vector<int>& path, vector<vector<int>>& cord){
        if(path.size()==n){
            cord.push_back(path);
            return;
        }

        for(int i=0; i<n; ++i){
            if(valid(path, cur, i)){
                path.push_back(i);
                solve(n, cur+1, path, cord);
                path.pop_back();
            }
        }
    }

    bool valid(vector<int>& path, int cur, int j){
        if(path.empty()) return true;
        for(int i=0; i<path.size(); ++i){
            // (i, path[i]) & (cur, j)
            if(i==cur || j==path[i] || abs(i-cur)==abs(path[i]-j))
                return false;
        }

        return true;
    }

    vector<vector<string>> draw(vector<vector<int>>& cord){
        if(cord.empty())    return vector<vector<string>>(); /// necessary!!
        int m=cord.size(), n=cord[0].size();
        vector<vector<string>> board(m, vector<string>(n, string(n, '.')));

        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                board[i][j][cord[i][j]]='Q';
            }
        }

        return board;
    }
};

int main()
{
    Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1),
                                                    new TreeNode(4)),
                                    new TreeNode(8, new TreeNode(7),
                                                    new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */

    a.flatten(tree);


}
