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
vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 

class Solution {
public:
	int numDistinctIslands(vector<vector<int>>& grid) {
		if (grid.empty() || grid[0].empty())
			return 0; 
		int n = grid.size(), m = grid[0].size(); 

		unordered_set<int> v; 
		unordered_set<string> res; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (grid[i][j] && !v.count(i*m + j)){
					string path; 
					dfs(grid, i, j, i, j, path, v); 
					cout << path << endl; 
					res.insert(path); 
				}
			}
		}
		return res.size(); 
	}

	void dfs(vector<vector<int>>& grid, int x0, int y0, int i, int j, string& path, unordered_set<int>& v){
		int n = grid.size(), m = grid[0].size(); 
		v.insert(i*m + j); 
		path += to_string(i - x0) + "_" + to_string(j - y0) + "_";
		for (auto& d : dirs){
			int xx = i + d[0], yy = j + d[1], idx = xx*m + yy;
			if (xx >= 0 && xx < n && yy >= 0 && yy < m && !v.count(idx) && grid[xx][yy]){
				dfs(grid, x0, y0, xx, yy, path, v); 
			}
		}
	}

	void bfs(vector<vector<int>>& grid, int x0, int y0, int i, int j, string& path, unordered_set<int>& v){
		int n = grid.size(), m = grid[0].size(); 
		queue<int> q; 
		q.push(i*m + j); 
		v.insert(i*m + j); 

		while (!q.empty()){
			int f = q.front(); 
			q.pop(); 
			
			int x = f / m, y = f%m; 
			path += to_string(x - x0) + "_" + to_string(y - y0) + "_"; 
			for (auto& d : dirs){
				int xx = x + d[0], yy = y + d[1], idx = xx*m + yy; 
				if (xx >= 0 && xx < n && yy >= 0 && yy < m && !v.count(idx) && grid[xx][yy]){
					v.insert(idx); 
					q.push(idx); 
				}
			}
		}
	}
};

class Solution2 {
public:
	int numDistinctIslands(vector<vector<int>>& grid) {
		
	}
};

int main(){
	Solution a; 

	vector<vector<int>> g = {
		{ 1, 1, 0, 1, 1 },
		{ 1, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 1 },
		{ 1, 1, 0, 1, 1 },
	};

	cout << a.numDistinctIslands(g) << endl; 

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

