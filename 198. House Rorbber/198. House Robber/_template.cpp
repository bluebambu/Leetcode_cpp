// _template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }


struct TreeNode
{
	TreeNode(int a) :val(a), left(nullptr), right(nullptr) {}
	TreeNode(int a, TreeNode* x, TreeNode* y) :val(a), left(x), right(y) {}
	TreeNode() :val(0), left(nullptr), right(nullptr) {}

	int val;
	TreeNode *left;
	TreeNode *right;

};

void print(TreeNode* root){
	queue<TreeNode*> q;
	q.push(root);

	while (q.size()){
		int n = q.size();
		for (int i = 0; i<n; ++i){
			TreeNode* front = q.front();
			q.pop();

			if (!front)
				cout << "# ";
			else{
				cout << front->val << " ";
				q.push(front->left);
				q.push(front->right);
			}
		}
		cout << endl;
	}
}

// passed. 
class Solution
{
public:
	int rob(vector<int>& nums) {
		if (nums.empty())
			return 0; 

		int n = nums.size(); 
		vector<int> dp(n, 0); 
		int res = nums[0]; 

		for (int i = 0; i < n; ++i){
			dp[i] += nums[i] + max(i - 2 >= 0 ? dp[i - 2] : 0, i - 3 >= 0 ? dp[i - 3] : 0); // dp[i] 只需要 dp[i-2] 和 dp[i-3] 的结果
			res = max(res, dp[i]); 
		}

		return res; 
	}

};



class Solution {
public:
	int rob(vector<int>& nums) {
		int n = nums.size(); 
		if (n == 0)
			return 0; 
		if (n == 1)
			return nums.back(); 

		int last = nums[0], cur = max(nums[0], nums[1]); 
		for (int i = 2; i < n; ++i){
			int llast = last; 
			last = cur; 
			cur = max(cur, llast + nums[i]); 
		}
		return cur; 
	}
};


int main()
{
	Solution a;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/

	a.flatten(tree);


}

