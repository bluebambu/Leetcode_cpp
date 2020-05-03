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
    TreeNode* MinBST(vector<int> v){
        return MinBST(v, 0, v.size()-1);
    }
    TreeNode* MinBST(vector<int> v, int i, int j){
        if(i>j)
            return nullptr;
        int mid = i+(j-i)/2;
        TreeNode *node = new TreeNode(v[mid]);
        node->left = MinBST(v, i, mid-1);
        node->right = MinBST(v, mid+1, j);
        return node;
    }

};

int main()
{
    Solution a;

    auto b = a.MinBST(vector<int>{1,3,5,7,8,12,15,17,19});

    print(b);


}
