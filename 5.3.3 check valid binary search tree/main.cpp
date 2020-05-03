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
    bool isValidBST(TreeNode* root) {
        return valid(root, INT_MIN, INT_MAX);
    }

    bool valid(TreeNode* root, int left, int right){
        if(!root) return true;

        return root->val > left && root->val < right &&
                valid(root->left, left, root->val) &&
                valid(root->right, root->val, right);
    }
/////////////////////////////////////////////

    bool isValidBST2(TreeNode* root) {
        vector<TreeNode*> stack;

        TreeNode* cur=root, *prev=nullptr;

        while(cur || stack.size()){
            while(cur){
                stack.push_back(cur);
                cur=cur->left;
            }

            TreeNode* node=stack.back();
            stack.pop_back();

            if(prev && prev->val >= node->val)
                    return false;
            prev=node;

            if(node->right) cur=node->right;

        }

        return true;
    }
//////////////////////////////////////
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, NULL, NULL);
    }

    bool isValidBST(TreeNode* root, TreeNode* minNode, TreeNode* maxNode) {
        if(!root) return true;
        if(minNode && root->val <= minNode->val || maxNode && root->val >= maxNode->val)
            return false;
        return isValidBST(root->left, minNode, root) && isValidBST(root->right, root, maxNode);
    }
//////////////////////////////////////////

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

    cout<<a.isValidBST2(tree);


}
