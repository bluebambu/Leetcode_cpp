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
class Solution {
public:
    /// O(n) 贪心解
    /// 而这道题，需要求的是最少的步数。因此需要添加step变量记录最少步数。至于什么时候step需要加1？
    /// 答案是当前的i超过了前一步的最远位置。所以引入last变量记录上一步能到达的最远位置。reach、step、last的初始值均为0。
    /// 当遍历到i的时候，如果i超过了last（即上一步能到达的最远位置），说明步数需要加1（即step++），此时仍需要更新last为当前最远位置reach。
    /// 全程只需遍历1次数组，而且空间复杂度为常量。
    //
    int jump(vector<int>& nums) {
        if(nums.empty()) return 0;

        int cur=0, nextfar=0, step=0;
        for(int i=0; i<nums.size() && i<=nextfar; ++i){
            if(i>cur){
                ++step;
                cur=nextfar;
            }
            nextfar = max(nextfar, nums[i]+i);
        }
        return step;
    }

    /// DP 解， TLE
    int jump(vector<int>& nums) {
        int n=nums.size();

        vector<int> dp(n, 0);

        for(int i=1; i<n; ++i){
            for(int j=0; j<i;++j){
                if(j+nums[j]>=i){
                    dp[i] = (dp[i]==0 ? dp[j]+1 : min(dp[i], dp[j]+1));
                }
            }
        }
        return dp[n-1];
    }
};

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
