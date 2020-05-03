// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <functional>
#include <bitset>
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

vector<vector<int>> dirs = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } }; 

class Solution {
public:
	vector<int> hitBricks(vector<vector<int>> grid, vector<vector<int>> hits) {
		vector<vector<int>> orig = grid; 

		if (grid.empty() || grid[0].empty())
			return{}; 

		int n = grid.size(), m = grid[0].size(); 
		for (int i = 0; i < hits.size(); ++i){
			grid[hits[i][0]][hits[i][1]] = 0; 
		}

		vector<vector<bool>> visited(n, vector<bool>(m, false)); 
		int tot = 0; 
		for (int j = 0; j<m; ++j){
			if (grid[0][j] && !visited[0][j]){
				tot += bfs(grid, 0, j, visited); 
			}
		}

		vector<int> res; 

		for (int i = hits.size() - 1; i >= 0; --i){
			vector<int>& add = hits[i]; 
			int x = add[0], y = add[1]; 
			if (orig[x][y]){
				grid[x][y] = 1;
				tot = bfs(grid, x, y, visited);
				res.push_back(tot);
			}
			else
				res.push_back(0); 
		}

		reverse(res.begin(), res.end()); 
		return res; 
	}

	int bfs(vector<vector<int>>& grid, int x, int y, vector<vector<bool>>& v){
		int n = grid.size(), m = grid[0].size(); 
		int r = 0; 
		queue<vector<int>> q; 
		q.push({ x, y }); 
		v[x][y] = true; 

		bool surround_visited = false; 
		for (auto& d : dirs){
			int xx = x + d[0], yy = y + d[1];
			if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&grid[xx][yy] && v[xx][yy]){
				surround_visited = true; 
			}
		}
		if (!surround_visited && x != 0){
			v[x][y] = false;
			return 0; 
		}
		else if (!surround_visited){
			v[x][y] = true;
		}
		
		while (!q.empty()){
			auto f = q.front(); 
			q.pop(); 
			int x = f[0], y = f[1]; 

			for (auto& d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&grid[xx][yy] && !v[xx][yy]){
					r += 1; 
					v[xx][yy] = true; 
					q.push({ xx, yy });
				}
			}
		}

		return r; 
	}
};

typedef vector<vector<int>> VVI; 

class Solution2 {
public:
	vector<int> hitBricks(vector<vector<int>> grid, vector<vector<int>> hits) {
		int n = grid.size(), m = grid[0].size(); 
		for (auto& h : hits){
			int x = h[0], y = h[1]; 
			if (grid[x][y] == 0)
				h[0] *= -1, h[1] *= -1;
			else
				grid[x][y] = 0; 
		}

		vector<int> res; 
		for (int j = 0; j < m; ++j){
			if (grid[0][j]){
				bfs(grid, 0, j, 2); 
			}
		}

		for (int i = hits.size() - 1; i >= 0; --i){
			auto h = hits[i]; 
			int x = h[0], y = h[1]; 
			if (x < 0){
				res.push_back(0); 
			}
			else{
				grid[x][y] = 1; 
				bool good = false; 
				if (x == 0) good = true;
				else{
					for (auto d : dirs){
						int xx = x + d[0], yy = y + d[1];
						if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&grid[xx][yy] == 2)
							good = true;
					}
				}

				if (!good){
					res.push_back(0); 
				}
				else{
					int tot = 0; 
					grid[x][y] = 2; 
					for (auto d : dirs){
						int xx = x + d[0], yy = y + d[1];
						if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&grid[xx][yy] == 1){
							tot += bfs(grid, xx, yy, 2); 
						}
					}
					res.push_back(tot); 
				}
			}

			prt2Layer(grid); 
		}

		reverse(res.begin(), res.end()); 
		return res; 
	}

	int bfs(VVI& grid, int x, int y, int newval){
		if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] == newval || grid[x][y] == 0)
			return 0; 
		int res = 1; 
		grid[x][y] = newval; 
		res += bfs(grid, x + 1, y, newval); 
		res += bfs(grid, x - 1, y, newval); 
		res += bfs(grid, x, y + 1, newval);
		res += bfs(grid, x, y - 1, newval);

		return res; 
	}
};


int main(){
	Solution a; 
	Solution2 a2; 

	vector<vector<int>> grid = {
		{ 1, 0, 0, 0 },
		{ 1, 1, 1, 0 }
	},
	hits = { { 1, 0 } }; 

	vector<vector<int>> grid2 = {
		{ 1, 0, 0, 0 },
		{ 1, 1, 0, 0 }
	},
	hits2 = { { 1, 1 }, { 1, 0 } };

	vector<vector<int>> grid3 =  { { 1 }, { 1 }, { 1 }, { 1 },{ 1 } }, 
		hits3 = { { 3, 0 }, { 4, 0 }, { 1, 0 }, { 2, 0 }, { 0, 0 } };

	vector<vector<int>> grid4 = {
		{1,1,1},
		{0,1,0},
		{0,0,0},
	}, 
	hits4 = {
		{0,2}, 
		{2,0}, 
		{0,1}, 
		{1,2}, 
	}; 

	auto b = a.hitBricks(grid2, hits2); 

	for (auto i : b)
		cout << i << ' '; 

	cout << endl; 

	// ----------------
	auto b2 = a2.hitBricks(grid2, hits2); 

	for (auto i : b2)
		cout << i << ' '; 

	cout << endl; 


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

