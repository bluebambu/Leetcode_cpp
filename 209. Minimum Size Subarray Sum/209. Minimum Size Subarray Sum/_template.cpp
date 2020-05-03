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


// Given an array of n positive integers and a positive integer s, find the minimal length of a 
// contiguous subarray of which the sum ¡Ý s.If there isn't one, return 0 instead.
// 
// For example, given the array[2, 3, 1, 2, 4, 3] and s = 7,
// the subarray[4, 3] has the minimal length under the problem constraint.
// 
// click to show more practice.
// More practice :
// 
// If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log n).


// ¹Ø¼ü´Ê£º positive integers£¡£¡ ÖØÒª£¡

// passed
class Solution {
public:
	int minSubArrayLen(int target, vector<int>& nums) {
		if (nums.empty())
			return 0;
		int left = 0, right = 1, sum = nums[0], res = nums.size();
		while (!(right == nums.size() && sum < target)){
			while (sum < target && right < nums.size()){
				sum += nums[right];
				++right;
			}
			res = min(res, right - left); 
			while (sum >= target && left < right){
				res = min(res, right - left);
				sum -= nums[left];
				++left;
			}
		}
		return left==0? 0 : res; 
	}													 
};



int main()
{
	Solution a;


	vector<int> b{ 2, 3, 1, 2, 4, 5 };
	vector<int> c{ 1, 1 };
	
	cout << a.minSubArrayLen(3, c); 

	

}

