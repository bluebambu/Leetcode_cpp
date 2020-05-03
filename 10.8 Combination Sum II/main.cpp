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


class Solution {
public:
    /// lc passed.
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> result;
        if(candidates.empty()) return result;

        vector<int> path;
        dfs(candidates, 0, 0, target, path, result);
        return result;
    }

    void dfs(vector<int>& candidates, int start, int sum, int target, vector<int>& path, vector<vector<int>>& result){
        if(sum==target){
            result.push_back(path);
            return;
        }
        for(int i=start; i<candidates.size(); ++i){
            int tmp = candidates[i];
            if(sum+tmp > target)
                return;
            sum+=tmp;
            path.push_back(tmp);
            dfs(candidates, i+1, sum, target, path, result);
            sum-=tmp;
            path.pop_back();
            while(i+1<candidates.size() && candidates[i]==candidates[i+1]) ++i; /// 在尾部去重， 不能在头部去， 参见 【1， 1， 7， 2】 => 9, 头部去重会错过 1，1，7 这个组合
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


}
