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

struct TreeNode;
void print();

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

void print(TreeNode* root){
    queue<TreeNode*> q;
    q.push(root);

    while(q.size()){
        auto tmp = q.front();
        cout<<tmp->val<<" ";
        if(tmp->left) q.push(tmp->left);
        if(tmp->right) q.push(tmp->right);
        q.pop();
    }
}



class Solution
{
public:
    //////////// TLE //////////////////
    int numIslands(vector<vector<char>>& M) {
        if(M.empty() || M[0].empty()) return 0;

        int result=2;

        int l = M.size(), w = M[0].size();

        for(int i=0; i<l; ++i){
            for(int j=0; j<w; ++j){
                if(M[i][j]=='1')
                    bfs(M, i, j, result);
            }
        }
        return result-2;
    }

    void bfs(vector<vector<char>>& M, int i, int j, int& result){
        vector<pair<int, int>> dir{{1,0},{-1,0},{0,1},{0,-1}};

        queue<pair<int, int>> q;
        q.push(make_pair(i, j));

        while(!q.empty()){
            pair<int, int> tmp = q.front();
            q.pop();
            M[tmp.first][tmp.second]=result;

            for(int k=0; k<dir.size(); ++k ){
                int tmp_x = tmp.first + dir[k].first;
                int tmp_y = tmp.second + dir[k].second;

                if(tmp_x>=0 && tmp_x<M.size() && tmp_y>=0 && tmp_y<M[0].size() && M[tmp_x][tmp_y]=='1')
                    q.push(make_pair(tmp_x, tmp_y));
            }
        }
        ++result;
    }

    /// TLE有两个原因， 一个是下面的reference， 另一个是 M[x][y] 应该在push进入 queue之前 改变值， 不然的话会有重复的搜索
    /*
                     x
                  x  3  y
                  4  1  2
                     5           如果是在 pop的时候改变值， 则 y 会被重复push进去queue （当分别走到 2 和 3 的时候）

    */

    ////////////////////  passed
    /// 很奇怪， result作为引用传进去， 耗时0.075s。 如果改成下面的写法， 只用0.057 s。 不知道为什么。。。。。。。
    void bfs(vector<vector<int>>& M, int i, int j){
        vector<pair<int, int>> dir{{1,0},{-1,0},{0,1},{0,-1}};
        M[i][j]=0;
        queue<pair<int, int>> q;
        q.push(make_pair(i, j));

        while(!q.empty()){
            pair<int, int> tmp = q.front();
            q.pop();

            for(int k=0; k<dir.size(); ++k ){
                int tmp_x = tmp.first + dir[k].first;
                int tmp_y = tmp.second + dir[k].second;

                if(tmp_x>=0 && tmp_x<M.size() && tmp_y>=0 && tmp_y<M[0].size() && M[tmp_x][tmp_y]==1){
                    q.push(make_pair(tmp_x, tmp_y));
                    M[tmp_x][tmp_y]=0;
                }
            }
        }
    }


    int numberIslands(vector<vector<int>>& M){
        if(M.empty() || M[0].empty()) return 0;

        int result=2;

        int l = M.size(), w = M[0].size();

        for(int i=0; i<l; ++i){
            for(int j=0; j<w; ++j){
                if(M[i][j]==1){
                    bfs(M, i, j);
                    ++result;
                }
            }
        }
        return result;
    }


    //////////// leetcode passed, DFS , 8ms  ///////
    int numIslands(vector<vector<char>>& M) {
        if(M.empty() || M[0].empty()) return 0;

        int result=0;
        for(int i=0; i<M.size(); ++i){
            for(int j=0; j<M[0].size(); ++j){
                if(M[i][j]=='1'){
                    dfs(M, i, j);
                    result++;
                }
            }
        }

        return result;
    }

    void dfs(vector<vector<char>>& M, int i, int j){
        if(i>=0 && i<M.size() && j >=0 && j<M[0].size())
            M[i][j]='0';
        if(i+1<M.size() && M[i+1][j]=='1')
            dfs(M, i+1, j);
        if(i-1>=0 && M[i-1][j]=='1')
            dfs(M, i-1, j);
        if(j+1<M[0].size() && M[i][j+1]=='1')
            dfs(M, i, j+1);
        if(j-1<M[0].size() && M[i][j-1]=='1')
            dfs(M, i, j-1);
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


}
