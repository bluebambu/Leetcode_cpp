// _template4.cpp : Defines the entry point for the console application.
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

typedef vector<int> VI; 
typedef vector<VI> VVI; 
typedef pair<int, int> PII; 

VVI dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 

// pass, 14% 
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
		int n = matrix.size(), m = matrix[0].size(); 
		queue<vector<int>> q; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (matrix[i][j] == 0)
					q.push({ i, j });
				else
					matrix[i][j] = INT_MAX; 
			}
		}

		while (!q.empty()){
			auto v = q.front(); 
			q.pop(); 
			int x = v[0], y = v[1]; 

			for (auto d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				if (xx >= 0 && xx < n&&yy >= 0 && yy<m&&matrix[xx][yy]>matrix[x][y] + 1){
					matrix[xx][yy] = matrix[x][y] + 1; 
					q.push({ xx, yy }); 
				}
			}
		}

		return matrix; 
    }
};

class Solution2 {
public:
	vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
		int n = matrix.size(), m = matrix[0].size(); 
		vector<vector<int>> dist(n, vector<int>(m, 0)); 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (matrix[i][j]){
					int up = i == 0 ? n+m : dist[i - 1][j],
						left = j == 0 ? m+n : dist[i][j - 1]; 
					dist[i][j] = min(up, left) + 1; 
				}
			}
		}

		prt2Layer(dist); 

		for (int i = n-1; i>=0; --i){
			for (int j = m - 1; j >= 0; --j){
				if (matrix[i][j]){
					int down = i == n-1 ? n+m : dist[i + 1][j],
						left = j == m-1 ? m+n : dist[i][j + 1], 
						cand = min(left, down) + 1; 
					dist[i][j] = min(dist[i][j], cand); 
				}
			}
		}

		return dist; 
	}
};


class Solution3 {
public:
	vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
		if (matrix.empty() || matrix[0].empty()) return{}; 
		int n = matrix.size(), m = matrix[0].size(); 
		queue<vector<int>> q; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (matrix[i][j] == 0)
					q.push({ i, j });
				else
					matrix[i][j] = INT_MAX; 
			}
		}

		while (q.size()){
			auto f = q.front(); 
			q.pop(); 
			int x = f[0], y = f[1]; 

			for (auto d : dirs){
				int xx = x + d[0], yy = y + d[1]; 
				if (xx >= 0 && xx < n&&yy >= 0 && yy<m&& matrix[xx][yy]>matrix[x][y]+1){
					matrix[xx][yy] = matrix[x][y] + 1; 
					q.push({ xx, yy }); 
				}
			}
		}

		return matrix; 
	}
};


int main(){
	Solution3 a;

	vector<vector<int>> mtx = {
		{ 0, 1, 1, 1 },
		{ 0, 1, 1, 1 },
		{ 0, 1, 1, 0 },
		{ 1, 1, 1, 0 },
	}; 

	auto d = a.updateMatrix(mtx); 
	prt2Layer(d); 


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6,
		new TreeNode(3, new TreeNode(1),
						new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
						new TreeNode(9,
		                               new TreeNode(10),
		                               nullptr)));
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

