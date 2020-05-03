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
    void connect(TreeLinkNode *root) {
        connect(root, NULL);
    }

    void connect(TreeLinkNode *root, TreeLinkNode *sibling) {
        if (root == nullptr)
            return;
        else
            root->next = sibling;

        connect(root->left, root->right);

        if (sibling)
            connect(root->right, sibling->left);
        else
            connect(root->right, nullptr);
    }


        //更简洁的方法
        void connect(TreeLinkNode *root) {
            if(!root) return;
            if(root->left!=NULL)
                root->left->next = root->right;
            if(root->left && root->next!=NULL)
                root->right->next = root->next->left;

            connect(root->left);
            connect(root->right);
        }
        // 尾递归可以直接变成迭代

    void connect(TreeLinkNode *root) {
        if(!root) return;

        vector<TreeLinkNode*> stack;
        TreeLinkNode* cur;

        stack.push_back(root);

        while(stack.size()){
            cur=stack.back();
            stack.pop_back();

            if(cur->left)
                cur->left->next=cur->right;
            if(cur->left && cur->next)
                cur->right->next=cur->next->left;

            if(cur->right) stack.push_back(cur->right);
            if(cur->left) stack.push_back(cur->left);
        }
    }


};

int main()
{
    Solution a;

    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1),
                                                    new TreeNode(4)),
                                    new TreeNode(8, new TreeNode(7),
                                                    new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */

    auto b = a.preorderTraversMorris(tree);

    for(auto i:b)
        cout<<i<<" ";
}
