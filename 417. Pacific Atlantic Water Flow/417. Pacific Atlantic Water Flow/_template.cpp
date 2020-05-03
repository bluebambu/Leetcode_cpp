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

// Given an m x n matrix of non - negative integers representing the height of each unit cell in a continent, the "Pacific ocean" 
// touches the left and top edges of the matrix and the "Atlantic ocean" touches the right and bottom edges.

// Water can only flow in four directions(up, down, left, or right) from a cell to another one with height equal or lower.

// Find the list of grid coordinates where water can flow to both the Pacific and Atlantic ocean.

// Note:
// The order of returned grid coordinates does not matter.
// Both m and n are less than 150.
// Example :

// 		Given the following 5x5 matrix :

// 		Pacific ~~~~~
// 		~1   2   2   3  (5) *
// 		~3   2   3  (4) (4) *
// 		~2   4  (5)  3   1 *
// 		~(6) (7)  1   4   5 *
// 		~(5)  1   1   2   4 *
// 		*   *   *   *   * Atlantic

// 	Return :

// [[0, 4], [1, 3], [1, 4], [2, 2], [3, 0], [3, 1], [4, 0]](positions with parentheses in above matrix).


// pass
vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 

template<typename T>
void prnt2layer(T v){
	for (auto i : v){
		for (auto j : i){
			cout << j << " "; 
		}
		cout << endl; 
	}
	cout << endl; 
}

class Solution {
public:
	vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
		if (matrix.empty() || matrix[0].empty())
			return{}; 

		int n = matrix.size(), m = matrix[0].size(); 
		vector<vector<int>> status(n, vector<int>(m, 0)); 

		queue<int> q; 
		unordered_set<int> v;

		for (int i = 0; i < n; ++i){
			q.push(i*m + 0); 
			v.insert(i*m);
			status[i][0] = 1; 
		}
		for (int j = 0; j < m; ++j){
			q.push(j); 
			v.insert(j);
			status[0][j] = 1; 
		}
		while (!q.empty()){
			int f = q.front(); 
			q.pop(); 
			int i = f / m, j = f%m; 

			for (auto& d : dirs){
				int x = i + d[0], y = j + d[1]; 
				if (x >= 0 && x < n && y >= 0 && y < m && !v.count(x*m + y) && matrix[x][y] >= matrix[i][j]){
					v.insert(x*m + y); 
					status[x][y] = 1; 
					q.push(x*m + y); 
				}
			}
		}

		for (auto k : status){
			for (auto l : k)
				cout << l << " "; 
			cout << endl; 
		}
		
		v = unordered_set<int>(); 
		vector<pair<int, int>> res; 
		for (int i = 0; i < n; ++i){
			q.push(i*m + m-1); 
			v.insert(i*m+m-1);
			if (status[i][m - 1] == 1)
				res.push_back({ i, m - 1 }); 
		}
		for (int j = 0; j < m; ++j){
			if (status[n - 1][j] == 1 && !v.count((n-1)*m+j))
				res.push_back({ n - 1, j }); 
			q.push((n-1)*m + j); 
			v.insert((n-1)*m + j);
		}
		while (!q.empty()){
			int f = q.front(); 
			q.pop(); 
			int i = f / m, j = f%m; 

			for (auto& d : dirs){
				int x = i + d[0], y = j + d[1]; 
				if (x >= 0 && x < n && y >= 0 && y < m && !v.count(x*m + y) && matrix[x][y] >= matrix[i][j]){
					v.insert(x*m + y); 
					q.push(x*m + y); 
					if (status[x][y] == 1){
						res.push_back({ x, y }); 
					}
				}
			}
		}
		return res;
	}
};

// wrong ans!!!
class Solution2 {
public:
	vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
		vector<pair<int, int>> res; 
		if (matrix.empty() || matrix[0].empty())
			return res; 
		int n = matrix.size(), m = matrix[0].size(); 

		unordered_map<int, int> v;
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				unordered_set<int> vst; 
				dfs(matrix, i, j, v, vst, res); 
			}
		}

		for (auto& k : v)
			cout << k.first / m << "-" << k.first%m << " " << k.second << endl;
		cout << endl; 

		return res; 
	}

	int dfs(vector<vector<int>>& matrix, int i, int j, unordered_map<int, int>& v, unordered_set<int>& vst, vector<pair<int, int>>& r){
		int n = matrix.size(), m = matrix[0].size(); 
		int idx = i*m + j;
		if (v.count(idx))
			return v[idx]; 

		int res = 0; 
		if ((i == 0 && j == m - 1) || (i == n - 1 && j == 9)){
			r.push_back({ i, j }); 
			return 3; 
		}
		if (i == 0 || j == 0)
			res |= 1; 
		if (i == n - 1 || j == m - 1)
			res |= 2; 

		vst.insert(idx); 
		for (auto& d : dirs){
			int x = i + d[0], y = j + d[1]; 
			if (x >= 0 && x < n && y >= 0 && y < m && matrix[x][y] <= matrix[i][j] && !vst.count(x*m+y)){
				res |= dfs(matrix, x, y, v, vst, r);
			}
		}

		if (res == 3)
			r.push_back({ i, j }); 

		v[idx] = res; 
		return res; 
	}
}; 



// pass; 
void prntv(vector<vector<bool>> v){
	for (auto a : v){
		for (auto b : a)
			cout << b << ' '; 
		cout << endl;
	}
	cout << endl << endl; 
}

class Solution3 {
public:
	vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
		if (matrix.empty() || matrix[0].empty())
			return{}; 

		int n = matrix.size(), m = matrix[0].size(); 
		vector<vector<bool>> pacific(n, vector<bool>(m, false)), atlantic = pacific; 

		check(matrix, pacific, 0); 
		check(matrix, atlantic, 1); 

		prntv(pacific);
		prntv(atlantic);
		
		vector<pair<int, int>> res; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (pacific[i][j] && atlantic[i][j])
					res.push_back({ i, j }); 
			}
		}

		return res; 
	}

	void check(vector<vector<int>>& mtx, vector<vector<bool>>& v, int flag){
		int n = mtx.size(), m = mtx[0].size(); 
		queue<pair<int, int>> q; 
		if (flag == 0) {//pacific
			for (int i = 0; i < n; ++i){
				q.push({ i, 0 }); 
				v[i][0] = true; 
			}
			for (int j = 1; j < m; ++j){
				q.push({ 0, j }); 
				v[0][j] = true; 
			}
		}
		else{
			for (int i = 0; i < n; ++i){
				q.push({ i, m-1 }); 
				v[i][m-1] = true; 
			}
			for (int j = 0; j < m-1; ++j){
				q.push({ n-1, j }); 
				v[n-1][j] = true; 
			}
		}

		while (!q.empty()){
			auto f = q.front(); 
			q.pop(); 
			int x = f.first, y = f.second; 

			for (auto d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&!v[xx][yy] && mtx[xx][yy] >= mtx[x][y]){
					v[xx][yy] = true; 
					q.push({ xx, yy });
				}
			}
		}
	}
}; 


class Solution4 {
public:
	vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
		int n = matrix.size(), m = matrix[0].size(); 
		vector<vector<int>> marker(n, vector<int>(m, 0)); 
		vector<vector<bool>> v(n, vector<bool>(m, false)); 

		for (int i = 0; i < n; ++i){
			if (!v[i][0])
				flow(matrix, i, 0, v, marker);
		}
		for (int j = 1; j < m; ++j){
			if (!v[0][1])
				flow(matrix, 0, j, v, marker);
		}

		v = vector<vector<bool>>(n, vector<bool>(m, false));
		for (int i = 0; i < n; ++i){
			if (!v[i][m - 1])
				flow(matrix, i, m - 1, v, marker);
		}
		for (int j = 0; j < m - 1; ++j){
			if (!v[n - 1][j])
				flow(matrix, n - 1, j, v, marker);
		}

		vector<pair<int, int>> res; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (marker[i][j] == 2)
					res.push_back({ i, j }); 
			}
		}

		prnt2layer(marker); 

		return res; 
	}

	void flow(vector<vector<int>>& mtx, int i, int j, vector<vector<bool>>& v, vector<vector<int>>& marker){
		int n = mtx.size(), m = mtx[0].size(); 
		marker[i][j] += 1; 
		v[i][j] = true; 

		for (auto d : dirs){
			int x = i + d[0], y = j + d[1]; 
			if (x >= 0 && x < n&&y >= 0 && y < n&&mtx[x][y] >= mtx[i][j] && !v[x][y]){
				flow(mtx, x, y, v, marker); 
			}
		}
	}
}; 


class Solution5 {
public:
	vector<pair<int, int>> pacificAtlantic(vector<vector<int>>& matrix) {
		int n = matrix.size(), m = matrix[0].size(); 
		vector<vector<int>> pac(n, vector<int>(m, 0)), atl = pac; 
		for (int j = 0; j < m; ++j){
			if (pac[0][j] == 0){
				bfs(matrix, pac, 0, j); 
			}
		}
		for (int i = 1; i < n; ++i){
			if (pac[i][0] == 0){
				bfs(matrix, pac, i, 0); 
			}
		}
		for (int j = 0; j < m; ++j){
			if (atl[n-1][j] == 0){
				bfs(matrix, atl, n - 1, j); 
			}
		}
		for (int i = 0; i < n-1; ++i){
			if (atl[i][m-1] == 0){
				bfs(matrix, atl, i, m - 1); 
			}
		}

		vector<pair<int, int>> res; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (atl[i][j] && pac[i][j])
					res.push_back({ i, j });
			}
		}
		return res; 
	}
	void bfs(vector<vector<int>>& mtx, vector<vector<int>>& rec, int i, int j){
		int n = mtx.size(), m = mtx[0].size(); 
		rec[i][j] = 1; 
		for (auto d : dirs){
			int x = i + d[0], y = j + d[1]; 
			if (x >= 0 && x < n&&y >= 0 && y < m&&rec[x][y] == 0 && mtx[x][y] >= mtx[i][j] ){
				bfs(mtx, rec, x, y); 
			}
		}
	}
}; 

int main() {
	Solution a;
	Solution5 a2;

	vector<vector<int>> m = {
		{1,2,2,3,5},
		{3,2,3,4,4},
		{2,4,5,3,1},
		{6,7,1,4,5},
		{5,1,1,2,4}
	};

	vector<vector<int>> mm2 = {
		{ 3, 3, 3, 3, 3, 3 },
		{ 3, 0, 3, 3, 0, 3 },
		{ 3, 3, 3, 3, 3, 3 },
	};

	vector<vector<int>> mm = {
		{ 1, 2 },
		{ 4, 3 }
	};
	auto b = a.pacificAtlantic(mm); 

	for (auto i : b){
		cout << i.first << "-" << i.second << endl; 
	}

	cout << "===========================\n"; 

	b = a2.pacificAtlantic(mm); 

	for (auto i : b){
		cout << i.first << "-" << i.second << endl; 
	}
}

