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
typedef pair<int, int> PII; 
vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 

class Solution {
public:
	int numDistinctIslands2(vector<vector<int>>& grid) {
		if (grid.empty() || grid[0].empty())
			return 0; 

		int n = grid.size(), m = grid[0].size(); 
		unordered_set<int> v; 
		set<vector<PII>> res; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (grid[i][j] && !v.count(i*m + j)){
					vector<PII> path; 
					dfs(grid, i, j, i, j, path, v); 
					res.insert(normalize(path)); 
				}
			}
		}
		return res.size(); 
	}

	void dfs(vector<vector<int>>& grid, int x0, int y0, int i, int j, vector<PII>& path, unordered_set<int>& v){
		int n = grid.size(), m = grid[0].size(); 
		v.insert(i*m + j); 
		path.push_back({ i - x0, j - y0 }); 

		for (auto& d : dirs){
			int x = i + d[0], y = j + d[1]; 
			if (x >= 0 && x < n&&y >= 0 && y < m&& !v.count(x*m + y) && grid[x][y]){
				dfs(grid, x0, y0, x, y, path, v); 
			}
		}
	}

	vector<PII> normalize(vector<PII>& path){
		vector<vector<PII>> cand(8); 
		for (auto& p : path){
			int x = p.first, y = p.second; 
			cand[0].push_back({ x, y }); 
			cand[1].push_back({ -x, y }); 
			cand[2].push_back({ x, -y }); 
			cand[3].push_back({ -x, -y }); 
			cand[4].push_back({ y, x });
			cand[5].push_back({ -y, x });
			cand[6].push_back({ y, -x });
			cand[7].push_back({ -y, -x });
		}

		for (auto& v : cand)
			sort(v.begin(), v.end()); 
		for (auto& v : cand){
			for (int i = 1; i < v.size(); ++i){
				v[i] = { v[i].first - v[0].first, v[i].second - v[0].second }; 
			}
			v[0] = { 0, 0 }; 
		}
		sort(cand.begin(), cand.end()); 
		return cand[0]; 
	}
};

typedef vector<vector<int>> VVI; 
class Solution2 {
public:
	int numDistinctIslands2(vector<vector<int>>& grid) {
		int n = grid.size(), m = grid[0].size(); 
		set<VVI> shapes; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (grid[i][j]==1){
					store(grid, i, j, shapes); 
					prt2Layer(grid);
				}
			}
		}

		return shapes.size() / 8; 
	}

	void store(VVI& grid, int x, int y, set<VVI>& shapes){
		vector<vector<vector<int>>> shape(8); 
		dfs(grid, x, y, x, y, shape); 
		for (auto& s : shape)
			sort(s.begin(), s.end()); 
		for (auto& s : shape){
			vector<int> orig = s[0]; 
			for (int i = 0; i < s.size(); ++i){
				s[i][0] -= orig[0];
				s[i][1] -= orig[1];
			}
		}

		for (auto& s : shape)
			shapes.insert(s); 
	}

	void dfs(VVI& g, int x, int y, int x0, int y0, vector<VVI>& shape){
		int n = g.size(), m = g[0].size(); 
		if (x < 0 || x >= n || y < 0 || y >= m || g[x][y] != 1)
			return; 

		g[x][y] = 2; 
		int xx = x - x0, yy = y - y0; 
		shape[0].push_back({ xx, yy }); 
		shape[1].push_back({ -xx, yy }); 
		shape[2].push_back({ xx, -yy }); 
		shape[3].push_back({ -xx, -yy }); 
		shape[4].push_back({ yy, xx }); 
		shape[5].push_back({ -yy, xx }); 
		shape[6].push_back({ yy, -xx }); 
		shape[7].push_back({ -yy, -xx });

		dfs(g, x + 1, y, x0, y0, shape);
		dfs(g, x - 1, y, x0, y0, shape);
		dfs(g, x, y + 1, x0, y0, shape);
		dfs(g, x, y - 1, x0, y0, shape);
	}
}; 

int main(){
	Solution2 a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	VVI c = { 
		{ 1, 1, 0, 0, 0 }, 
		{ 1, 0, 0, 0, 1 }, 
		{ 1, 0, 0, 0, 1 }, 
		{ 0, 0, 0, 1, 1 } 
	}; 

	cout << a.numDistinctIslands2(c) << endl; 


	// vector<vector<vector<int>>> x = {
	// 	{ { 3, 0 }, { 1, -1 }, { 0, 8 } },
	// 	{ { 2, 0 }, { 0, -1 }, { -2, 8 } },
	// }; 

	// for (auto& y:x) 
	// 	sort(y.begin(), y.end()); 

	// for (auto& y:x) {
	// 	prt2Layer(y); 
	// }


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

