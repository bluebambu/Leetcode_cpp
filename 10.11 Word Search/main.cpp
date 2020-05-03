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


class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if(board.empty() || board[0].empty()) return false;

        int m=board.size(), n=board[0].size();
        vector<vector<bool>> map(m, vector<bool>(n, false));

        for(int i=0; i<m; ++i){
            for(int j=0; j<n; ++j){
                if(dfs(board, i, j, 0, word, map))
                    return true;
            }
        }
        return false;
    }

    bool dfs(vector<vector<char>>& board, int x, int y, int i, string& word, vector<vector<bool>>& map){
        if(i==word.size()) /// 这句 必须写在第一个！！ 不然会被下面一句给过滤掉 ！！！
            return true;
        if(x<0 || x>=board.size() || y<0 || y>=board[0].size())
            return false;
        if(board[x][y]!=word[i] || map[x][y]) /// 重要！
            return false;
        map[x][y]=true;
        bool result = dfs(board, x+1, y, i+1, word, map) ||
                      dfs(board, x-1, y, i+1, word, map) ||
                      dfs(board, x, y+1, i+1, word, map) ||
                      dfs(board, x, y-1, i+1, word, map) ;
        map[x][y]=false;
        return result;
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
