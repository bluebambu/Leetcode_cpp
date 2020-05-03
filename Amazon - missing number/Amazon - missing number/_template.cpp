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



// [6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18]   sz = 12			    
// find the missing 15. Can you do better than traversing the whole array
// 
// [12, ... 18]
// [14, .. 18]
// [14, 16]   final case


class Solution
{
public:
	int missing(vector<int>& nums){
		int left = 0, right = nums.size() - 1;

		while (1){
			int mid = left + (right - left) / 2;

			if (left + 1 == right) // && nums[right] - nums[left] > 1)
				break;
			else if (nums[left] + (mid - left) == nums[mid])
				left = mid;
			else
				right = mid;
		}

		return (nums[left] + nums[right]) / 2;
	}

};

// what if there are multiple missing integers in the range?? recursion to 
// conduct binary search on both side. 
// vector<int> b = { 1,2,4,5,6,9,10 }; 
//
// output is {3, 7, 8}
// 
class Solution2 {
public:
	vector<int> missing(vector<int>& nums){
		vector<int> res; 
		dfs(nums, 0, nums.size() - 1, res);
		return res; 
	}

	void dfs(vector<int>& nums, int left, int right, vector<int>& res){
		if (left + 1 == right){
			if (nums[right] - nums[left] > 1)
				for (int i = nums[left] + 1; i < nums[right]; ++i)
					res.push_back(i); 
			return; 
		}

		int mid = left + (right - left) / 2; 

		if (nums[left] + (mid - left) != nums[mid])
			dfs(nums, left, mid, res);
		if (nums[mid] + (right - mid) != nums[right])
			dfs(nums, mid, right, res); 

	}
};

int main()
{
	Solution2 a;

	vector<int> b = { 1,2,4,5,6,9,10 }; 

	auto c = a.missing(b); 

	for (auto i : c)
		cout << i << " "; 


}

