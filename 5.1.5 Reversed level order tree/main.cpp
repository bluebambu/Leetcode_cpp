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


class Solution
{
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> result;
        int size=0;
        lvl(root, 1, result, size);
        return result;
    }

    void lvl(TreeNode* root, int level, vector<vector<int>>& result, int& size){
        if(!root) return;

        if(level > result.size())
            {result.emplace(result.begin(), vector<int>());++size;}

        result[size-level].push_back(root->val);
        lvl(root->left, level+1, result, size);
        lvl(root->right, level+1, result, size);
    }
};


int main()
{
    Solution a;

    TreeNode* tree = new TreeNode(3,new TreeNode(6, new TreeNode(9), new TreeNode(1)),new TreeNode(4, new TreeNode(3), new TreeNode(4)));
    /*      3
        6       4
     9    1   3    4

    */

    auto b = a.LevelOrder6(tree);

    for(auto i:b)
        {for(auto j:i)
            cout<<j<<" ";
         cout<<endl;
        }
}
