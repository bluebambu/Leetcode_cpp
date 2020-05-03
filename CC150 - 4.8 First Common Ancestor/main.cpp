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
    TreeNode* CommonAncest(TreeNode* root, int a, int b){
        TreeNode* CA=nullptr;
        CommonAncest(root, a, b, CA);
        return CA;
    }
    bool CommonAncest(TreeNode*root, int a, int b, TreeNode*& CA){
        if(!root)
            return false;

        bool left = CommonAncest(root->left, a, b, CA);
        bool right = CommonAncest(root->right, a, b, CA);

        if(left && right)
            CA = root;
        else if(left || right){
            if(root->val ==a || root->val == b)
                CA = root;
            return true; /// 只要子树里面有匹配，就返回true ！！
        }else{ // (!left && !right)
            if(root->val ==a || root->val == b){
                if(a==b) /// in case a和b相等
                    CA = root;
                return true;
            }
        }
        return false;

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

    cout<<a.CommonAncest(tree, 3, 9)->val ;


}
