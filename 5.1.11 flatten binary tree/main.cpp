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
    void flatten(TreeNode* root) {
        if(!root) return;

        flatten(root->left);
        flatten(root->right);
        // 仔细想，其实前序，中序，后序都能得到最后的答案
        // 因此，用前序改成non recursive的就很方便

        if(root->left){ // if 语句是必须的！！
            TreeNode* cur=root->left;
            while(cur->right)
                cur=cur->right;
            cur->right=root->right;
            root->right=root->left;
            root->left=nullptr;
        }

    }

        /*** non-recursive-implementation method 1  ***/
        void flatten(TreeNode* root) {
            TreeNode* cur=root;
            while(cur){
                if(cur->left){
                    TreeNode* pre=cur->left;
                    while(pre->right){
                        pre=pre->right;
                    }
                    pre->right=cur->right;
                    cur->right=cur->left;
                    cur->left=NULL;
                }
                cur=cur->right;
            }
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
