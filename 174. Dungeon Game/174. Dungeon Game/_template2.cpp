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
// The demons had captured the princess(P) and imprisoned her in the bottom - right corner of a dungeon.The dungeon consists of M x N rooms laid out in a 2D grid.Our valiant knight(K) was initially positioned in the top - left room and must fight his way through the dungeon to rescue the princess.
// The knight has an initial health point represented by a positive integer.If at any point his health point drops to 0 or below, he dies immediately.
// Some of the rooms are guarded by demons, so the knight loses health(negative integers) upon entering these rooms; other rooms are either empty(0's) or contain magic orbs that increase the knight's health(positive integers).
// In order to reach the princess as quickly as possible, the knight decides to move only rightward or downward in each step.

// Write a function to determine the knight's minimum initial health so that he is able to rescue the princess.
// For example, given the dungeon below, the initial health of the knight must be at least 7 if he follows the optimal path RIGHT->RIGHT->DOWN->DOWN.
// -2  -3  3
// -5  -10  1
// 10   30  -5 (P)

// Notes:
// The knight's health has no upper bound.
// Any room can contain threats or power - ups, even the first room the knight enters and the bottom - right room where the princess is imprisoned.

// 从前往后推，比想象的难很多！ 这个解答是错误的，例子在下面：
// Input:
// [[1, -3, 3], 
// [0, -2,  0], 
// [-3, -3, -3]]
// Output : 5
// Expected : 3
// 走到d[1][2]的时候， 上方是(4, 3), 左方是(1,2), 貌似应该选择左方路线，实际上要选择上方路线！！
// 这也说明，不走到底，无法了解最后的情况！！！！ 所以如果要从左上角开始，必须DFS到底才行！！！！
// 因此， dp解法从右下开始， 是合理的!!
class Solution {
public:
	struct status{
		int cur_health;
		int added;
		status(){}
		status(int x, int y) :cur_health(x), added(y) {}
		status(const status& other):cur_health(other.cur_health), added(other.added) {}
		status& operator=(const status& other){
			cur_health = other.cur_health; 
			added = other.added; 
			return *this; 
		}
	};

	status comp(status pre, int cur_dgn){
		int temp = pre.cur_health + cur_dgn; 
		if (temp > 0)
			return status(temp, pre.added);
		else
			return status(1, pre.added + (1 - temp)); 
	}

	status less_added(const status& a, const status& b){
		return (a.cur_health - a.added < b.cur_health - b.added) ? b : a;
	}

	int calculateMinimumHP(vector<vector<int>>& dungeon) {
		if (dungeon.empty() || dungeon[0].empty())
			return 0; 

		int n = dungeon.size(), m = dungeon[0].size(); 
		vector<vector<status>> dp(n, vector<status>(m)); 

		// start calculating dp[i][j]
		dp[0][0] = dungeon[0][0] > 0 ? status(dungeon[0][0]+1, 1) : status(1, 1 - dungeon[0][0]); 

		for (int i = 1; i < m; ++i){
			dp[0][i] = comp(dp[0][i - 1], dungeon[0][i]); 
		}
		for (int i = 1; i < n; ++i){
			dp[i][0] = comp(dp[i - 1][0], dungeon[i][0]); 
		}
		for (int i = 1; i < n; ++i){
			for (int j = 1; j < m; ++j){
				dp[i][j] = less_added(comp(dp[i - 1][j], dungeon[i][j]), comp(dp[i][j - 1], dungeon[i][j])); 
			}
		}

		return dp[n - 1][m - 1].added; 
	}
};

// wrong ans!!!
class Solution2 {
public:
	int calculateMinimumHP(vector<vector<int>>& dungeon) {
		if (dungeon.empty() || dungeon[0].empty())
			return 0; 

		int n = dungeon.size(), m = dungeon.at(0).size(); 

		vector<vector<int>> dp(n, vector<int>(m, 0)); 

		dp[n - 1][m - 1] = (dungeon.back().back()) >0 ?  1 : dungeon.back().back() ;  // caution! positive d[end][end] only needs 1 health!! 

		for (int i = n - 2; i >= 0; --i)
			dp[i][m - 1] = comp(dp[i + 1][m - 1], dungeon[i][m - 1]); 
		for (int j = m - 2; j >= 0; --j)
			dp[n - 1][j] = comp(dp[n - 1][j + 1], dungeon[n - 1][j]); 
		for (int i = n - 2; i >= 0; --i){
			for (int j = m - 2; j >= 0; --j){
				dp[i][j] = min(comp(dp[i + 1][j], dungeon[i][j]), comp(dp[i][j + 1], dungeon[i][j])); 
			}
		}

		return dp[0][0]; 
	}

	int comp(int pre, int cur_d){
		int tmp = pre - cur_d; 
		if (tmp < 1)
			tmp = 1; 
		return tmp; 
	}
};

// wrong answer!!!!!
class Solution3 {
public:
	int calculateMinimumHP(vector<vector<int>>& dungeon) {
		int n = dungeon.size(), m = dungeon[0].size(); 
		vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(2, -100))); 
		for (int i = 1; i <= n; ++i){
			for (int j = 1; j <= m; ++j){
				if (i == 1 && j == 1){
					dp[1][1] = { dungeon[0][0], min(dungeon[0][0], 0) }; 
					continue;
				}
				vector<int>& up = dp[i - 1][j], &left = dp[i][j - 1];
				int cur = dungeon[i - 1][j - 1];
				int cand1x = up[0] + cur, cand1y = min(cand1x, up[1]),
					cand2x = left[0] + cur, cand2y = min(cand2x, left[1]); 
				dp[i][j] = ((cand1y >cand2y || (cand1y==cand2y && cand1x > cand2x)) ? vector<int>({ cand1x, cand1y }) : vector<int>({ cand2x, cand2y })); 
			}
		}

		int final = dp.back().back().at(1); 

		for (auto x : dp) {
			for (auto y : x)
				cout << "[" << y[0] << ", " << y[1] << "] "; 
			cout << endl; 
		}

		if (final < 0)
			return -1 * final + 1;
		else
			return final == 0 ? 1 : 0; 
	}
};

// some forward-DP solution from web. 
//class Solution4 {
//public:
//	typedef vector<int> vector; 

//	int calculateMinimumHP(vector<vector>& dungeon) {
//		if (dungeon.empty()) return 0;
//		long long row = dungeon.size();
//		long long col = dungeon[0].size();
//		vector low(col), up(col), low_cur(col), up_cur(col);
//		low_cur[0] = low[0] = up[0] = up_cur[0] = dungeon[0][0];
//		for (long long i = 1; i < col; ++i) {
//			up_cur[i] = low_cur[i] = up_cur[i - 1] + dungeon[0][i];
//			up[i] = low[i] = min(up[i - 1], up_cur[i]);
//		}
//		for (long long i = 1; i < row; ++i) {
//			up_cur[0] += dungeon[i][0];
//			low_cur[0] += dungeon[i][0];
//			up[0] = low[0] = min(up_cur[0], up[0]);
//			for (long long j = 1; j<col; ++j) {
//				if (min(low_cur[j] + dungeon[i][j], low[j])>min(low_cur[j - 1] + dungeon[i][j], low[j - 1])) {
//					low_cur[j] += dungeon[i][j];
//					low[j] = min(low_cur[j], low[j]);
//				}
//				else if (min(low_cur[j] + dungeon[i][j], low[j]) < min(low_cur[j - 1] + dungeon[i][j], low[j - 1])){
//					low_cur[j] = low_cur[j - 1] + dungeon[i][j];
//					low[j] = min(low[j - 1], low_cur[j]);
//				}
//				else{
//					low[j] = min(low_cur[j] + dungeon[i][j], low[j]);
//					low_cur[j] = max(low_cur[j], low_cur[j - 1]) + dungeon[i][j];
//				}
//				if (low[j] < min(up_cur[j] + dungeon[i][j], up[j])){
//					low[j] = min(up_cur[j] + dungeon[i][j], up[j]);
//					low_cur[j] = up_cur[j] + dungeon[i][j];
//				}
//				if (low[j] < min(up_cur[j - 1] + dungeon[i][j], up[j - 1])){
//					low[j] = min(up_cur[j - 1] + dungeon[i][j], up[j - 1]);
//					low_cur[j] = up[j - 1] + dungeon[i][j];
//				}
//				if (up_cur[j] > up_cur[j - 1]) {
//					up_cur[j] += dungeon[i][j];
//					up[j] = min(up[j], up_cur[j]);
//				}
//				else if (up_cur[j] < up_cur[j - 1]){
//					up_cur[j] = up_cur[j - 1] + dungeon[i][j];
//					up[j] = min(up_cur[j], up[j - 1]);
//				}
//				else{
//					up_cur[j] += dungeon[i][j];
//					up[j] = min(max(up[j], up[j - 1]), up_cur[j]);
//				}
//			}
//		}
//		int ans = max(low[col - 1], up[col - 1]);
//		return ans > -1 ? 1 : 1 - ans;
//	}
//};


class Solution5 {
public:
	int calculateMinimumHP(vector<vector<int>>& dungeon) {
		int n = dungeon.size(), m = dungeon[0].size(); 
		vector<vector<int>> dp(n, vector<int>(m, 0)); 

		for (int i = n - 1; i >= 0; --i){
			for (int j = m - 1; j >= 0; --j){
				if (i == n - 1 && j == m - 1)
					dp[i][j] = max(1 - dungeon[i][j], 1);
				else if (i == n - 1)
					dp[i][j] = max(dp[i][j + 1] - dungeon[i][j], 1);
				else if (j == m - 1)
					dp[i][j] = max(dp[i + 1][j] - dungeon[i][j], 1);
				else
					dp[i][j] = min(max(dp[i][j + 1] - dungeon[i][j], 1), max(dp[i + 1][j] - dungeon[i][j], 1)); 
			}
		}

		//prt2Layer(dungeon); 
		//prt2Layer(dp); 
		
		return dp[0][0]; 
	}
};


class Solution6 {
public:
	int calculateMinimumHP(vector<vector<int>>& dungeon) {
		int n = dungeon.size(), m = dungeon[0].size(); 
		vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT_MAX)); 
		dp[n - 1][m - 1] = dungeon[n - 1][m - 1] >= 0 ? 1 : (1 - dungeon[n - 1][m - 1]); 

		for (int i = n - 1; i >= 0; --i){
			for (int j = m - 1; j >= 0; --j){
				if (i==n-1 && j==m-1) continue;

				int target = min(dp[i + 1][j], dp[i][j + 1]); 
				dp[i][j] = max(target - dungeon[i][j], 1); 
			}
		}

		prt2Layer(dungeon); 
		cout << endl; 
		prt2Layer(dp); 

		return dp[0][0]; 
	}
};



int main(){
	Solution5 a;
	Solution6 a2;

	vector<int> b = { 7, 2, 5, 10, INT_MAX };

	vector<vector<int>> map = {
		{ -2, -3, 3 },
		{ -5, -10, 1 },
		{ 10, 30, -5 }
	};

	vector<vector<int>> map2 = { // corner case
		{ 1, -3, 3 },
		{ 0, -2, 0 },
		{ -3, -3, -3 }
	}; 

	vector<vector<int>> map3 = { { 100 } }; 
	cout << a.calculateMinimumHP( map) << endl; 
	cout << a2.calculateMinimumHP(map) << endl; 


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