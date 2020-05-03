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


class Solution
{
public:
    //////////// leetcode passed, dfs  ///////////////////////////
    void solveSudoku(vector<vector<char>>& board) {
        vector<pair<int, int>> unfilled;

        int m=board.size();
        int n=board[0].size();

        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                if(board[i][j]=='.')
                    unfilled.push_back(make_pair(i, j));
            }
        }

        vector<vector<char>> b2;
        dfs(unfilled, 0, board, b2);
        board=b2;
    }

    void dfs(vector<pair<int, int>>& unfilled, int cur, vector<vector<char>>& board, vector<vector<char>>& b2){
        if(cur==unfilled.size()){
            b2=board;
            return;
        }else if(cur>unfilled.size())
            return;

        int x=unfilled[cur].first;
        int y=unfilled[cur].second;

        /// helper vector, record possible fillings
        vector<bool> potential(9, true);
        func(board, x, y, potential);

        for(int i=0; i<9; ++i){
            if(potential[i]){
                board[x][y]=i+1+'0';
                dfs(unfilled, cur+1, board, b2);
                board[x][y]='.';
            }
        }
    }

    void func(vector<vector<char>>& board, int x, int y, vector<bool>& potential){
        for(int j=0; j<board.size(); ++j)
            if(board[x][j]!='.')
                potential[board[x][j]-'0'-1]=false;

        for(int i=0; i<board.size(); ++i)
            if(board[i][y]!='.')
                potential[board[i][y]-'0'-1]=false;

        /// check squares
        int sqx=x/3*3;
        int sqy=y/3*3;
        for(int i=0; i<3; ++i){
            for(int j=0; j<3; ++j){
                if(board[sqx+i][sqy+j]!='.')
                    potential[board[sqx+i][sqy+j]-'0'-1]=false;
            }
        }
    }

    ///////////////////// leetcode dfs answer, more concise ///////////////////
    void solveSudoku(vector<vector<char>>& board) {
        solve(board, 0);
    }
    bool solve(vector<vector<char>>& board, int ind){
        if(ind==81) return true;
        int i=ind/9, j=ind%9;
        if(board[i][j]!='.') return solve(board, ind+1);
        else{
            for(char f = '1'; f <= '9'; f++)
            {
                if(isValidFill(board, i, j, f))
                {
                    board[i][j]= f;
                    if(solve(board, ind+1)) return true;
                    board[i][j]='.';
                }
            }
            return false;
        }
    }
    bool isValidFill(vector<vector<char>>& board, int i, int j, char fill) {
        for(int k=0; k<9; k++)
        {
            if(board[i][k]==fill) return false; //check the row
            if(board[k][j]==fill) return false; //check the column
            int r= i/3*3+j/3;   //select the block
            if(board[r/3*3+k/3][r%3*3+k%3]==fill) return false; //check the block
        }
        return true;
    }

        //////////// another hashtable solution  ////////////////////
    void solveSudoku(vector<vector<char> > &board) {
        if (board.size() != 9 || board[0].size() != 9)
        {
            return;
        }

        int rowhash[9][9] = {{0}}, colhash[9][9] = {{0}}, blockhash[9][3][3] = {{{0}}};
        for ( int i = 0; i < 9; i++)
        {
            for ( int j = 0; j < 9; j++)
            {
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '1';
                    rowhash[num][i] = 1;
                    colhash[num][j] = 1;
                    blockhash[num][i/3][j/3] = 1;
                }
            }
        }

        solveSudoku_DFS(board, 0, rowhash, colhash, blockhash);
    }
    bool solveSudoku_DFS(vector<vector<char> > &board, int pos, int rowhash[9][9], int colhash[9][9], int blockhash[9][3][3])
    {
        if ( pos >= 81)
        {
            return true;
        }
        int i = pos / 9, j = pos % 9;

        if (board[i][j] != '.')
        {
            return solveSudoku_DFS(board, pos+1, rowhash, colhash, blockhash);
        }
        else
        {
            for ( int num = 0; num < 9; num++)
            {
                if (rowhash[num][i] != 1 && colhash[num][j] != 1 && blockhash[num][i/3][j/3] != 1)
                {
                    board[i][j] = '1' + num;
                    rowhash[num][i] = 1;
                    colhash[num][j] = 1;
                    blockhash[num][i/3][j/3] = 1;
                    if (solveSudoku_DFS(board, pos+1, rowhash, colhash, blockhash))
                    {
                        return true;
                    }
                    else
                    {
                        board[i][j] = '.';
                        rowhash[num][i] = 0;
                        colhash[num][j] = 0;
                        blockhash[num][i/3][j/3] = 0;
                    }
                }
            }

            return false;
        }
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
