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
inline float min(float a, float b) { return a < b ? a : b; }


struct TreeNode {
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



// 
// You are given a m x n 2D grid initialized with these three possible values.
// 
// - 1 - A wall or an obstacle.
// 0 - A gate.
// INF - Infinity means an empty room.We use the value 231 - 1 = 2147483647 to represent INF as you may assume that the distance to a gate is less than 2147483647.
// 
// Fill each empty room with the distance to its nearest gate.If it is impossible to reach a gate, it should be filled with INF.
// 
// For example, given the 2D grid:
// 
// INF - 1  0  INF
// INF INF INF - 1
// INF - 1 INF - 1
// 0 - 1 INF INF
// 
// After running your function, the 2D grid should be :
// 
// 3 - 1   0   1
// 2   2   1 - 1
// 1 - 1   2 - 1
// 0 - 1   3   4


vector<pair<int, int>> dir = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
vector<vector<int>> dirs = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
int INF = 2147483647;

// pass, but slow
class Solution {
public:
	void wallsAndGates(vector<vector<int>>& rooms) {
		if (rooms.empty() || rooms[0].empty())
			return;

		for (int i = 0; i < rooms.size(); ++i){
			for (int j = 0; j < rooms[i].size(); ++j){
				if (rooms[i][j] == 0)
					bfs(rooms, i, j);
			}
		}
	}


	void bfs(vector<vector<int>>& matrix, int i, int j){
		struct node{
			int x;
			int y;
			int step;
			node(int a, int b, int c) :x(a), y(b), step(c) {}
		};

		queue<node> q;
		q.push(node(i, j, 0));

		while (!q.empty()){
			node tmp = q.front();
			q.pop();

			for (int k = 0; k < dir.size(); ++k){
				int x = tmp.x + dir[k].first,
					y = tmp.y + dir[k].second,
					step = tmp.step + 1;

				// pay attention to the boundry of matrix
				if (x >= 0 && x < matrix.size() && y >= 0 && y<matrix[0].size() && (matrix[x][y] == 2147483647 || matrix[x][y]>step)){
					matrix[x][y] = step;
					q.push(node(x, y, step));
				}
			}
		}
	}
};


// faster
class Solution2 {
public:
	void wallsAndGates(vector<vector<int>>& rooms) {
		if (rooms.empty() || rooms[0].empty())
			return;

		for (int i = 0; i < rooms.size(); ++i){
			for (int j = 0; j < rooms[i].size(); ++j){
				if (rooms[i][j] == 0)
					dfs(rooms, i, j, 0);
			}
		}
	}


	void dfs(vector<vector<int>>& matrix, int i, int j, int step){
		if (i < 0 || i >= matrix.size() || j < 0 || j >= matrix[0].size() || matrix[i][j] < 0 || matrix[i][j] < step)
			return; 

		matrix[i][j] = step; 
		dfs(matrix, i + 1, j, step + 1); 
		dfs(matrix, i, j + 1, step + 1); 
		dfs(matrix, i - 1, j, step + 1); 
		dfs(matrix, i, j - 1, step + 1); 

	}
};


// passed
class Solution3 {
public:
	void wallsAndGates(vector<vector<int>>& rooms) {
		if (rooms.empty() || rooms[0].empty())
			return; 

		int n = rooms.size(), m = rooms[0].size(); 
		queue<int> q; 

		for (int i = 0; i < rooms.size(); ++i){
			for (int j = 0; j < rooms[i].size(); ++j){
				if (rooms[i][j] == 0)
					q.push(i*m + j); 
			}
		}

		int dist = 1; 
		while (!q.empty()){
			int sz = q.size(); 
			for (int i = 0; i < sz; ++i){
				int f = q.front(); 
				q.pop(); 
				int x = f / m, y = f%m; 

				for (auto& d : dirs){
					int xx = x + d[0], yy = y + d[1]; 
					if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&rooms[xx][yy] == 2147483647){
						rooms[xx][yy] = dist; 
						q.push(xx*m + yy); 
					}
				}
			}
			++dist;
		}
	}
}; 

class Solution4 {
public:
	void wallsAndGates(vector<vector<int>>& rooms) {
		if (rooms.empty() || rooms[0].empty())
			return; 

		for (int i = 0; i < rooms.size(); ++i){
			for (int j = 0; j < rooms[i].size(); ++j){
				if (rooms[i][j] == 0){
					dfs(rooms, i, j, 0); 
				}
			}
		}
	}

	void dfs(vector<vector<int>>& rooms, int i, int j, int d){
		int n = rooms.size(), m = rooms[0].size(); 
		if (i < 0 || i >= n || j < 0 || j >= m)
			return; 
		if (rooms[i][j] < d)
			return; 

		rooms[i][j] = d; 

		dfs(rooms, i + 1, j, d + 1);
		dfs(rooms, i - 1, j, d + 1);
		dfs(rooms, i, j + 1, d + 1);
		dfs(rooms, i, j - 1, d + 1);
	}
}; 


class Solution5 {
public:
	void wallsAndGates(vector<vector<int>>& rooms) {
		queue<vector<int>> q; 
		int n = rooms.size(), m = rooms[0].size(); 
		vector<vector<int>> visited(n, vector<int>(m, 0)); 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (rooms[i][j] == 0){
					q.push({ i, j }); 
					visited[i][j] = 1;
				}
			}
		}

		int dist = 1; 
		while (!q.empty()){
			int sz = q.size(); 
			for (int i = 0; i < sz; ++i){
				auto f = q.front(); 
				q.pop(); 

				for (auto d : dirs){
					int xx = f[0] + d[0], yy = f[1] + d[1]; 
					if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&!visited[xx][yy] && rooms[xx][yy] == INF){
						visited[xx][yy] = 1; 
						rooms[xx][yy] = dist; 
						q.push({ xx, yy }); 
					}
				}

			}
			++dist;
		}
	}
};

class Solution6 {
public:
	void wallsAndGates(vector<vector<int>>& rooms) {
			
	}
}; 



int main() {
	vector<vector<int>> grid = {
		{ INF, -1, 0, INF },
		{ INF, INF, INF, -1 },
		{ INF, -1, INF, -1 },
		{ 0, -1, INF, INF },
	};

	Solution5 a; 
	a.wallsAndGates(grid); 

	for (auto i : grid){
		for (auto j : i){
			cout << j << ' '; 
		}
		cout << endl; 
	}

}

