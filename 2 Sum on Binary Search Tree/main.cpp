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
    bool TwoSumBST(TreeNode* root, int target){
        if(!root) return false;
        vector<TreeNode*> left, right;
        TreeNode *l=root, *r=root;

        while(l){
            left.push_back(l);
            l=l->left;
        }

        while(r){
            right.push_back(r);
            r=r->right;
        }

        while(left.back() != right.back()){
            l=left.back();
            r=right.back();
            int tmp = l->val + r->val;
            if( tmp ==target)
                return true;
            else if(tmp > target){
                right.pop_back();
                if(r->left){
                    r=r->left;
                    while(r){
                        right.push_back(r);
                        r=r->right;
                    }
                }
            }else{
                left.pop_back();
                if(l->right){
                    l=l->right;
                    while(l){
                        left.push_back(l);
                        l=l->left;
                    }
                }
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
    cout<<a.TwoSumBST(tree, 17);

}
