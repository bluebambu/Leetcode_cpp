#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
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
    vector<int> PostOrderTraverse(TreeNode *root)
    {
        vector<int> val_output;
        vector<TreeNode*> node_stack;
        TreeNode* cur=root, *prev=nullptr, * tmp=nullptr;

        while(cur || !node_stack.empty())
        {
            while(cur)
            {
                node_stack.push_back(cur);
                cur=cur->left;
            }


            if(!node_stack.empty())
            {
                tmp=node_stack.back();

                if(tmp->right != prev && tmp->right)
                {
                    cur=tmp->right;
                }
                else
                {
                    val_output.push_back(tmp->val);
                    prev=tmp;
                    node_stack.pop_back();
                }
            }
        }
        return val_output;
    }


    vector<int> PostOrderTraverse2(TreeNode* root)
    {
        vector<int> val_output;
        vector<TreeNode*> node_stack;

        node_stack.push_back(root);

        TreeNode* cur, *pre=nullptr;

        while(!node_stack.empty())
        {
            cur=node_stack.back();

            if((cur->left==nullptr && cur->right==nullptr) ||
               (pre!=nullptr && (pre==cur->right || pre==cur->left)))
            {
                val_output.push_back(cur->val);
                node_stack.pop_back();
                pre=cur;
            }
            else
            {
                if(cur->right) node_stack.push_back(cur->right);
                if(cur->left) node_stack.push_back(cur->left);
            }
        }

        return val_output;
    }

    vector<int> PostOrderTraverse3(TreeNode* root)
    {
        vector<TreeNode*> node_stack;
        vector<int> result;

        TreeNode* leftptr = root;
        TreeNode* prev = nullptr;

        while( node_stack.size() || leftptr)
        {
            while(leftptr)
            {
                node_stack.push_back(leftptr);
                leftptr  = leftptr->left;
            }

            TreeNode* tmp = node_stack.back();

            if(prev ==  tmp->right || !tmp->right)
            {
                node_stack.pop_back();
                result.push_back(tmp->val);
                prev = tmp;
            }
            else
                leftptr = tmp->right;

        }

        return result;
    }


    /////////////// Morris traversal 麻烦！ ///////////////
void reverse(TreeNode *from, TreeNode *to) // reverse the tree nodes 'from' -> 'to'.
{
    if (from == to)
        return;
    TreeNode *x = from, *y = from->right, *z;
    while (true){
        z = y->right;
        y->right = x;
        x = y;
        y = z;
        if (x == to)
            break;
    }
}

void printReverse(TreeNode* from, TreeNode *to)// print the reversed tree nodes 'from' -> 'to'.
{
    reverse(from, to);

    TreeNode *p = to;
    while (true)
    {
        printf("%d ", p->val);
        if (p == from)
            break;
        p = p->right;
    }

    reverse(to, from);
}

void postorderMorrisTraversal(TreeNode *root) {
    TreeNode dump(0);
    dump.left = root;
    TreeNode *cur = &dump, *prev = NULL;
    while (cur)
    {
        if (cur->left == NULL)
        {
            cur = cur->right;
        }
        else
        {
            prev = cur->left;
            while (prev->right != NULL && prev->right != cur)
                prev = prev->right;

            if (prev->right == NULL)
            {
                prev->right = cur;
                cur = cur->left;
            }
            else
            {
                printReverse(cur->left, prev);  // call print
                prev->right = NULL;
                cur = cur->right;
            }
        }
    }
}
/////////////////////// preorder 反转！ ////////////////////
    vector<int> postorderTraversal(TreeNode *root) {
        stack<TreeNode*> nodeStack;
        vector<int> result;
        //base case
        if(root==NULL)
            return result;
        nodeStack.push(root);
        while(!nodeStack.empty()){
            TreeNode* node= nodeStack.top();
            result.push_back(node->val);
            nodeStack.pop();
            if(node->left)
            nodeStack.push(node->left);
            if(node->right)
            nodeStack.push(node->right);
        }

        reverse(result.begin(),result.end());
        return result;

}
};

int main()
{
    Solution a;

    TreeNode* tree = new TreeNode(3,new TreeNode(6, new TreeNode(9), new TreeNode(1)),new TreeNode(4, new TreeNode(3), new TreeNode(4)));
    /*      3
        6       4
     9    1   3    4

    */

    auto b = a.PostOrderTraverse3(tree);

    for(auto i:b)
        cout<<i<<" ";
}
