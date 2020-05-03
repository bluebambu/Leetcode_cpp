// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <functional>
#include <numeric>
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
//  In a given array nums of positive integers, find three non-overlapping subarrays with maximum sum.

// Each subarray will be of size k, and we want to maximize the sum of all 3*k entries.
// Return the result as a list of indices representing the starting position of each interval 
// (0-indexed). If there are multiple answers, return the lexicographically smallest one.

// Example:
// Input: [1,2,1,2,6,7,5,1], 2
// Output: [0, 3, 5]
// Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
// We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.

// Note:
// nums.length will be between 1 and 20000.
// nums[i] will be between 1 and 65535.
// k will be between 1 and floor(nums.length / 3).


// TLE, ugly implementation
class Solution {
public:
	vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int sz) {
		int n = nums.size();
		auto r = helper(nums, n, 3, sz); 
		return r.second; 
	}

	pair<int, vector<int>> helper(vector<int>& nums, int n, int k, int sz){
		if (n < sz*k || k < 0)
			return { INT_MIN, {} };
		if (k == 0)
			return{ 0, {} };

		if (n == sz && k == 1){
			return{ accumulate(nums.begin(), nums.begin()+sz, 0), { 0 }};
		}
		
		auto t2 = helper(nums, n - sz, k - 1, sz); 
		auto t1 = helper(nums, n - 1, k, sz); 

		int ttt = accumulate(nums.begin()+n-sz, nums.begin()+n, 0); 

		int dpN2 = t2.first + ttt; 
		int dpN1 = t1.first; 
		if (dpN2 > dpN1){
			t2.second.push_back(n - sz); 
			return{ dpN2, t2.second }; 
		}
		else{
			return{ dpN1, t1.second }; 
		}
	}
};


// pass AC, but slow
class Solution2 {
public:
	vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int sz) {
		int n = nums.size(); 
		vector<int> cumsum(n + 1, 0); 
		int cum = 0; 
		for (int i = 1; i < n + 1; ++i){
			cum += nums[i-1]; 
			cumsum[i] = cum; 
		}
		
		typedef pair<int, vector<int>> PIV; 
		vector<vector<PIV>> dp(n + 1, vector<PIV>(4, { 0, {} })); 
		// for (int i = 0; i < n + 1; ++i)
		// 	dp[i][0] = { 0, {} }; 
		// for (int j = 0; j < 4; ++j)
		// 	dp[0][j] = { 0, {} }; 

		// dp[i][j] = max( dp[i-sz][j-1]+cumsum(), dp[i-1][j] )
		for (int j = 1; j < 4; ++j){
			for (int i = j*sz; i < n + 1; ++i){
				int v1 = dp[i - sz][j - 1].first + (cumsum[i] - cumsum[i - sz]); 
				int v2 = dp[i - 1][j].first; 
				if (v1 > v2){
					dp[i][j] = { v1, dp[i - sz][j - 1].second }; 
					dp[i][j].second.push_back(i - sz); 
				}
				else{
					dp[i][j] = dp[i - 1][j]; 
				}
			}
		}

		return dp.back().back().second; 
	}
};







int main(){
	Solution2 a; 

	vector<int> b = { 7, 13, 20, 19, 19, 2, 10, 1, 1, 19 }; 

	prt1Layer(a.maxSumOfThreeSubarrays(b, 3)); 


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

