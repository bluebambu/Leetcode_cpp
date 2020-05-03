// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

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
// In the computer world, use restricted resource you have to generate maximum benefit is what we always want to pursue.
// For now, suppose you are a dominator of m 0s and n 1s respectively. On the other hand, there is an array with strings consisting of only 0s and 1s.
// Now your task is to find the maximum number of strings that you can form with given m 0s and n 1s. Each 0 and 1 can be used at most once. 
// Note:
// The given numbers of 0s and 1s will both not exceed 100
// The size of given string array won't exceed 600.

// Example 1:
// Input: Array = {"10", "0001", "111001", "1", "0"}, m = 5, n = 3
// Output: 4

// Explanation: This are totally 4 strings can be formed by the using of 5 0s and 3 1s, which are “10,”0001”,”1”,”0”

// Example 2:
// Input: Array = {"10", "0", "1"}, m = 1, n = 1
// Output: 2

// Explanation: You could form "10", but then you'd have nothing left. Better form "0" and "1".



// wrong code !!!!
class Solution_wrong {
public:
	// 错误的关键在于， 我想用memorization， 但是memorization没有visited 的状态！！ 
	// 这样的话就会有重复的结果！！
	// 这也是为什么一开始我觉得如果dp， 应该是个 3维的dp.....
	// 看来 dfs+memorization 和 二维 dp 做法比较还是麻烦了很多!!!!
	int findMaxForm(vector<string>& strs, int m, int n) {
		vector<vector<int>> dp(m+1, vector<int>(n+1, -1)); 
		set<int> visited;
		return helper(strs, m, n, dp, visited); 
	}

	int helper(vector<string>& strs, int m, int n, vector<vector<int>>& dp, set<int>& visited){
		if (m == 0 && n == 0)
			return 0; 
		if (dp[m][n]!=-1)
			return dp[m][n]; 

		int res = 0; 
		for (int i=0; i<strs.size(); ++i){
			if (visited.count(i)!=0)
				continue;
			int ones = 0, zeros = 0; 
			for (auto c : strs[i]) c == '0' ? ++zeros : ++ones; 
			if (m<zeros || n<ones)
				continue;
			visited.insert(i); 
			res = max(res, helper(strs, m - zeros, n - ones, dp, visited) + 1); 
			visited.erase(i); 
		}
		dp[m][n] = res; 
		return res; 
	}
};


// 是个二维的背包问题， 
// memory limit reached, but the essentials are here. 
class Solution {
public:
	int findMaxForm(vector<string>& strs, int m, int n) {
		int len = strs.size(); 

		vector<vector<vector<int>>> dp(len + 1,
			vector<vector<int>>(m + 1,
			vector<int>(n + 1, 0))); 

		for (int i = 0; i < len; ++i){
			int ones = 0, zeroes = 0;
			for (auto c : strs[i]){
				if (c == '0')
					++zeroes;
				else
					++ones; 
			}
			// 这里如果用 (c == '0') ? ++zeros : ++ones， 括号是必须的！！ a?b:c 优先级最低！！

			cout << zeroes << " " << ones << endl; 
			
			// j, k need to start from 0, cuz (1,0) (0,1) can also be a solution! 
			// To update (x,0) (0,x), we also need the if()else() conditions below. 
			for (int j = 0; j < m + 1; ++j){
				for (int k = 0; k < n + 1; ++k){
					// j & k should not start from 'zeros' and 'ones' , cuz for 
					// j & k < zeros, ones, it need to be same as previous level
					if (j >= zeroes && k >= ones){
						dp[i + 1][j][k] = max(dp[i][j][k], dp[i][j - zeroes][k - ones] + 1);
					}
					else
						dp[i + 1][j][k] = dp[i][j][k]; 
				}
			}
			prt2Layer(dp[i + 1]); 
		}

		// for (auto a : dp){
		// 	for (auto b : a){
		// 		for (auto c : b){
		// 			cout << c << " "; 
		// 		}
		// 		cout << endl; 
		// 	}
		// 	cout << endl << endl; 
		// }

		return dp[len][m][n]; 
	}
};


class Solution_op {
public:
	int findMaxForm(vector<string>& strs, int m, int n) {
		int len = strs.size();

		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); 

		for (int i = 0; i < len; ++i){
			int zeros = 0, ones = 0; 
			for (auto c : strs[i]){
				if (c == '0')
					++zeros;
				else
					++ones; 
			}

			for (int j = m; j >= 0; --j){
				for (int k = n; k >= 0; --k){
					if (j >= zeros && k >= ones)
						dp[j][k] = max(dp[j][k], dp[j - zeros][k - ones] + 1);
				}
			}
		}

		return dp[m][n]; 
	}
};

class Solution4 {
public:
	int findMaxForm(vector<string>& strs, int m, int n) {
		int a = strs.size(); 
		vector<vector<vector<int>>> dp(a + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0))); 
		vector<vector<int>> proc; 
		for (auto s : strs){
			int ones = 0; 
			for (auto c : s)
				if (c == '1')
					++ones; 
			proc.push_back({ ones, int(s.size()) - ones }); 
		}
		// dp[i][j][k] = max( dp[i-1][j][k], dp[i-1][j-zeros(i-1)][k-ones(i-1)] + 1 )
		for (int i = 1; i <= a; ++i){
			for (int j = 0; j <= m; ++j){
				for (int k = 0; k <= n; ++k){
					vector<int>& cur = proc[i - 1]; 
					if (k >= cur[0] && j >= cur[1])
						dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j - cur[1]][k - cur[0]] + 1);
					// these 2 lines are abundant
					//else if (k >= cur[0])
					//	dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j][k - cur[0]]); 
					//else if (j >= cur[1])
					//	dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j-cur[1]][k]); 
					else
						dp[i][j][k] = dp[i - 1][j][k]; 
				}
			}
		}
		return dp[a][m][n]; 
	}
};


class Solution5 {
public:
	int findMaxForm(vector<string>& strs, int m, int n) {
		int a = strs.size(); 
		vector<vector<int>> proc;
		for_each(strs.begin(), strs.end(), [&](string& s){
			int one = 0; 
			for (auto c : s)
				one += (c == '1' ? 1 : 0); 
			proc.push_back({ one, int(s.size()) - one }); 
		}); 
		
		prt2Layer(proc); 

		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

		for (int i = 0; i < a; ++i){
			for (int j = m; j >= 0; --j){
				for (int k = n; k >=0 ; --k){
					vector<int>& cur = proc[i]; 
					if (j >= cur[1] && k >= cur[0])
						dp[j][k] = max(dp[j][k], dp[j - cur[1]][k - cur[0]] + 1); 
				}
			}
		}

		return dp.back().back(); 
	}
}; 



int main(){
	Solution a;
	Solution4 a2;
	Solution5 a3;

	vector<string> b = { "10", "0", "1"}; 
	vector<string> b2 = { "10", "0001", "111001", "1", "0" }; // m = 5, n = 3

	cout << a.findMaxForm(b2,  5, 3) << endl; 
	cout << a2.findMaxForm(b2, 5, 3) << endl; 
	cout << a3.findMaxForm(b2, 5, 3) << endl; 


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

