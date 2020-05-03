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


struct TreeNode
{
    TreeNode(int a):val(a), left(nullptr), right(nullptr) {}
    TreeNode(int a, TreeNode* x, TreeNode* y):val(a), left(x), right(y) {}
    TreeNode():val(0), left(nullptr), right(nullptr) {}

    int val;
    TreeNode *left;
    TreeNode *right;

};

/// BFS
class Solution2 {
    vector<pair<int, int>> dir{{1,0}, {-1,0}, {0,1}, {0,-1}};
public:
    void solve(vector<vector<char>>& board) {
        if(board.empty() || board[0].empty()) return;

        int len=board.size(), wid=board[0].size();

        for(int j=0; j<wid; ++j)
            if(board[0][j]=='O')
                bfs(board, 0, j);

        for(int i=0; i<len; ++i)
            if(board[i][wid-1]=='O')
                bfs(board, i, wid-1);

        for(int j=wid-1; j>=0; --j)
            if(board[len-1][j]=='O')
                bfs(board, len-1, j);

        for(int i=len-1; i>=0; --i)
            if(board[i][0]=='O')
                bfs(board, i, 0);

        for(int i=0; i<len; ++i){
            for(int j=0; j<wid; ++j){
                board[i][j] = ( board[i][j]=='n' ? 'O' : 'X') ;
            }
        }
    }

    void bfs(vector<vector<char>>& board, int x, int y){
        if(x<0 || x>=board.size() || y<0 || y>=board[0].size())
            return;
        queue<pair<int, int>> q;
        q.push(make_pair(x, y));  /// queue里存的是曾经是 X ， 但是已经改成 N 的cell
        board[x][y]='n';

        while(!q.empty()){
            auto tmp=q.front();
            q.pop();

            for(int i=0; i<dir.size(); ++i){
                int tmp_x = tmp.first+dir[i].first;
                int tmp_y = tmp.second+dir[i].second;

                if( tmp_x>=0 && tmp_x<board.size() && tmp_y>=0 && tmp_y<board[0].size() &&  board[tmp_x][tmp_y]=='O'){
                    board[tmp_x][tmp_y]='n';   /// 必须在这里改值
                    q.push(make_pair(tmp_x, tmp_y));
                }
            }
        }

    }
};



/// 解法不好， visited 根本不需要
class Solution
{
public:
    void solve(vector<string>& board) {
        if(board.empty() || board[0].empty()) return;
        int width=board[0].size(), length=board.size();
        vector<vector<bool>> visited(length, vector<bool>(width, true));

        for(int i=0; i<width-1; ++i)
            search(board,visited, i, 0);
        for(int i=1; i<length-1; ++i)
            search(board,visited, width-1, 1);
        for(int i=width-2; i>=0; --i)
            search(board, visited,i, length-1);
        for(int i=length-2; i>=0; --i)
            search(board,visited, i, 0);

        for(int i=0; i<length-1; ++i)
            for(int j=0; j<width-1; ++j)
                if(board[i][j]=='O') board[i][j]= 'X' ;

        for(int i=0; i<length-1; ++i)
            for(int j=0; j<width-1; ++j)
                board[i][j]== (board[i][j]=='N') ? 'O' : 'X';
    }

    void search(vector<string> & board,vector<vector<bool>>& visited, int i, int j){
        int width=board[0].size(), length=board.size();
        if(i<0 || i>=length || j<0 || j>=width)
            return;
        if(visited[i][j]==false) return;
        if(visited[i][j]==true && board[i][j]=='O')
            {board[i][j]=='N';visited[i][j]=false;}
        if(visited[i][j]==true && board[i][j]=='X')
            {visited[i][j]=false;return;}


        search(board, visited, i+1, j);
        search(board, visited, i, j+1);
        search(board, visited, i-1, j);
        search(board, visited, i, j-1);
    }
};


/// 标准 DFS 解
class Solution {
public:
	void solve(vector<vector<char>>& board) {
        int i,j;
        int row=board.size();
        if(!row)
        	return;
        int col=board[0].size();

		for(i=0;i<row;i++){
			check(board,i,0,row,col);
			if(col>1)
				check(board,i,col-1,row,col);
		}
		for(j=1;j+1<col;j++){
			check(board,0,j,row,col);
			if(row>1)
				check(board,row-1,j,row,col);
		}
		for(i=0;i<row;i++)
			for(j=0;j<col;j++)
				if(board[i][j]=='O')
					board[i][j]='X';
		for(i=0;i<row;i++)
			for(j=0;j<col;j++)
				if(board[i][j]=='1')
					board[i][j]='O';
    }
	void check(vector<vector<char> >&vec,int i,int j,int row,int col){
		if(vec[i][j]=='O'){
			vec[i][j]='1';
			if(i>1)
				check(vec,i-1,j,row,col);
			if(j>1)
				check(vec,i,j-1,row,col);
			if(i+1<row)
				check(vec,i+1,j,row,col);
			if(j+1<col)
				check(vec,i,j+1,row,col);
		}
	}
};

/** But here is the problem of DFS solution



This is a DFS solution, but it may causes a stack overflow issue.

When you use DFS, it is tricky to use:

        if(i>1)
            check(vec,i-1,j,row,col);
        if(j>1)
            check(vec,i,j-1,row,col);

because it is more common to write like this:

        if(i>=1)
            check(vec,i-1,j,row,col);
        if(j>=1)
            check(vec,i,j-1,row,col);

Then I'll explain it.

There is a test case like this:

OOOOOOOOOO
XXXXXXXXXO
OOOOOOOOOO
OXXXXXXXXX
OOOOOOOOOO
XXXXXXXXXO
OOOOOOOOOO
OXXXXXXXXX
OOOOOOOOOO
XXXXXXXXXO

To make it clear, I draw a 10x10 board, but it is actually a 250x250 board like this one.

When dfs function visit board[0][0], it ought to visit every grid marked 'O', thus lead to stack overflow(runtime error).

After you change "if(j>=1)" to "if(j>1)", the DFS function won't check board[i][0] (0<=i<=row-1), and then not all the grids marked 'O' will be visited when you dfs(board[0][0]).
Your code won't cause stack overflow in this test case, but if we change the test case a little, it won't work well.

Consider a test case like this:

OOOOOOOOOOOX
XXXXXXXXXXOX
XOOOOOOOOOOX
XOXXXXXXXXXX
XOOOOOOOOOOX
XXXXXXXXXXOX
XOOOOOOOOOOX
XOXXXXXXXXXX
XOOOOOOOOOOX
XXXXXXXXXXOX

I draw a 10x12 board, but it may be as large as the 250x250 board.

I believe that your code will get "runtime error" in this test case when tested in Leetcode system.




*/



int main()
{
    Solution a;

    vector<string> board = {"XOXOXO","OXOXOX","XOXOXO","OXOXOX"};

    a.solve(board);

    for(auto i:board){
        cout<<i<<endl;
    }

}
