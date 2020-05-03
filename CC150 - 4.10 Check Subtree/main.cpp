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

void print(TreeNode* root){
    queue<TreeNode*> q;
    q.push(root);

    while(q.size()){
        int n=q.size();
        for(int i=0; i<n; ++i){
            TreeNode* front = q.front();
            q.pop();

            if(!front)
                cout<<"# ";
            else{
                cout<<front->val<<" ";
                q.push(front->left);
                q.push(front->right);
            }
        }
        cout<<endl;
    }
}


class Solution
{
public:
    bool ContainTree(TreeNode* root, TreeNode* b){
        if(!b)  return true;
        if(!root)  return false;
        if(root->val == b->val)
            if( SameTree(root, b) ) /// 这里不能直接 return SameTree(root,b) !!!
                return true;
        return ContainTree(root->left, b) || ContainTree(root->right, b) ;
    }

    bool SameTree(TreeNode* a, TreeNode* b){
        if(!a && !b)
            return true;
        if(!a || !b)
            return false;
        return a->val==b->val && SameTree(a->left, b->left) && SameTree(a->right, b->right);
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
