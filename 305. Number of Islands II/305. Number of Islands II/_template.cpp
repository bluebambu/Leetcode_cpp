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



// A 2d grid map of m rows and n columns is initially filled with water.We may perform an addLand operation which turns the water at position(row, col) into a land.Given a list of positions to operate, count the number of islands after each addLand operation.An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically.You may assume all four edges of the grid are all surrounded by water.
// 
// Example:
// 
// Given m = 3, n = 3, positions = [[0, 0], [0, 1], [1, 2], [2, 1]].
// Initially, the 2d grid grid is filled with water. (Assume 0 represents water and 1 represents land).
// 
// 0 0 0
// 0 0 0
// 0 0 0
// 
// Operation #1: addLand(0, 0) turns the water at grid[0][0] into a land.
// 
// 1 0 0
// 0 0 0   Number of islands = 1
// 0 0 0
// 
// Operation #2: addLand(0, 1) turns the water at grid[0][1] into a land.
// 
// 1 1 0
// 0 0 0   Number of islands = 1
// 0 0 0
// 
// Operation #3: addLand(1, 2) turns the water at grid[1][2] into a land.
// 
// 1 1 0
// 0 0 1   Number of islands = 2
// 0 0 0
// 
// Operation #4: addLand(2, 1) turns the water at grid[2][1] into a land.
// 
// 1 1 0
// 0 0 1   Number of islands = 3
// 0 1 0
// 
// We return the result as an array: [1, 1, 2, 3]
// 
// Challenge :
// 
// 		  Can you do it in time complexity O(k log mn), where k is the length of the positions ?



// faster approach	, pass
class Solution2 {
public:
	vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
		vector<int> res; 

		vector<int> root(m*n, -1); 
		vector<pair<int, int>> dir{ { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
		int count = 0; 
		for (auto pos : positions){
			++count; 
			int idx = pos.first*n + pos.second;
			root[idx] = idx; 
			
			for (auto d : dir){
				int x = pos.first + d.first,
					y = pos.second + d.second; 
				if (x<0 || x >= m || y<0 || y >= n || root[x*n+y]==-1)
					continue;
				int neibID = find(root, x*n + y); 													 // x x x
				if (neibID != idx){	 // 很重要， 判断 idx 这个点周围的邻点是不是属于同一个component。 类似  x Y x  ,	 这样的。 
					root[idx] = neibID;
					idx = neibID;  // 更新到当前root的值，把新的点和旧的点当做一整个岛， 和下一个邻点比较！ 
					--count; 
				}
			}
			res.push_back(count); 
		}
		return res; 
	}

	int find(vector<int>& root, int p){
		while (p != root[p]){
			root[p] = root[root[p]]; 
			p = root[p]; 
		}
		return p;
	}

};


vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 

class Solution3{
public:
	vector<int> numIslands2(int n, int m, vector<pair<int, int>>& positions) {
		vector<int> res; 
		if (m == 0 || n == 0) return res; 
		vector<int> g(m*n, 0); 
		for (int i = 0; i < m*n; ++i){
			g[i] = -1; 
		}

		int cnt = 0; 
		for (auto& p : positions){
			add(g, p.first, p.second, m, cnt); 
			res.push_back(cnt); 
		}
		
		return res; 
	}

	void add(vector<int>& g, int i, int j, int m, int& cnt){
		int idx = i*m + j; 
		g[idx] = idx; 
		++cnt; 
		int n = g.size() / m; 
		for (auto& d : dirs){
			int x = i + d[0], y = j + d[1], iidx = x*m + y; 
			if (x >= 0 && x < n && y >= 0 && y < m && g[iidx] != -1){
				int r = root(g, x, y, m); 
				if (r != idx){
					g[r] = idx;
					--cnt; 
				}
			}
		}
	}

	int root(vector<int>& g, int i, int j, int m){
		int idx = i*m + j; 
		if (g[idx] == idx)
			return idx; 
		return root(g, g[idx] / m, g[idx] % m, m); 
	}
};


class Solution4{
public:
	vector<int> numIslands2(int n, int m, vector<pair<int, int>>& positions) {
		vector<int> root(n*m, -1); 
		int tot = 0; 
		vector<int> r; 

		for (auto& p : positions){
			int x = p.first, y = p.second; 
			int idx = x*m + y; 
			root[idx] = idx; 
			++tot; 

			for (auto d : dirs){
				int xx = x + d[0], yy = y + d[1], iidx = xx*m + yy; 
				if (xx>=0&&xx<n&&yy>=0&&yy<m&&root[iidx] != -1 && find(root, iidx) != idx){
					root[find(root, iidx)] = idx;
					--tot; 
				}
			}

			r.push_back(tot);
		}

		return r; 
	}

	int find(vector<int>& root, int id){
		while (root[id] != id){
			id = root[id]; 
		}
		return id; 
	}
}; 

class Solution5 {
public:
	vector<int> numIslands2(int n, int m, vector<pair<int, int>>& positions) {
		vector<int> root(n*m, -1); 
		vector<int> res; 
		int cnt = 0; 

		for (auto& p : positions){
			int x = p.first, y = p.second; 
			int idx = x*m + y; 
			root[idx] = idx; 
			cnt += 1; 
			
			for (auto d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&root[xx*m + yy] != -1 && find(root, xx*m + yy) != idx){
					root[find(root, xx*m + yy)] = idx;
					--cnt; 
				}
			}

			res.push_back(cnt); 
		}
		return res;
	}

	int find(vector<int>& root, int i){
		while (i != root[i]) i = root[i]; 
		return i; 
	}
	void unify(vector<int>& root, int i, int j){
		if (find(root, i) == j) return; 
		root[find(root, i)] = j;
	}
}; 


class Solution6 {
public:
	vector<int> numIslands2(int n, int m, vector<pair<int, int>>& positions) {
		vector<int> root(n*m, -1); 
		int cnt = 0; 
		vector<int> res; 

		for (auto& p : positions){
			int x = p.first, y = p.second, idx = x*m + y; 
			cnt += 1; 
			root[idx] = idx; 
			for (auto d : dirs){
				int xx = x + d[0], yy = y + d[1], iidx = xx*m + yy; 
				if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&root[iidx] != -1 && find(root, iidx)!=idx){
					unify(root, iidx, idx); 
					cnt -= 1; 
				}
			}
			res.push_back(cnt); 
		}
		return res;
	}
	int find(vector<int>& root, int i){
		while (i != root[i]) i = root[i]; 
		return i; 
	}
	void unify(vector<int>& root, int i, int j){
		if (find(root, i) == j) return; 
		root[find(root, i)] = j;
	}
}; 


class Solution7 {
public:
	vector<int> numIslands2(int n, int m, vector<pair<int, int>>& positions) {
		vector<int> root(n*m, -1); 
		int cnt = 0; 
		vector<int> res; 

		for (auto& p : positions){
			int x = p.first, y = p.second; 
			cnt += 1; 
			int idx = x*m + y; 
			root[idx] = idx;  
			for (auto d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				if (xx >= 0 && xx < n&&yy >= 0 && yy < m && root[xx*m+yy] != -1){
					if (find(root, xx*m+yy) != find(root, idx)){
						cnt -= 1; 
						unify(root, xx*m + yy, idx); 
					}
				}
			}
			res.push_back(cnt); 
		}
		return res; 
	}
	int find(vector<int>& root, int idx){
		while (idx != root[idx])
			idx = root[idx]; 
		return idx; 
	}
	void unify(vector<int>& root, int from, int to){
		int rf = find(root, from), rt = find(root, to); 
		if (rf == rt) return; 
		root[rf] = rt; 
	}
};


class Solution8 {
public:
	vector<int> numIslands2(int n, int m, vector<pair<int, int>>& positions) {
		vector<int> res; 
		vector<int> root(n*m, -1); 

		int cnt = 0; 
		for (auto& p : positions){
			int x = p.first, y = p.second; 
			cnt += 1; 
			root[x*m + y] = x*m + y; 
			for (auto d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				if (xx >= 0 && xx < n && yy >= 0 && yy < m && root[xx*m + yy]>0){
					int r1 = find(root, x*m + y), r2 = find(root, xx*m + yy);
					if (r1 != r2){
						root[r2] = r1; 
						cnt -= 1; 
					}
				}
			}
			res.push_back(cnt);
		}

		return res; 
	}

	int find(vector<int>& root, int i){
		while (root[i] != i)
			i = root[i]; 
		return i; 
	}

};


int main() {
	Solution3 a;
	Solution7 a2;

	vector<pair<int, int>> pos({ { 0, 0 }, { 0, 1 }, { 1, 2 }, { 2, 1 } });
	vector<pair<int, int>> pos2({ { 4, 3 }, { 2, 3 }, { 2, 1 }, { 5, 0 } });

	vector<int> b = a.numIslands2(6, 5, pos2); 

	for (auto i : b)
		cout << i << " "; 
	cout << endl << endl;
	
	b = a2.numIslands2(6, 5, pos2); 

	for (auto i : b)
		cout << i << " "; 
	cout << endl; 
}

