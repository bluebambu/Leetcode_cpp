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


class Solution
{
public:
	int rob(vector<int>& nums) {
		if (nums.empty())
			return 0; 
		if (nums.size() == 1)
			return nums[0]; 

		int n = nums.size(); 
		int cur = nums[0], prev1 = 0, prev2=0; 
		int res1 = nums[0], res2 = nums[1]; 

		for (int i = 2; i <= n-1; ++i){
			int tmp = cur; 
			cur = max(prev1, prev2) + nums[i - 1]; 
			prev2 = prev1; 
			prev1 = tmp; 
			res1 = max(res1, cur); 
		}

		cur = nums[1], prev1 = 0, prev2 = 0; 

		for (int i = 3; i <= n; ++i){
			int tmp = cur;
			cur = max(prev1, prev2) + nums[i - 1];
			prev2 = prev1;
			prev1 = tmp;
			res2 = max(res2, cur);
		}

		return max(res1, res2); 
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
		if (n == 2)
			return max(nums[0], nums[1]); 
		return max(rob(nums, 0, n - 2), rob(nums, 1, n - 1)); 
	}

	int rob(vector<int>& nums, int start, int end){
		int last = nums[start], cur = max(nums[start], nums[start + 1]); 
		for (int i = start + 2; i <= end; ++i){
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

