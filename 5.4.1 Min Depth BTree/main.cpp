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
    ////////// leetcode passed ////////////
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        if(!root->left || !root->right) return ((!root->left)? minDepth(root->right) : minDepth(root->left))+1;

        return 1+min(minDepth(root->left), minDepth(root->right));
    }
    ///////////////////////////////

    int minDepth(TreeNode* root) {
        if(root==nullptr) return 0;

        int result=INT_MAX;

        stack<pair<TreeNode*, int>> s;
        s.push(make_pair(root, 1));

        while(!s.empty()){
            auto node=s.top().first;
            auto depth=s.top().second;
            s.pop();

            if(node->left==nullptr && node->right==nullptr){
                result=min(result, depth);
            }

            if(node->left && result > depth)
                s.push(make_pair(node->left, depth+1));
            if(node->right && result >depth)
                s.push(make_pair(node->right, depth+1));
        }

        return result;
    }
//////////////////// PostOrder solution!! /////////////////////
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        vector<TreeNode*> stack;
        TreeNode* cur=root, *prev=nullptr;
        int depth=0, result=INT_MAX;

        while(cur || stack.size()){
            while(cur){
                stack.push_back(cur);
                depth++;
                cur=cur->left;
            }

            TreeNode* node=stack.back();

            if(node->right == nullptr || node->right==prev){
                if(!node->left && !node->right)
                    result=min(result, depth);
                stack.pop_back();
                depth--;
                prev=node;
            }else
                cur=node->right;
        }

        return result;
    }
///////////// Postorder recursion ////////////
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        int height=0;
        int mindep=INT_MAX;
        post(root, height, mindep);
        return mindep;
    }

    void post(TreeNode* root, int& height, int& mindep){
        if(!root) return;
        ++height;
        if(!root->left && !root->right) mindep=min(mindep, height);

        post(root->left, height, mindep);
        post(root->right, height, mindep);
        --height;
    }
};

int main()
{
    Solution a;

    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */

    auto b = a.minDepth3(tree);

        cout<<b<<" ";
}
