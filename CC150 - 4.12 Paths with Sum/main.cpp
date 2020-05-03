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

/// 记录路径。 每个节点都对上面的路径进行从尾到头的加和，如果有等于target的则记录进result.
class Solution
{
public:
    vector<vector<int>> pathSum(TreeNode* root, int target){
        vector<vector<int>> result;
        if(!root) return result;
        vector<int> path;
        pathSum(root, target, path, result);
        return result;
    }
    void pathSum(TreeNode* node, int target, vector<int>& path, vector<vector<int>>& result){
        if(!node)
            return;
        path.push_back(node->val);
        int curSumUp=0;
        for(int i=path.size()-1; i>=0; --i){
            curSumUp += path[i];
            if(curSumUp == target){
                result.push_back(vector<int>(path.begin()+i, path.end()));
            }
        }
        pathSum(node->left, target, path, result);
        pathSum(node->right, target, path, result);
        path.pop_back();
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

    auto b = a.pathSum(tree, 7);

    for(auto i:b)
        for(auto j:i)
            cout<<j<<" ";


}
