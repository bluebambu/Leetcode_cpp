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
    /////////// passed //////////
    vector<vector<int>> findL(TreeNode* root){
        vector<vector<int>> result;
        f(root, result);
        return result;
    }

    int f(TreeNode* root, vector<vector<int>>& result){
        if(!root) return 0;
        int left = f(root->left, result);
        int right = f(root->right, result);

        int curlvl = max(left, right)+1;
        if(result.size()<curlvl)
            result.push_back(vector<int>());
        result[curlvl-1].push_back(root->val);

        return curlvl;
    }

};


int main()
{
	Solution a;

//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1, new TreeNode(8), new TreeNode(11)),
                                                    new TreeNode(4)),
                                    new TreeNode(8, new TreeNode(7),
                                                    new TreeNode(9)));
    /*      6
        3       8
     1    4   7    9

    */

    auto b = a.findL(tree);

    for(auto i:b){
        for(auto j:i)
            cout<<j<<" ";
        cout<<endl;
    }


}
