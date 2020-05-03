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
//
///Find the contiguous subarray within an array (containing at least one number) which has the largest product.
//
///For example, given the array [2,3,-2,4],
///the contiguous subarray [2,3] has the largest product = 6.

class Solution {
public:
    ///////// leetcode passed ///////////////////
    int maxProduct(vector<int>& nums) {
        if(nums.empty()) return 0;
        int n=nums.size();
        int result=nums[0];
        vector<int> maxp(n, 0), minp(n, 0);

        maxp[0]=minp[0]=nums[0];

        for(int i=1; i<nums.size(); ++i){
            maxp[i] = max(max(nums[i], maxp[i-1]*nums[i]), minp[i-1]*nums[i]);
            minp[i] = min(min(nums[i], maxp[i-1]*nums[i]), minp[i-1]*nums[i]);
            result = max(result, maxp[i]);
        }

        return result;
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
