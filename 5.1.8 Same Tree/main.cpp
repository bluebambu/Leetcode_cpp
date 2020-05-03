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
    bool SameTree(TreeNode* root1, TreeNode* root2)
    {
        if( !root1 && !root2 ) return true;

        if( !root1 || !root2 ) return false;

        return root1->val == root2->val
                && SameTree(root1->left, root2->left)
                && SameTree(root1->right, root2->right);
    }



    bool SameTree2(TreeNode* root1, TreeNode* root2)
    {
        vector<TreeNode*> help_stack;

        help_stack.push_back(root1);
        help_stack.push_back(root2);

        TreeNode *tmp1, *tmp2;

        while(help_stack.size())
        {
            tmp2=help_stack.back();
            help_stack.pop_back();
            tmp1=help_stack.back();
            help_stack.pop_back();

            if(!tmp2 && !tmp1) continue;
            if(!tmp1 || !tmp2) return false;
            // 要注意左右子为空的情况，不能像 traverse时
            // 那样直接 if(node->left) 略过去了，而应该比较
            if(tmp2->val != tmp1->val)
                return false;
            else
            {
                help_stack.push_back(tmp1->right);
                help_stack.push_back(tmp2->right);
                help_stack.push_back(tmp1->left);
                help_stack.push_back(tmp2->left);
            }
        }

        return true;
    }

    bool SameTree3(TreeNode* root1, TreeNode* root2)
    {
        if(!root1 && !root2) return true;
        if(!root1 || !root2) return false;

        return root1->val == root2 -> val
                && SameTree(root1->left, root2->left)
                && SameTree(root1->right, root2->right);
    }
/////////////////////////////////////////////////////////
    bool isSameTree(TreeNode* p, TreeNode* q) {
        TreeNode* curp=p, *curq=q;
        vector<TreeNode*> stack;

        while(curp || curq || stack.size()){
        ///// 判断条件很 tricky //////////////
            if((curp && curq)==0 && (curp || curq)==1) return false;

            while(curp || curq){
                if((curp && curq)==0 && (curp || curq)==1) return false;
                stack.push_back(curp);
                stack.push_back(curq);
                curp=curp->left;
                curq=curq->left;
            }

            TreeNode* nodeq = stack.back();
            stack.pop_back();
            TreeNode* nodep = stack.back();
            stack.pop_back();

            if(nodeq->val != nodep->val)
                return false;

            if(nodep->right) curp=nodep->right;
            if(nodeq->right) curq=nodeq->right;
        }

        return true;
    }


};

int main()
{
    Solution a;

    TreeNode* tree1 = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree2 = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));

    /*      6
        3       8
     1    4   7    9

    */

    auto b = a.SameTree4(tree1, tree2);


        cout<<b<<" ";
}
