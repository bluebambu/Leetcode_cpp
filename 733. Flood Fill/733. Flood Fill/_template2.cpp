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
	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
		unordered_set<int> v; 
		dfs(image, sr, sc, newColor, v); 
		return image; 
	}

	void dfs(vector<vector<int>>& image, int i, int j, int newc, unordered_set<int>& v){
		int n = image.size(), m = image[0].size(); 
		int h = i*m + j; 
		v.insert(i*m + j); 

		for (auto& d : dirs){
			int x = i + d[0], y = j + d[1]; 
			if (x >= 0 && x<n && y >= 0 && y<m && image[x][y] == image[i][j] && !v.count(x*m+y))
				dfs(image, x, y, newc, v); 
		}
		image[i][j] = newc; 
	}
};

typedef pair<int, int> PII; 

class Solution2 {
public:
	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
		int n = image.size(), m = image[0].size(); 
		int pv = image[sr][sc]; 
		image[sr][sc] = newColor; 
		queue<PII> q; 
		q.push({ sr, sc }); 
		unordered_set<int> v; 
		v.insert(sr*m + sc); 

		while (!q.empty()){
			PII f = q.front(); 
			q.pop(); 

			int i = f.first, j = f.second; 
			for (auto& d : dirs){
				int x = i + d[0], y = j + d[1]; 
				int idx = x*m + y; 
				if (x >= 0 && x < n && y >= 0 && y < m && !v.count(idx) && image[x][y]==pv){
					v.insert(idx); 
					image[x][y] = newColor; 
					q.push({ x, y }); 
				}
			}
		}

		return image; 
	}
}; 

class Solution3 {
public:
	vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
		int oldColor = image[sr][sc]; 
		queue<pair<int, int>> q; 
		int n = image.size(), m = image[0].size(); 
		vector<vector<bool>> visited(n, vector<bool>(m, false)); 
		image[sr][sc] = newColor; 

		q.push({ sr, sc }); 
		visited[sr][sc] = true; 

		while (!q.empty()){
			auto f = q.front(); 
			q.pop();
			int x = f.first, y = f.second; 

			for (auto d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&!visited[xx][yy] && image[xx][yy] == oldColor){
					image[xx][yy] = newColor; 
					q.push({ xx, yy }); 
				}
			}
		}

		return image; 
	}
}; 

// pass
class Solution4 {
public:
	vector<vector<int>> floodFill(vector<vector<int>> image, int sr, int sc, int newColor) {
		int n = image.size(), m = image[0].size(); 
		vector<vector<bool>> visited(n, vector<bool>(m, false)); 
		visited[sr][sc] = true;
		dfs(image, sr, sc, newColor, visited); 
		return image; 
	}

	void dfs(vector<vector<int>>& image, int x, int y, int newColor, vector<vector<bool>>& v){
		int n = image.size(), m = image[0].size(); 
		int olccolor = image[x][y];
		image[x][y] = newColor; 
		for (auto d : dirs){
			int xx = x + d[0], yy = y + d[1]; 
			if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&!v[xx][yy] && image[xx][yy] == olccolor){
				v[xx][yy] = true;
				dfs(image, xx, yy, newColor, v); 
			}
		}
	}
}; 


class Solution5 {
public:
	vector<vector<int>> floodFill(vector<vector<int>> image, int sr, int sc, int newColor) {
		vector<vector<int>> res; 
		int n = image.size(), m = image[0].size(); 
		fill(image, sr, sc, image[sr][sc], newColor, res); 
		return image; 
	}
	void fill(vector<vector<int>>& image, int i, int j, int oldColor, int newColor, vector<vector<int>>& res){
		if (image[i][j] != oldColor)
			return; 

		int n = image.size(), m = image[0].size(); 
		image[i][j] = newColor; 
		res.push_back({ i, j }); 

		for (auto d : dirs){
			int x = i + d[0], y = j + d[1]; 
			if (x >= 0 && x < n&&y >= 0 && y < m&&image[x][y] == oldColor)
				fill(image, x, y, oldColor, newColor, res); 
		}
	}
}; 

int main(){
	Solution4 a; 
	Solution5 a2; 

	vector<vector<int>> i = {
		{1,1,1},
		{1,1,0},
		{1,0,1}
	};

	vector<vector<int>> ii = {
		{0,0,0},
		{0,0,0},
	};
	auto c = a.floodFill(ii, 0, 0, 2); 

	prt2Layer(c);

	cout << "=======\n"; 

	c = a2.floodFill(ii, 0, 0, 2); 

	prt2Layer(c);


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

