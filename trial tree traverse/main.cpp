#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>

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
    vector<int> PreOrderTraverse(TreeNode* root)
    {
        vector<int> val_output;
        vector<TreeNode*> node_stack;

        TreeNode* cur=root;
        node_stack.push_back(root);

        while(node_stack.size())
        {
            TreeNode* node = node_stack.back();
            node_stack.pop_back();
            val_output.push_back(node->val);

            if(node->right) node_stack.push_back(node->right);
            if(node->left) node_stack.push_back(node->left);
        }

        return val_output;
    }

    vector<int> InOrderTraverse(TreeNode* root)
    {
        vector<int> val_output;
        vector<TreeNode*> node_stack;

        TreeNode* cur=root;

        while(cur || !node_stack.empty())
        {
            while(cur)
            {
                node_stack.push_back(cur);
                cur=cur->left;
            }

            if(node_stack.size())
            {
                cur=node_stack.back();
                val_output.push_back(cur->val);
                node_stack.pop_back();
                cur=cur->right;
            }
        }

        return val_output;


    }

    vector<int> InOrderTraverse2(TreeNode* root)
    {
        vector<int> val_output;
        vector<TreeNode*> node_stack;

        TreeNode* cur=root;

        while(cur || node_stack.size())
        {
            if(cur)
            {
                node_stack.push_back(cur);
                cur=cur->left;
            }
            else
            {
                cur=node_stack.back();
                node_stack.pop_back();
                val_output.push_back(cur->val);
                cur=cur->right;
            }
        }

        return val_output;
    }

    vector<int> PostOrderTraverse(TreeNode* root)
    {
        vector<int> val_output;
        vector<TreeNode*> node_stack;

        TreeNode* cur=root, *prev = nullptr, *tmp;

        while(cur || node_stack.size())
        {
            while(cur)
            {
                node_stack.push_back(cur);
                cur=cur->left;
            }

            if(node_stack.size())
            {
                tmp=node_stack.back();

                if(tmp->right && tmp->right!=prev)
                {
                    cur=tmp->right;
                }
                else
                {
                    val_output.push_back(tmp->val);
                    node_stack.pop_back();
                    prev=tmp;
                }
            }
        }

        return val_output;
    }

    vector<int> pre(TreeNode* root)
    {
        vector<TreeNode*> node_stack;
        vector<int> val_container;

        TreeNode* cur = root;

        node_stack.push_back(root);

        while(node_stack.size())
        {
            cur=node_stack.back();
            node_stack.pop_back();
            val_container.push_back(cur->val);

            if(cur->right) node_stack.push_back(cur->right);
            if(cur->left) node_stack.push_back(cur->left);

        }

        return val_container;

    }

    vector<int> In(TreeNode* root)
    {
        vector<int> val_output;
        vector<TreeNode*> node_stack;

        TreeNode* cur=root;

        while(node_stack.size() || cur)
        {
            while(cur)
            {node_stack.push_back(cur); cur=cur->left;}

            TreeNode* node = node_stack.back();
            node_stack.pop_back();
            val_output.push_back(node->val);

            if(node->right)
            {
                cur=node->right;
            }
        }

        return val_output;
    }

    vector<int> Post(TreeNode* root)
    {
        vector<int> val_output;
        vector<TreeNode*> node_stack;
        TreeNode* cur = root;
        TreeNode* prev;

        while(cur || node_stack.size())
        {
            while(cur)
            {
                node_stack.push_back(cur);
                cur=cur->left;
            }

            TreeNode* node=node_stack.back();

            if(node->right && node->right!=prev)
            {
                cur=node->right;
            }
            else
            {
                node_stack.pop_back();
                val_output.push_back(node->val);
                prev=node;
            }

        }

        return val_output;
    }

    vector<int> Post2(TreeNode* root)
    {
        vector<int> val_output;
        vector<TreeNode*> node_stack;

        TreeNode* cur=root;
        TreeNode* pre=nullptr;

        node_stack.push_back(root);

        while(node_stack.size())
        {
            cur=node_stack.back();

            if((!cur->left && !cur->right) || (pre!=nullptr && (pre==cur->left || pre==cur->right)))
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

    vector<int> PreOrder(TreeNode* root)
    {
        vector<int> val_output;
        vector<TreeNode*> node_stack  ;

        TreeNode* cur=root;

        node_stack.push_back(cur);

        while(node_stack.size())
        {
            cur=node_stack.back();
            node_stack.pop_back();
            val_output.push_back(cur->val);

            if(cur->right) node_stack.push_back(cur->right);
            if(cur->left) node_stack.push_back(cur->left);

        }

        return val_output;
    }

    vector<int> InOrder(TreeNode* root)
    {
        vector<int> val_output;
        vector<TreeNode*> node_stack  ;

        TreeNode* cur=root;

        while(node_stack.size() || cur)
            // cur 只管探索 node->left，所以可以放在条件语句中
        {
            while(cur)
            {
                node_stack.push_back(cur);
                cur=cur->left;
            }

            TreeNode* node = node_stack.back();
            node_stack.pop_back();
            val_output.push_back(node->val);

            if(node->right) cur=node->right;


        }

        return val_output;

    }

    vector<int> PostOrder(TreeNode* root)
    {
        vector<int> val_output;
        vector<TreeNode*> node_stack  ;

        TreeNode* cur=root;
        TreeNode* prev=nullptr;

        while(node_stack.size() || cur)
        {
            while(cur)
            {
                node_stack.push_back(cur);
                cur=cur->left;
            }

            TreeNode* node = node_stack.back();

            if(node->right && (node->right != prev))
            {
                cur=node->right;
            }
            else
            {
                node_stack.pop_back();
                val_output.push_back(node->val);
                prev=node;
            }

        }

        return val_output;
    }

    vector<int> PreOrder2(TreeNode* root)
    {
        vector<int> result;

        pretraverse(root, result);

        return result;
    }

    void pretraverse(TreeNode* node, vector<int> & result)
    {
        if(node==nullptr) return;

        result.push_back(node->val);
        pretraverse(node->left, result);
        pretraverse(node->right, result);
    }

    vector<int> PreOrder3(TreeNode* root)
    {
        vector<int> result;
        vector<TreeNode*> help_stack;

        help_stack.push_back(root);

        while(!help_stack.empty())
        {
            TreeNode* tmp = help_stack.back();
            help_stack.pop_back();

            result.push_back(tmp->val);

            if(tmp->right) help_stack.push_back(tmp->right);
            if(tmp->left) help_stack.push_back(tmp->left);
        }

        return result;
    }

    vector<int> InOrder3(TreeNode* root)
    {
        vector<TreeNode*> help_stack    ;
        vector<int> result;

        TreeNode* cur=root, *node;

        while(help_stack.size() || cur)
        {
            while(cur)
            {
                help_stack.push_back(cur);
                cur=cur->left;
            }

            TreeNode* tmp = help_stack.back();
            help_stack.pop_back();

            result.push_back(tmp->val);

            if(tmp->right)
                cur=tmp->right;
        }

        return result;
    }

    vector<int> PostOrder3(TreeNode* root)
    {
        vector<TreeNode*> help_stack;
        vector<int> result;

        TreeNode* cur=root, *node, *prev=nullptr;

        while(help_stack.size() || cur)
        {
            while(cur)
            {
                help_stack.push_back(cur);
                cur=cur->left;
            }

            TreeNode* tmp = help_stack.back();

            if(tmp->right && prev != tmp->right) // 注意查 tmp->right
                cur=tmp->right;
            else
            {
                help_stack.pop_back();
                result.push_back(tmp->val);
                prev = tmp;
            }
        }

        return result;
    }

    vector<int> PostOrder4(TreeNode* root)
    {
        vector<TreeNode*> help_stack;
        vector<int> result;

        TreeNode* cur=root, *node;
        TreeNode* prev=nullptr;

        while(help_stack.size() || cur)
        {
            while(cur)
            {
                help_stack.push_back(cur);
                cur=cur->left;
            }

            node = help_stack.back();

            if(node->right && node->right != prev)
                cur=node->right;
            else
            {
                result.push_back(node->val);
                help_stack.pop_back();
                prev=node;
            }
        }

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

    auto b = a.PostOrder4(tree);

    for(auto i:b)
        cout<<i<<" ";
}
