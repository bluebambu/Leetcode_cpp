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
	int islandPerimeter(vector<vector<int>>& grid) {
		int res = 0; 
		queue<vector<int>> q; 
		int n = grid.size(); 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < grid[i].size(); ++j){
				if (grid[i][j] == 1){
					queue<vector<int>> q; 
					q.push({ i, j }); 
					grid[i][j] = 2;

					while (!q.empty()){
						vector<int> f = q.front(); 
						q.pop(); 
						int x = f[0], y = f[1]; 

						for (auto d : dirs){
							int xx = x + d[0], yy = y + d[1]; 
							if (xx < 0 || xx >= n || yy < 0 || yy >= grid[xx].size() || grid[xx][yy] == 0)
								res += 1; 
							else if (grid[xx][yy] == 1){
								grid[xx][yy] = 2; 
								q.push({ xx, yy });
							}
						}


						prt2Layer(grid); 
					}
				}
			}
		}

		return res; 
	}
};



class Solution2 {
public:
	int islandPerimeter(vector<vector<int>>& grid) {
		queue<vector<int>> q; 
		for (int i = 0; i < grid.size(); ++i){
			for (int j = 0; j < grid[0].size(); ++j){
				if (grid[i][j] == 1){
					return bfs(grid, i, j); 
				}
			}
		}
		return -1; 
	}
	int bfs(vector<vector<int>>& g, int i, int j){
		int res = 0; 
		int n = g.size(), m = g[0].size(); 
		queue<vector<int>> q; 
		q.push({ i, j }); 
		g[i][j] = 2; 

		while (!q.empty()){
			auto f = q.front(); 
			q.pop(); 
			int x = f[0], y = f[1]; 
			for (auto d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				if (xx < 0 || xx >= n || yy < 0 || yy >= m || g[xx][yy] == 0)
					res += 1; 
				else if (g[xx][yy] == 1){
					g[xx][yy] = 2; 
					q.push({ xx, yy }); 
				}
			}
		}
		return res; 
	}
};



int main(){
	Solution2 a; 

	vector<vector<int>> g = { { 1, 1 }, { 1, 1 } };

	cout << a.islandPerimeter(g) << endl; 


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

