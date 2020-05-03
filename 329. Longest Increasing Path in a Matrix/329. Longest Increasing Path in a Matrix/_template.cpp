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


// Given an integer matrix, find the length of the longest increasing path.
// 
// From each cell, you can either move to four directions : left, right, up or down.You may NOT move diagonally or move outside of the boundary(i.e.wrap - around is not allowed).
// 
// Example 1 :
// 
// nums = [
// 		[9, 9, 4],
// 		[6, 6, 8],
// 		[2, 1, 1]
// ]
// 
// Return 4
// The longest increasing path is[1, 2, 6, 9].
// 
// Example 2:
// 
// nums = [
// 		[3, 4, 5],
// 		[3, 2, 6],
// 		[2, 2, 1]
// ]
// 
// Return 4
// The longest increasing path is[3, 4, 5, 6].Moving diagonally is not allowed.
// 
// Credits:
// Special thanks to @dietpepsi for adding this problem and creating all test cases.



vector<vector<int>> dir{ { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
// pass ! 
class Solution {
public:
	int longestIncreasingPath(vector<vector<int>>& matrix) {
		int n = matrix.size(), m = matrix[0].size(); 
		int res = 0; 
		vector<vector<int>> dp(n, vector<int>(m, -1)); 

		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				res = max(res, dfs(matrix, i, j, dp)); 
			}
		}
		return res; 
	}


	int dfs(vector<vector<int>>& matrix, int r, int c, vector<vector<int>>& dp){
		if (dp[r][c] >= 0)
			return dp[r][c]; 

		int res = 0; 
		for (auto d : dir){
			int x = r + d[0],
				y = c + d[1]; 
			if (x >= 0 && x < matrix.size() && y >= 0 && y < matrix[0].size() && matrix[x][y] > matrix[r][c]){
				res = max(res, dfs(matrix, x, y, dp)); 
			}
		}

		dp[r][c] = res+1; 
		return res+1; 
	}
};


typedef pair<int, int> PII;
vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 

class Solution2 {
public:

	int longestIncreasingPath(vector<vector<int>>& matrix) {
		int res = 0; 
		int n = matrix.size(), m = matrix[0].size(); 
		if (n == 0 || m == 0)
			return 0; 

		map<PII, int> visited; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				res = max(res, dfs(matrix, i, j, visited)); 
			}
		}
		return res; 
	}

	int dfs(vector<vector<int>>& matrix, int i, int j, map<PII, int>& visited){
		if (visited.count({ i, j }))
			return visited[{i, j}]; 

		int n = matrix.size(), m = matrix[0].size(); 
		int len = 1; 
		int val = matrix[i][j]; 

		for (auto d : dirs){
			int x = i + d[0], y = j + d[1]; 
			if (x >= 0 && x < n && y >= 0 && y<m && matrix[x][y]>val){
				len = max(len, dfs(matrix, x, y, visited) + 1); 
			}
		}
		visited[{i, j}] = len;
		return len; 
	}
};


class Solution3 {
public:
	unordered_map<int, unordered_map<int, int>> g;
	int longestIncreasingPath(vector<vector<int>>& matrix) {
		int n = matrix.size(), m = matrix[0].size(); 
		int res = 0; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				res = max(res, dfs(matrix, i, j)); 
			}
		}
		return res; 
	}

	int dfs(vector<vector<int>>& mtx, int i, int j){
		if (g.count(i) && g[i].count(j))
			return g[i][j]; 

		int cur = mtx[i][j]; 
		int n = mtx.size(), m = mtx[0].size(); 
		// if (
		// 	(i == 0 || cur < mtx[i - 1][j]) &&
		// 	(i == n - 1 || cur < mtx[i + 1][j]) &&
		// 	(j == 0 || cur < mtx[i][j - 1]) &&
		// 	(j == m - 1 || cur < mtx[i][j + 1])
		// 	)
		// 	return 1; 

		int r = 0; 
		for (auto d : dirs){
			int xx = i + d[0], yy = j + d[1]; 
			if (xx >= 0 && xx < n&&yy >= 0 && yy < m && cur < mtx[xx][yy]){
				r = max(r, dfs(mtx, xx, yy)); 
			}
		}

		g[i][j] = r + 1; 
		return r + 1; 
	}
};


class Solution4 {
public:
	unordered_map<int, unordered_map<int, int>> g;
	int longestIncreasingPath(vector<vector<int>>& matrix) {
		int n = matrix.size(), m = matrix[0].size(); 
		int res = INT_MIN; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				res = max(res, dfs(matrix, i, j)); 
			}
		}
		return res; 
	}
	int dfs(vector<vector<int>>& m, int i, int j){
		if (g[i][j]) return g[i][j]; 
		int n = matrix.size(), n2 = matrix[0].size(); 
		int r = 0; 
		for (auto d : dirs){
			int ii = i + d[0], jj = j + d[1]; 
			if (ii >= 0 && ii < n&&jj >= 0 && jj<n2 &&m[ii][jj]>m[i][j]){
				r = max(r, 1 + dfs(m, ii, jj)); 
			}
		}
		g[i][j] = r; 
		return r; 
	}
}; 


int main() {
	Solution2 a;
	Solution3 a2;
	vector<vector<int>> b = {
		{ 9, 9, 4 },
		{ 6, 6, 8 },
		{ 2, 1, 1 },
	};

	vector<vector<int>> c = {
		{ 3, 4, 5 },
		{ 3, 2, 6 },
		{ 2, 2, 1 },
	};

	cout << a.longestIncreasingPath(c) << endl; 
	cout << a2.longestIncreasingPath(c) << endl; 

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

