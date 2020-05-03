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

struct TreeNode;
void print();

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
        auto tmp = q.front();
        cout<<tmp->val<<" ";
        if(tmp->left) q.push(tmp->left);
        if(tmp->right) q.push(tmp->right);
        q.pop();
    }
}



class Solution
{
public:
    ////////// leetcode passed //////////////////
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        if(!root) return nullptr;

        stack<TreeNode*> st;
        TreeNode* cur=root;
        TreeNode* result=nullptr;
        bool found=false;

        while(!st.empty() || cur){
            while(cur){
                st.push(cur);
                cur=cur->left;
            }

            TreeNode* node=st.top();
            st.pop();

            if(found) return node;
            if(node==p) found=true;

            if(node->right) cur=node->right;
        }

        return nullptr;
    }

    ///
    TreeNode* inorderSuccessor2(TreeNode* root, TreeNode* p) {
        if(!root) return nullptr;
        TreeNode* cur=root;
        bool found=false;

        while(cur){
            TreeNode* node=cur->left;
            if(node){
                while(node->right && node->right!=cur)
                    node=node->right;
                if(node->right==cur){
                    node->right=nullptr;
                }else{
                    node->right=cur;
                    cur=cur->left;
                    continue;
                }
            }
            if(found) return cur;
            if(cur==p) found=true;

            cur=cur->right;
        }
        return nullptr;
    }

};


int main()
{
	Solution a;
//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* p;
    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1, p=new TreeNode(11), nullptr),
                                                    new TreeNode(4)),
                                    new TreeNode(8, new TreeNode(7),
                                                    new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */

    cout<<a.inorderSuccessor2(tree, p)->val;

}
