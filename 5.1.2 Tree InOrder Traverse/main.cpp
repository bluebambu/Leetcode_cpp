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
////// morris, leetcode passed //////////////
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        TreeNode* cur=root, *prev;

        while(cur){
            TreeNode* left = cur->left;
            if(!left){
                result.push_back(cur->val);
                prev=cur;
                cur=cur->right;
            }else{
                while(left->right!=nullptr && left->right!=cur){
                    left=left->right;
                }

                if(left->right==nullptr){
                    left->right=cur;
                    cur=cur->left;
                }else{
                    left->right=nullptr;
                    result.push_back(cur->val);
                    cur=cur->right;
                }
            }
        }
        return result;
    }

////////////////////////////////////////

};

int main()
{
    Solution a;

    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */

    auto b = a.InOrderTraverse2(tree);

    for(auto i:b)
        cout<<i<<" ";
}
