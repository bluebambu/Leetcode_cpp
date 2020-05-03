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


class Solution {
public:
	vector<int> shortest(vector<vector<string>> stores, vector<string> interest){
		unordered_map<string, vector<int>> intst_pos(interest.begin(), interest.end()); 
		int n = stores.size(), m = stores[0].size(); 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (intst_pos.count(stores[i][j])){
					intst_pos[stores[i][j]] = { i, j }; 
				}
			}
		}

		vector<vector<int>> dist(n, vector<int>(m, 0)); 
		for (auto& p : intst_pos){
			auto loc = p.second; 
			bfs(loc, dist); 
		}

		int minDist = INT_MAX;
		vector<int> minloc = { 0, 0 };
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (dist[i][j] < minDist){
					minDist = dist[i][j]; 
					minloc = { i, j }; 
				}
			}
		}
		return minloc; 
	}
	void bfs(vector<int>& pos, vector<vector<int>>& dist){
		int n = dist.size(), m = dist[0].size(); 
		queue<vector<int>> q; 
		set<vector<int>> v; 
		q.push(pos); 
		v.insert(pos); 
		int d = 0; 

		while (!q.empty()){
			int sz = q.size(); 
			while (sz--){
				auto f = q.front(); 
				q.pop(); 
				int x = f[0], y = f[1]; 
				dist[x][y] += d; 

				for (auto d : dirs){
					int xx = x + d[0], yy = y + d[1]; 
					if (xx >= 0 && xx < n&&yy >= 0 && yy < m&&!v.count({ xx, yy })){
						v.insert({ xx, yy }); 
						q.push({ xx, yy }); 
					}
				}
			}
			++d; 
		}
	}

	void dfs(vector<int>& pos, vector<vector<int>>& dist){
		int n = dist.size(), m = dist[0].size(); 
		vector<vector<int>> v(n, vector<int>(m, 0)); 
		dfs(pos[0], pos[1], dist, 0, v); 
	}
	void dfs(int x, int y, vector<vector<int>>& dist, int val, vector<vector<int>>& v){
		int n = dist.size(), m = dist[0].size();
		if (x < 0 || x >= n || y < 0 || y >= m || v[x][y])return;

		dist[x][y] += val; 
		v[x][y] = 1; 

		dfs(x + 1, y, dist, val + 1, v); 
		dfs(x - 1, y, dist, val + 1, v); 
		dfs(x , y + 1, dist, val + 1, v); 
		dfs(x , y - 1, dist, val + 1, v); 
	}
};


int main(){
	Solution a;

	vector<int> b = { 1, 2, 3, 4, 5 }; 



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

