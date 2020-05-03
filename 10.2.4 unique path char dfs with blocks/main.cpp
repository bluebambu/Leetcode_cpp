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

// dfs solution, dp solution

class Solution
{
public:
    vector<vector<char>> charpath(vector<string>& board){
        vector<vector<char>> result;
        int m=board.size(), n=board[0].size();
        vector<char> path;
        dfs(board, 0, 0, path, result);
        return result;
    }

    void dfs(vector<string>& board, int x, int y, vector<char>& path, vector<vector<char>>& result){


        if(x>board.size()-1 || y>board.at(0).size()-1  || board[x][y]=='+' ){
        //  board[x][y]=='+'  只能写在最后面！！！
            path.push_back('+');
            return;
        }

        path.push_back(board[x][y]);

        if(x==board.size()-1 && y==board[0].size()-1){
            result.push_back(path);
            return;
        }

        dfs(board, x+1, y, path, result);
        path.pop_back();
        dfs(board, x, y+1, path, result);
        path.pop_back();
    }




};


int main()
{
    Solution a;
    vector<string> board {
                            "1+3456789", //0
                            "0+wertyui", //1
                            "o+asdfghj", //2
                            "klzxcvbnm", //3
                         };

    auto b=a.charpath(board);
    for(auto i:b){
      for(auto j:i)
        cout<<j;
    cout<<endl;
    }
}
