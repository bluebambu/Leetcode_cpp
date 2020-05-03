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
    /// lc passed
    int totalNQueens(int n) {
        if(n<2) return n;
        vector<int> chess;
        int result=0;
        dfs(n, chess, result);
        return result;
    }

    void dfs(int n, vector<int>& chess, int& result){
        if(chess.size()==n){
            result++;
            return;
        }
        for(int i=0; i<n; ++i){
            if(valid(chess, i)){
                chess.push_back(i);
                dfs(n, chess, result);
                chess.pop_back();
            }
        }
    }

    bool valid(vector<int>& chess, int i){
        int n=chess.size();
        // new one is (n, i)
        for(int j=0; j<n; ++j){
            if(chess[j]==i || (abs(j-n)==abs(chess[j]-i)))
                return false;
        }
        return true;
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
