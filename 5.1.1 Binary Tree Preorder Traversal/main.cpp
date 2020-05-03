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
    vector<int> preorderTraversal(TreeNode *root)
    {
        vector<TreeNode*> nodeStack;
        vector<int> val_output;

        if(!root) return val_output;

        nodeStack.push_back(root);

        while(nodeStack.size())
        {
            TreeNode* tmp = nodeStack.back();
            nodeStack.pop_back();

            val_output.push_back(tmp->val);

            if(tmp->right) nodeStack.push_back(tmp->right);
            if(tmp->left) nodeStack.push_back(tmp->left);
        }

        return val_output;
    }

    vector<int> preorderTraversMorris(TreeNode* root)
    // morris 的方法中，叶子 和 节点 需要区别对待
    {
        vector<int> val_output;

        TreeNode* cur = root;

        while(cur)
        {
            if(cur->left == nullptr)
            {
                val_output.push_back(cur->val); // 输出叶子
                cur = cur->right;
            }
            else
            {
                TreeNode* node = cur -> left;
                while(node->right!=nullptr && node->right!=cur)
                    node=node->right;

                if(node->right == nullptr)
                {
                    node->right=cur;
                    val_output.push_back(cur->val);
                    // 输出节点， 改变位置能变成中序
                    cur=cur->left;
                }
                else
                {
                    node->right=nullptr;
                    cur=cur->right;
                }
            }
        }

        return val_output;
    }

    vector<int> preorderTraversal2(TreeNode *root)
    {
        vector<TreeNode*> node_stack;
        vector<int> result;

        node_stack.push_back(root);

        while(node_stack.size())
        {
            TreeNode* tmp = node_stack.back();
            node_stack.pop_back();
            result.push_back(tmp->val);

            if(tmp->right) node_stack.push_back(tmp->right);
            if(tmp->left) node_stack.push_back(tmp->left);
        }

        return result;
    }

    vector<int> preorderTraversalMorris2(TreeNode* root) {

            TreeNode* cur=root;
            vector<int> result;
            if(!root) return result;

            while(cur){
                if(cur->left==nullptr){
                    result.push_back(cur->val);
                    cur=cur->right;
                }else{
                    TreeNode* node = cur->left;

                    while(node->right!=nullptr && node->right!=cur)
                        node=node->right;

                    if(node->right==nullptr){
                        node->right=cur;
                        result.push_back(cur->val);
                        cur=cur->left;
                    }else if(node->right==cur){
                        node->right=nullptr;
                        cur=cur->right;
                    }
                }
            }

            return result;

    }

    vector<int> preorderTraversal5(TreeNode* root) {
        vector<int> result;
        if(!root) return result;

        result.push_back(root->val);
        if(root->left) result.insert(result.end(), preorderTraversal(root->left).begin(), preorderTraversal(root->left).end());
        if(root->right) result.insert(result.end(), preorderTraversal(root->right).begin(), preorderTraversal(root->right).end());

        return result;

    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        vector<TreeNode*> stack;
        TreeNode* cur=root;

        while(cur || stack.size()){
            while(cur){
                result.push_back(cur->val);
                stack.push_back(cur);
                cur=cur->left;
            }

            TreeNode* tmp = stack.back();
            stack.pop_back();

            if(tmp->right) cur=tmp->right;
        }

        return result;
    }


///////////// leetcode passed, 只需要push 右子树 ////////////////////////
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        vector<TreeNode*> stack;
        TreeNode* cur=root;

        while(cur || stack.size()){
            while(cur){
                result.push_back(cur->val);
                if(cur->right) stack.push_back(cur->right);
                cur=cur->left;
            }

            if(stack.empty()) break;
            cur=stack.back();
            stack.pop_back();

//            if(stack.size()){
//                TreeNode* node=stack.back();
//                stack.pop_back();
//                cur=node;
//            }
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

    auto b = a.preorderTraversal5(tree);

    for(auto i:b)
        cout<<i<<" ";
}
