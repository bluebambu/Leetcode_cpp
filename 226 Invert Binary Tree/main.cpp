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


class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(!root) return nullptr;

        TreeNode* p=invertTree(root->left);
        TreeNode* q=invertTree(root->right);

        root->left=q;
        root->right=p;

        return root;
    }

        ///////////// leetcode passed  /////////////
    TreeNode* invertTree2(TreeNode* root) {
        if(!root) return nullptr;

        stack<TreeNode*> st;
        TreeNode* cur=root, *prev=nullptr;

        while(!st.empty() || cur!=nullptr){
            while(cur){
                st.push(cur);
                cur=cur->left;
            }

            TreeNode* node=st.top();
            if(node->right==nullptr || prev==node->right){
                st.pop();
                exchg(node);
                prev=node;
            }else
                cur=node->right;
        }

        return root;
    }

    void exchg(TreeNode* root){
        TreeNode* left=root->left;
        TreeNode* right=root->right;

        root->left=right;
        root->right=left;
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

    auto c=a.invertTree2(tree);



}
