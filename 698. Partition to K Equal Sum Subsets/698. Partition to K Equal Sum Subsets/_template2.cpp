// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <numeric>
#include <functional>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a < b ? a : b; }


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
		for (int i = 0; i < n; ++i){
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


template <typename C>
void prt1Layer(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void prt2Layer(C v){
	for (auto i : v){
		for (auto j : i)
			cout << j << " ";
		cout << endl; 
	}
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
// Given an array of integers nums and a positive integer k, find 
// whether it's possible to divide this array into k non-empty subsets whose sums are all equal.

// Example 1:

// Input: nums = [4, 3, 2, 3, 5, 2, 1], k = 4
// Output: True
// Explanation: It's possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.

// Note:
// 1 <= k <= len(nums) <= 16.
// 0 < nums[i] < 10000.


// pass AC
class Solution {
public:
	bool canPartitionKSubsets(vector<int>& nums, int k) {
		int sum = accumulate(nums.begin(), nums.end(), 0); 
		if (sum%k)
			return false; 
		vector<bool> visited(nums.size(), false); 
		int target = sum / k; 
		return helper(nums, k, target, 0, 0, visited); 
	}

	bool helper(vector<int>& nums, int k, int target, int start, int curSum, vector<bool>& visited){
		if (k == 1)
			return true; 
		if (curSum == target)
			return helper(nums, k - 1, target, 0, 0, visited); 
		if (curSum > target)
			return false; 

		for (int i = start; i < nums.size(); ++i){
			if (visited[i] == false){
				visited[i] = true; 
				if (helper(nums, k, target, i + 1, curSum + nums[i], visited))
					return true; 
				visited[i] = false; 
			}
		}
		return false;
	}
};








int main(){
	Solution a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/



	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

