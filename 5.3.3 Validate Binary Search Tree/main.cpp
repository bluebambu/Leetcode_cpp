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
    ////////////////////////////////////////
    bool isValidBST(TreeNode* root) {
        TreeNode* prev = NULL;
        return validate(root, prev);
    }
    bool validate(TreeNode* node, TreeNode* &prev) {
        if (node == NULL) return true;
        if (!validate(node->left, prev)) return false;
        if (prev != NULL && prev->val >= node->val) return false;
        prev = node;
        return validate(node->right, prev);
    }

    ////////////// passed, better solution ,  no INT_MAX INT_MIN ////////
    bool isValidBST(TreeNode* root) {
        return valid(root, nullptr, nullptr);
    }

    bool valid(TreeNode* root, TreeNode* minNode, TreeNode* maxNode){
        if(!root) return true;
        if(( minNode && root->val <= minNode->val ) || (maxNode && root->val >= maxNode->val) ) /// 这一步不合理，就终止； 否则继续探寻下一步
            return false;
        return valid(root->left, minNode, root) && valid(root->right, root, maxNode);
    }

    /// 另一种写法！！！

    bool isValidBST(TreeNode* root) {
        return v(root, nullptr, nullptr);
    }

    bool v(TreeNode* root, TreeNode* low, TreeNode* high){
        if(!root) return true;
        if((!low || (root->val > low->val))  &&  (!high || (root->val < high->val)))
            return  v(root->left, low, root) && v(root->right, root, high);
        else
            return false;
    }


    ///////////////////////////////////////
    bool isValidBST(TreeNode* root) {
        vector<TreeNode*> stack;

        TreeNode* cur=root, *prev=nullptr;

        while(cur || stack.size()){
            while(cur){
                stack.push_back(cur);
                cur=cur->left;
            }

            TreeNode* node=stack.back();
            stack.pop_back();

            if(node->right){
                if(prev && prev->val >= node->val)
                    return false;
                prev=node;
                cur=node->right;
            }else{
                if(prev && prev->val >= node->val)
                    return false;
                prev=node;
            }
        }

        return true;
    }
////////////// morris /////////////
    bool isValidBST(TreeNode* root) {
        TreeNode* cur=root, *prev=nullptr;

        while(cur){
            if(!cur->left){
                if(prev && (prev->val >= cur->val)) return false;
                prev=cur;
                cur=cur->right;
            }else{
                TreeNode* node=cur->left;
                while(node->right!=nullptr && node->right!=cur )
                    node=node->right;

                if(node->right==nullptr){
                    node->right=cur;
                    cur=cur->left;
                }else{
                    node->right=nullptr;
                    if(prev && (prev->val >= cur->val)) return false;
                    prev=cur;
                    cur=cur->right;
                }
            }
        }
        return true;
    }
};

int main()
{
    Solution a;

    TreeNode* tree = new TreeNode(10,new TreeNode(5),
                                    new TreeNode(15, new TreeNode(6), new TreeNode(20)));
    /*      10
        5       15
              6    20

    */

    auto b = a.isValidBST(tree);

            cout<<b<<" ";
}
