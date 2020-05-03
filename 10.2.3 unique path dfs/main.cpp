#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <thread>

using namespace std;

inline int exchg(int &a, int &b)  {int c=a; a=b; b=c;}
inline int log2(int N){return log10(N)/log10(2);}
inline float min(float a, float b) {return a<b?a:b;}



class Solution
{
public:
    vector<vector<char>> charpath(vector<string>& board){
        int m=board.size();
        int n=board[0].size();

        vector<vector<char>> result;
        vector<char> path;
        dfs(board, m, n, 0, 0, path , result);
        cout<<path[0]<<endl;
        return result;
    }

    void dfs(vector<string>& board, int m, int n, int i, int j,vector<char>& path,  vector<vector<char>>& result){
        if(i>m-1 || j>n-1) {
            path.push_back('+');
            return;
        }
        if(i==m-1 && j==n-1){
            path.push_back(board[i][j]);
            result.push_back(path);
            return;
        }

        path.push_back(board[i][j]);
        dfs(board, m, n, i+1, j, path, result);
        path.pop_back();
        dfs(board, m, n, i, j+1, path, result);
        path.pop_back();
    }

    ///////////// use copy of Path  is quite slower than the dfs, using reference of path./////////////////
    void dfs2(vector<string>& board, int m, int n, int i, int j,vector<char> path,  vector<vector<char>>& result){
        if(i>m-1 || j>n-1) {
            return;
        }
        if(i==m-1 && j==n-1){
            path.push_back(board[i][j]);
            result.push_back(path);
            return;
        }

        path.push_back(board[i][j]);
        dfs2(board, m, n, i+1, j, path, result);
        dfs2(board, m, n, i, j+1, path, result);
    }

};

int main()
{
    Solution a;
    vector<string> board {
                            "123456789", //0
                            "0qwertyui", //1
                            "opasdfghj", //2
                            "klzxcvbnm", //3
                            };

    auto b=a.charpath(board);
    for(auto i:b){
        for(auto j:i)
            cout<<j;
        cout<<endl;
    }
}
