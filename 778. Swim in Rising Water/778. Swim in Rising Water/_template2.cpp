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

vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
unordered_map<string, int> cache; 

class Solution {
public:
	string uid(int x, int y){
		return to_string(x) + "_" + to_string(y); 
	}

	string uid2(int x, int y, int z){
		return to_string(x) + "_" + to_string(y) + "_" + to_string(z); 
	}

	int swimInWater(vector<vector<int>>& grid) {
		unordered_set<string> v; 
		return dfs(grid, 0, 0, grid[0][0], v) - grid[0][0]; 
	}

	int dfs(vector<vector<int>>& grid, int x, int y, int h, unordered_set<string>& v){
		int n = grid.size(), m = grid[0].size(); 
		if (x == n - 1 && y == m - 1){
			return max(h, grid[x][y]); 
		}
		if (cache.count(uid2(x, y, h)))
			return cache[uid2(x, y, h)]; 

		v.insert(uid(x, y)); 
		int res = INT_MAX; 
		for (auto& d : dirs){
			int xx = x + d[0], yy = y + d[1]; 
			if (xx >= 0 && xx < n && yy >= 0 && yy < m && !v.count(uid(xx, yy))){
				int curh = max(h, grid[xx][yy]); 
				res = min(res, dfs(grid, xx, yy, curh, v)); 
			}
		}
		v.erase(uid(x, y)); 

		cache[uid2(x, y, h)] = res; 
		return res; 
	}
};

typedef pair<int, int> PII; 

class Solution2{
public:
	int index(int x, int y, int n){
		return x*n + y; 
	}
	int swimInWater(vector<vector<int>>& grid) {
		int n = grid.size(), m = grid[0].size(); 
		set<PII> pq; 
		pq.insert({ grid[0][0], index(0, 0, m) }); 
		unordered_set<int> v; 
		v.insert(index(0, 0, m)); 

		while (!pq.empty()){
			PII f = *(pq.begin()); 
			pq.erase(pq.begin()); 

			int h = f.first, x = f.second / n, y = f.second%n; 
			v.insert(index(x, y, m)); 

			for (auto& d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				if (xx >= 0 && xx < n && yy >= 0 && yy < m && !v.count(index(xx, yy, m))){
					PII old = { grid[xx][yy], index(xx, yy, m) }; 
					if (pq.count(old))
						pq.erase(pq.find(old)); 
					int curh = max(grid[xx][yy], h); 
					if (xx == n - 1 && yy == m - 1)
						return curh; 
					pq.insert({ curh, index(xx, yy, m) }); 
				}
			}
		}

		return -1; 
	}

};


class Solution3{
public:
	int index(int x, int y, int n){
		return x*n + y;
	}
	int swimInWater(vector<vector<int>>& grid) {
		int n = grid.size(), m = grid[0].size(); 
		set<PII> pq; 
		pq.insert({ grid[m][0], index(0, 0, m) }); 
		unordered_set<int> v; 
		v.insert(0); 

		while (!pq.empty()){
			PII f = *(pq.begin()); 
			pq.erase(pq.begin()); 

			int h = f.first, x = f.second / n, y = f.second%n; 

			for (auto& d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				int idx = index(xx, yy, m); 
				if (xx >= 0 && xx < n && yy >= 0 && yy < m && !v.count(idx)){
					v.insert(idx); 
					int curh = max(grid[xx][yy], h); 
					if (xx == n - 1 && yy == m - 1) return curh; 
					pq.insert({ curh, idx }); 
				}
			}
		}

		return -1; 
	}
}; 


// pass pq + bfs
class Solution4 {
public:
	int index(int x, int y, int m){
		return x*m + y;
	}
	int swimInWater(vector<vector<int>>& grid) {
		int n = grid.size(), m = grid[0].size(); 
		set<PII> pq; 
		pq.insert({ grid[0][0], 0 }); 
		unordered_set<int> v; 
		v.insert(0); 

		while (!pq.empty()){
			PII f = *(pq.begin()); 
			pq.erase(pq.begin()); 

			int h = f.first, x = f.second / n, y = f.second%n; 
			queue<int> q; 
			q.push(index(x, y, m)); 
			while (!q.empty()){
				int ff = q.front(); 
				q.pop();

				if (ff/n == n - 1 && ff%n == m - 1)
					return h; 

				for (auto& d : dirs){
					int xx = ff / n + d[0], yy = ff%n + d[1]; 
					if (xx >= 0 && xx < n && yy >= 0 && yy < m && !v.count(index(xx, yy, m))){
						v.insert(index(xx, yy, m)); 
						if (grid[xx][yy] < h)
							q.push(index(xx, yy, m));
						else
							pq.insert({ max(h, grid[xx][yy]), index(xx, yy, m) }); 
					}
				}
			}
		}
		return -1; 
	}
}; 


class Solution5 {
public:
	int index(int x, int y, int m){
		return x*m + y;
	}
	int mwimInWater(vector<vector<int>>& grid) {
		int n = grid.size(), m = grid[0].size(); 
		int l = -1, r = n*n-1; 
		while (l < r){
			int mid = l + (r - l) / 2;
			unordered_set<int> v; 
			if (valid(grid, 0, 0, mid, v))
				r = mid;
			else
				l = mid + 1; 
		}

		return r; 
	}

	bool valid(vector<vector<int>>& grid, int i, int j, int thr, unordered_set<int>& v){
		int n = grid.size(), m = grid[0].size(); 
		v.insert(index(i, j, m)); 
		for (auto& d : dirs){
			int x = i + d[0], y = j + d[1]; 
			if (grid[i][j]<= thr && x >= 0 && x < n && y >= 0 && y < m && !v.count(index(x, y, m)) && grid[x][y] <= thr){
				if (x == n - 1 && y == m - 1)
					return true; 
				if (valid(grid, x, y, thr, v))
					return true; 
			}
		}
		return false;
	}
};


class Solution7 {
public:
	int swimInWater(vector<vector<int>>& grid) {
		set<PII> pq; 

		int n = grid.size(), m = grid[0].size(); 
		vector<vector<bool>> visited(n, vector<bool>(m, false)); 
		add_pq(pq, 0, 0, grid); 
		int lastH = grid[0][0]; 

		PII cur; 
		while (!pq.empty()){
			while ((*(pq.begin())).first <= lastH){
				cur = *(pq.begin());
				pq.erase(pq.begin());
				int h = cur.first, i = cur.second;;
				int x = i / m, y = i%m;
				if (x == n - 1 && y == m - 1)
					return lastH;

				for (auto d : dirs){
					int xx = x + d[0], yy = y + d[1];
					if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&!visited[xx][yy]){
						visited[xx][yy] = true;
						add_pq(pq, xx, yy, grid);
					}
				}
			}

			lastH = (*(pq.begin())).first;
		}
		
		return lastH; 
	}

	int index(int x, int y, int m){
		return x*m + y;
	}

	void add_pq(set<PII>& pq, int x, int y, vector<vector<int>>& grid){
		pq.insert({ grid[x][y], index(x, y, grid[0].size()) }); 
	}
}; 

class Solution8 {
public:
	int swimInWater(vector<vector<int>>& grid) {
		int left = grid[0][0], right = maxH(grid) ; 

		while (left < right){
			int mid = left + (right - left) / 2; 
			if (can_not_pass(grid, mid))
				left = mid + 1;
			else
				right = mid; 
		}

		return left; 
	}

	int maxH(vector<vector<int>>& grid){
		int r = INT_MIN; 
		for (auto a : grid)
			for (auto b : a)
				r = max(r, b); 
		return r;
	}

	bool can_not_pass(vector<vector<int>>& grid, int h){
		queue<pair<int, int>> q; 
		int n = grid.size(), m = grid[0].size(); 
		vector<vector<bool>> visited(n, vector<bool>(m, false)); 

		q.push({ 0, 0 }); visited[0][0] = true; 

		while (!q.empty()){
			auto f = q.front(); 
			q.pop(); 
			int x = f.first, y = f.second; 

			for (auto d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&!visited[xx][yy] && grid[xx][yy] <= h){
					if (xx == n - 1 && yy == m - 1)
						return false; 
					visited[xx][yy] = true; 
					q.push({ xx, yy }); 
				}
			}
		}

		return true; 
	}
}; 

class Solution9 {
public:
	int swimInWater(vector<vector<int>>& grid) {
		int left = grid[0][0], right = maxH(grid) ; 

		while (left < right){
			int mid = left + (right - left) / 2; 
			if (can_not_pass(grid, mid))
				left = mid + 1;
			else
				right = mid; 
		}

		return left; 
	}

	int maxH(vector<vector<int>>& grid){
		int r = INT_MIN; 
		for (auto a : grid)
			for (auto b : a)
				r = max(r, b); 
		return r;
	}

	bool can_not_pass(vector<vector<int>>& grid, int h){
		queue<pair<int, int>> q; 
		int n = grid.size(), m = grid[0].size(); 
		vector<vector<bool>> visited(n, vector<bool>(m, false)); 

		q.push({ 0, 0 }); visited[0][0] = true; 

		while (!q.empty()){
			auto f = q.front(); 
			q.pop(); 
			int x = f.first, y = f.second; 

			for (auto d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&!visited[xx][yy] && grid[xx][yy] <= h){
					if (xx == n - 1 && yy == m - 1)
						return false; 
					visited[xx][yy] = true; 
					q.push({ xx, yy }); 
				}
			}
		}

		return true; 
	}
}; 

class Solution10 {
public:
	int swimInWater(vector<vector<int>>& grid) {
		int left = 0, right = 0; 
		for (auto i : grid)
			for (auto j : i)
				right = max(right, j); 

		while (left + 1 < right){
			int mid = left + (right - left) / 2; 
			if (canPass(grid, mid))
				right = mid;
			else
				left = mid;
		}

		return right; 
	}

	bool canPass(vector<vector<int>>& grid, int h){
		unordered_map<int, unordered_map<int, int>> cache; 
		int n = grid.size(), m = grid[0].size(); 
		vector<vector<bool>> v(n, vector<bool>(m, false)); 
		return canPass(grid, 0, 0, h, v, cache); 
	}
	bool canPass(vector<vector<int>>& grid, int i, int j, int h,
		vector<vector<bool>>& v, 
		unordered_map<int, unordered_map<int, int>>& cache
		){

		if (v[i][j])
			return cache[i][j]; 

		if (grid[i][j] > h)
			return false; 

		int n = grid.size(), m = grid[0].size(); 
		v[i][j] = true; 

		for (auto d : dirs){
			int x = i + d[0], y = j + d[1]; 
			if (x >= 0 && x < n&&y >= 0 && y < m&&!v[x][y] && grid[x][y]<=h){
				if (x == n - 1 && y == m - 1)
					return true; 
				
				if (canPass(grid, x, y, h, v, cache)){
					cache[x][y] = true; 
					return true; 
				}
			}
		}

		cache[i][j] = false; 
		return false; 
	}
}; 


class Solution11 {
public:
	int swimInWater(vector<vector<int>>& grid) {
		int left = grid[0][0], right = h(grid); 
		while (left < right){
			int mid = left + (right - left) / 2; 
			if (canReach(grid, mid))
				right = mid;
			else
				left = mid+1; 
		}
		return right; 
	}
	int h(vector<vector<int>>& g){
		int res = -1; 
		for (auto& r : g){
			for (auto& c : r)
				res = max(res, c); 
		}
		return res;
	}
	bool canReach(vector<vector<int>>& grid, int height){
		int n = grid.size(), m = grid[0].size(); 
		queue<vector<int>> q; 
		q.push({ 0, 0 }); 
		unordered_map<int, unordered_map<int, int>> v; 
		v[0][0] = 1; 

		while (!q.empty()){
			auto f = q.front(); 
			q.pop(); 
			int x = f[0], y = f[1]; 
			
			for (auto d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&!v[xx][yy] && grid[xx][yy] <= height){
					if (xx == n - 1 && yy == m - 1)
						return true; 
					v[xx][yy] = 1; 
					q.push({ xx, yy }); 
				}
			}
		}

		return false; 
	}
};


int main(){
	Solution8 a; 
	Solution11 a2; 

	vector<vector<int>> grid = { 
		{ 0, 1, 2, 3, 4 }, 
		{ 24, 23, 22, 21, 5 }, 
		{ 12, 13, 14, 15, 16 }, 
		{ 11, 17, 18, 19, 20 }, 
		{ 10, 9, 8, 7, 6 } 
	}; 

	vector<vector<int>> grid2 = {
		{ 0, 2 },
		{ 1, 3 }
	};

	cout << a.swimInWater(grid) << endl; 
	cout << a2.swimInWater(grid) << endl; 


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

