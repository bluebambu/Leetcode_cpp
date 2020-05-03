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


class Solution
{
public:
    int maxuniquelen(TreeNode* root) {
        int result=0;
        vector<int> path;
        dfs(root, path, result);
        return result;
    }

    void dfs(TreeNode* root, vector<int>& path, int& result){
        if(!root) return;

        if( find(path.begin(), path.end(), root->val)!= path.end())
            return;

        if( !root->left && !root->right){
            result=max(result, int(path.size()+1));
            return;
        }

        path.push_back(root->val);
        dfs(root->left, path, result);
        dfs(root->right, path, result);

    }

};

int main()
{
    Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree1 = new TreeNode(1,new TreeNode(2, nullptr,
                                                    new TreeNode(INT_MAX, new TreeNode(3),
                                                                    new TreeNode(3))),
                                    new TreeNode(3, new TreeNode(6),
                                                    new TreeNode(7, new TreeNode(14, new TreeNode(14),
                                                                                    new TreeNode(9)),
                                                                    new TreeNode(3))));
    /*      6
        3       8
     1    4   7    9
    */

    TreeNode* tree = new TreeNode(1);

    auto b=a.maxuniquelen(tree1);

    cout<<b;


}
