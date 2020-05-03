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
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> result;
        vector<int> tmp;
        path(root, sum, tmp, result);
        return result;
    }

    void path(TreeNode* root, int sum, vector<int> tmp, vector<vector<int>>& result){
        // tmp 貌似不能用reference   可以用的
        if(!root) return;
        tmp.push_back(root->val);
        if(!root->left && !root->right){
            if(root->val == sum){
                result.push_back(tmp);
            }
        }

        path(root->left, sum-root->val, tmp, result);
        path(root->right, sum-root->val, tmp, result);

    }
////////////////////////////////////////////////////////////////
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> result;
        vector<int> tmp;
        int total=0;

        vector<TreeNode*> stack;
        TreeNode* cur=root, *prev=nullptr; /// postorder traversal

        while(cur || stack.size()){
            while(cur){
                stack.push_back(cur);
                total+=cur->val;
                tmp.push_back(cur->val);
                cur=cur->left;
            }

            TreeNode* node=stack.back();

            if(node->right==nullptr || node->right==prev){
                if(!node->left && !node->right)
                    if(total==sum)
                        result.push_back(tmp);
                stack.pop_back();
                tmp.pop_back();
                total-=node->val;
                prev=node;
            }else
                cur=node->right;
        }

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

    a.flatten(tree);


}
