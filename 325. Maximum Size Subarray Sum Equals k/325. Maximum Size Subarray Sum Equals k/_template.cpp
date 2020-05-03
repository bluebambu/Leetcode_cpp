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
#include <string> 
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>

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


// Given an array nums and a target value k, find the maximum length of a subarray that sums to k.If there isn't one, return 0 instead.
// 
// Note:
// The sum of the entire nums array is guaranteed to fit within the 32 - bit signed integer range.
// 
// Example 1 :
// 
// Given nums = [1, -1, 5, -2, 3], k = 3,
// return 4. (because the subarray[1, -1, 5, -2] sums to 3 and is the longest)
// 
// Example 2 :
// 
// Given nums = [-2, -1, 2, 1], k = 1,
// return 2. (because the subarray[-1, 2] sums to 1 and is the longest)
// 
// Follow Up :
// Can you do it in O(n) time ?




// pass, 思路是近似于 range sum query， subarray可以看做是 累积和 之差。 
// 想达到 O(n) , 需要思考如何将 (i,j) 穷举变成 On。 类似于 2 sum， hashtable是一种途径。 
class Solution {
public:
	int maxSubArrayLen(vector<int>& nums, int k) {
		if (nums.empty())
			return 0;
		unordered_map<int, int> m;
		m[0] = -1;
		int sum = 0;
		int res = 0;

		for (int i = 0; i < nums.size(); ++i){
			sum += nums[i];
			if (m.find(sum) == m.end())
				m[sum] = i;
			if (m.find(sum - k) != m.end())
				res = max(res, i - m[sum - k]);
		}
		return res;
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

	vector<int> b{-2, -1, 2, 1};
	cout << a.maxSubArrayLen(b, 1); 


}

