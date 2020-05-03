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


template<typename T>
void prnt2layer(T c){
	for (auto i : c){
		for (auto j : i){
			cout << j << " "; 
		}
		cout << endl;  
	}
}
// Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb.
// The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed.
// Note that you can only put the bomb at an empty cell.

// Example:

// For the given grid

// 0 E 0 0
// E 0 W E
// 0 E 0 0

// return 3. (Placing a bomb at(1, 1) kills 3 enemies)

class Solution {
public:
	int maxKilledEnemies(vector<vector<char>>& grid) {
		if (grid.size() == 0 || grid[0].size() == 0)
			return 0; 
		int n = grid.size(); 
		int m = grid[0].size(); 

		vector<vector<char>> up = grid, down = up, left = up, right = up;
		vector<vector<int>> empty; 

		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				(j == 0 || grid[i][j] == 'W') ? left[i][j] = (grid[i][j] == 'E') : left[i][j] = left[i][j - 1] + (grid[i][j] == 'E');
				(j == 0 || grid[i][m - j - 1] == 'W') ? right[i][m - j - 1] = (grid[i][m - j - 1] == 'E') : right[i][m - j - 1] = right[i][m - j] + (grid[i][m - j - 1] == 'E');
				(i == 0 || grid[i][j] == 'W') ? up[i][j] = (grid[i][j] == 'E') : up[i][j] = up[i - 1][j] + (grid[i][j] == 'E');
				(i == 0 || grid[n - i - 1][j] == 'W') ? down[n - i - 1][j] = (grid[n - i - 1][j] == 'E') : down[n - i - 1][j] = down[n - i][j] + (grid[n - i - 1][j] == 'E');

				if (grid[i][j] == '0'){
					empty.push_back({ i, j }); 
				}
			}
		}

		int res = 0; 
		for (auto pos : empty){
			int x = pos[0], y = pos[1]; 
			res = max(res, left[x][y] + right[x][y] + up[x][y] + down[x][y]); 
		}
		return res; 
	}
};


class Solution2 {
public:
	int maxKilledEnemies(vector<vector<char>>& grid) {
		if (grid.empty() || grid[0].empty())
			return 0; 

		int n = grid.size(), m = grid[0].size(); 
		vector<vector<int>> up(n, vector<int>(m, 0)), down = up, left = up, right = up; 
		
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (i == 0){
					up[i][j] = 0;
				}
				else{
					up[i][j] = (grid[i - 1][j] == 'W') ? 0 : up[i - 1][j] + (grid[i - 1][j] == 'E'); 
				}

				if (j == 0){
					left[i][j] = 0; 
				}
				else{
					left[i][j] = (grid[i][j - 1] == 'W') ? 0 : left[i][j - 1] + (grid[i][j - 1] == 'E');
				}
			}
		}

		for (int i = n-1; i >= 0; --i){
			for (int j = m-1; j >= 0; --j){
				if (i == n-1){
					down[i][j] = 0;
				}
				else{
					down[i][j] = (grid[i + 1][j] == 'W') ? 0 : down[i + 1][j] + (grid[i + 1][j] == 'E');
				}

				if (j == m-1){
					right[i][j] = 0;
				}
				else{
					right[i][j] = (grid[i][j + 1] == 'W') ? 0 : right[i][j + 1] + (grid[i][j + 1] == 'E');
				}
			}
		}

		prnt2layer(up); 
		prnt2layer(down);
		prnt2layer(left); 
		prnt2layer(right); 

		int res = INT_MIN; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (grid[i][j] == '0'){
					res = max(res, (up[i][j] + down[i][j] + left[i][j] + right[i][j])); 
				}
			}
		}

		return res==INT_MIN ? 0 : res; 
	}
};


int main()
{
	Solution a;
	Solution2 a2;

	vector<vector<char>> b = {
		{ '0', 'E', '0', '0' },
		{ 'E', '0', 'W', 'E' },
		{ '0', 'E', '0', '0' },
	}; 

	vector<vector<char>> c = { { 'E' } }; 

	vector<vector<char>> d = { 
		{ 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E' }, 
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' }, 
		{ 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E' } 
	};

	cout << a.maxKilledEnemies(d) << endl; 
	cout << a2.maxKilledEnemies(d) << endl;

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

