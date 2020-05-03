// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <numeric>
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

template <typename T>
void vprt(vector<T> v){
	for (auto i : v)
		cout << v << " ";
	cout << endl;
}

template <typename T>
void vvprt(vector<vector<T>> v){
	for (auto i : v){
		for (auto j : i){
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <typename C>
void setprt(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
// You are given a list of non - negative integers, a1, a2, ..., an, and a target, S.Now you have 
// 2 symbols + and - .For each integer, you should choose one from + and - as its new symbol.

// Find out how many ways to assign symbols to make sum of integers equal to target S.
// Example 1:
// Input : nums is[1, 1, 1, 1, 1], S is 3.
// Output : 5
// 	 Explanation :

// 				 -1 + 1 + 1 + 1 + 1 = 3
// 				 + 1 - 1 + 1 + 1 + 1 = 3
// 				 + 1 + 1 - 1 + 1 + 1 = 3
// 				 + 1 + 1 + 1 - 1 + 1 = 3
// 				 + 1 + 1 + 1 + 1 - 1 = 3

// 				 There are 5 ways to assign symbols to make the sum of nums be target 3.

// 			 Note:
// 		The length of the given array is positive and will not exceed 20.
// 			The sum of elements in the given array will not exceed 1000.
// 			Your output answer is guaranteed to be fitted in a 32 - bit integer.


// dfs, pass AC, but too slow. 44% 
class Solution {
public:
	int findTargetSumWays(vector<int>& nums, int S) {
		unordered_map<int, unordered_map<int, int>> visited; 
		
		return helper(nums, nums.size(), S, visited); 
	}

	int helper(vector<int>& nums, int sz, int target, 
		unordered_map<int, unordered_map<int, int>>& visited){
		
		if (visited.count(sz) && visited[sz].count(target)){
			return visited[sz][target];
		}

		if (sz == 0){
			return target == 0 ? 1 : 0; 
		}

		visited[sz][target] = helper(nums, sz - 1, target - nums[sz - 1], visited) +
			helper(nums, sz - 1, target + nums[sz - 1], visited); 

		cout << sz << " " << target << " " << visited[sz][target] << endl; 

		return visited[sz][target]; 
	}
};


// dfs is slow because it is power(2,n) complexity. 
// DP will be faster, complexity is O(N*target)
// **** 这个思路不正确， 也很不好！！！
class Solution2 {
public:
	int findTargetSumWays(vector<int>& nums, int S) {
		int n = nums.size();
		int sum = accumulate(nums.begin(), nums.end(), 0);
		vector<unordered_map<int, int>> dp(n + 1);

		dp[1][nums[0]] = 1;
		dp[1][-nums[0]] = 1;
		for (int i = 2; i < n + 1; ++i){
			for (int j = -sum; j <= sum; ++j){
				// dp[i][j]
				dp[i][j] = dp[i - 1][j - nums[i - 1]] + dp[i - 1][j + nums[i - 1]];
			}
		}
		return dp[n][S];
	}
};


class Solution3 {
public:
	int findTargetSumWays(vector<int>& nums, int S) {
		int n = nums.size(); 
		vector<unordered_map<int, int>> dp(n + 1); 

		dp[0][0] = 1;
		for (int i = 1; i <= n; ++i){
			for (auto& j : dp[i - 1]){
				int target = j.first, cnt = j.second; 
				dp[i][target + nums[i - 1]] += cnt; 
				dp[i][target - nums[i - 1]] += cnt; 
			}
		}
		return dp[n][S];
	}
};


class Solution4 {
public:
	int findTargetSumWays(vector<int>& nums, int S) {
		// dp[i][n] = dp[i-1][n-nums[i]] + dp[i-1][n+nums[i]]
		unordered_map<int, unordered_map<int, int>> dp; 

		return dfs(nums, nums.size(), S, dp); 
	}

	int dfs(vector<int>& nums, int i, int S, unordered_map<int, unordered_map<int, int>>& dp){
		if (i < 1)
			return 0; 
		if (i == 1 && (S == nums[0] || S == -nums[0]))
			return 1; 

		int res = dfs(nums, i - 1, S - nums[i - 1], dp) +
			dfs(nums, i - 1, S + nums[i - 1], dp); 
		dp[i][S] = res; 
		return res; 
	}
}; 

int main()
{
	Solution4 a;
	vector<int> b{ 1, 1, 1, 1, 1};
	cout << a.findTargetSumWays(b, 3) << endl;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/


}

