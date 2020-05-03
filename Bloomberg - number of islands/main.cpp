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



int main()
{
	vector<vector<int>> M = {{1, 0, 1, 1, 1, 0},
                             {0, 0, 0, 0, 1, 0},
                             {0, 0, 0, 1, 1, 0},
                             {0, 1, 0, 0, 1, 0}
                            };

    cout<<numberIslands(M);
}
