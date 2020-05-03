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

class Solution2 {
public:
    /// pass, recursion
    void recoverTree(TreeNode* root) {
        TreeNode *p1=nullptr, *p2=nullptr, *prev=nullptr; /// initialization is very important! otherwise they will point to random place!!!
        r(root, prev, p1, p2);
        swap(p1->val, p2->val); /// 必须交换 val， 不然毫无作用， 因为p1 p2只是node* 的 copy ， 不是实际值。
    }

    void r(TreeNode* root, TreeNode*& prev, TreeNode *&p1, TreeNode *&p2){
        if(!root) return ;
        r(root->left, prev, p1, p2);
        if(prev){
            if(!p1 && prev->val > root->val)
                p1=prev;
            if(root->val < prev -> val)
                p2=root;
        }
        prev = root;
        r(root->right, prev, p1, p2);
    }
};

class Solution
{
public:
    ///////// passed
    void recoverTree(TreeNode* root) {

        TreeNode* cur=root, *prev=nullptr;
        TreeNode* x1=nullptr, *x2=nullptr;

        while(cur){
            if(cur->left==nullptr){
                visit(cur, prev, x1, x2);
                cur=cur->right;
            }else{
                TreeNode* node=cur->left;

                while(node->right!=nullptr && node->right!=cur)
                    node=node->right;

                if(node->right==nullptr){
                    node->right=cur;
                    cur=cur->left;
                }else{
                    node->right=nullptr;
                    visit(cur, prev, x1, x2);
                    cur=cur->right;
                }
            }
        }

        swap(x1->val, x2->val);

        return;
    }

    void visit(TreeNode*& cur, TreeNode*& prev, TreeNode*& x1, TreeNode*& x2){
        if(prev!=nullptr){
            if(cur->val < prev->val && x2==nullptr && x1==nullptr){
                x1=prev;x2=cur;
            }else if(x1!=nullptr && prev!=x1 && cur->val < prev->val){
                x2=cur;
            }
        }

        prev=cur;
    }



 ////////////////////////////////////////////////
        TreeNode* first=NULL;
        TreeNode* second=NULL;
        TreeNode* prev = new TreeNode(INT_MIN);

    void recoverTree(TreeNode* root) {
        help(root);
        swap(first->val, second->val);
    }

    void help(TreeNode* root){
        if(root==NULL)  return;
        help(root->left);
        if(first==NULL && prev->val >= root->val)   first=prev;
        if(first!=NULL && prev->val >= root->val)   second=root;
        prev=root;
        help(root->right);
    }
};

};


int main()
{
    Solution a;

    TreeNode* tree = new TreeNode(3,new TreeNode(6, new TreeNode(9), new TreeNode(1)),new TreeNode(4, new TreeNode(3), new TreeNode(4)));
    /*      3
        6       4
     9    1   3    4

    */

    auto b = a.LevelOrder6(tree);

    for(auto i:b)
        {for(auto j:i)
            cout<<j<<" ";
         cout<<endl;
        }
}
