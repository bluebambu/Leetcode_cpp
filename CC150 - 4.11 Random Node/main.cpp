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
    int sizeDown;

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
                cout<<front->sizeDown<<" ";
                q.push(front->left);
                q.push(front->right);
            }
        }
        cout<<endl;
    }
}


class BST  /// BST with subtree size.
{
    TreeNode* root;
public:
    BST():root(nullptr) {}

    TreeNode* R(){return root; }


    bool insert(int x){
        return insert(root, x);
    }
    bool insert(TreeNode*& root, int x){
        if(!root){
            root=new TreeNode(x);
            root->sizeDown=1;
            return true;
        }
        if(root->val == x)
            return false;
        else if(root->val > x){
            bool tmp=insert(root->left, x);
            if(tmp)
                root->sizeDown+=1;
            return tmp;
        }
        else if(root->val < x){
            bool tmp=insert(root->right, x);
            if(tmp)
                root->sizeDown+=1;
            return tmp;
        }
    }



};

int main()
{
    BST a;

    for(int i=0; i<50; ++i)
        a.insert(abs(i-20));

    print(a.R());


}
