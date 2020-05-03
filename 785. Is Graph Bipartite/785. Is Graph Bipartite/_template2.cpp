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


class Solution {
public:
	bool isBipartite(vector<vector<int>>& graph) {
		int n = graph.size();
		vector<vector<int>> g; 

		for (int i = 0; i < graph.size(); ++i){
			for (auto j : graph[i])
				g[i][j] = g[j][i] = 1;
		}

		vector<int> status(n, 0); 

		for (int i = 0; i < n; ++i){
			if (status[i] == 0 && !dfs(i, g, status, 1))
				return false; 
		}

		return true; 
	}

	bool dfs(int cur, vector<vector<int>>& g, vector<int>& status, int st){
		status[cur] = st; 
		for (int i = 0; i < g.size(); ++i){
			if (g[cur][i] && status[i] == st)
				return false; 
			if (g[cur][i] && status[i] == 0){
				if (!dfs(i, g, status, -1 * st))
					return false; 
			}
		}
		return true; 
	}
};

// wrong solution, I thought the graph is a matrix boolean map. But it is not... 
class Solution2 {
public:
	bool isBipartite(vector<vector<int>>& graph) {
		int n = graph.size(); 
		vector<int> status(n, -1); 
		queue<int> q; 
		q.push(0); ; status[0] = 0; 

		while (!q.empty()){
			int f = q.front(); 
			q.pop(); 
			int cur_st = status[f]; 

			for (int i = 0; i < n; ++i){
				if (graph[f][i] && f != i){
					if (status[i] == cur_st)
						return false; 
					if (status[i] == -1){
						status[i] = (!cur_st); 
						q.push(i); 
					}
				}
			}
		}

		return true; 
	}
};


class Solution3 {
public:
	bool isBipartite(vector<vector<int>>& graph) {
		unordered_map<int, unordered_set<int>> g; 
		unordered_map<int, int> status; 
		for (int i = 0; i < graph.size(); ++i){
			for (int j = 0; j < graph[i].size(); ++j){
				g[i].insert(graph[i][j]); 
			}
		}

		for (int i = 0; i < graph.size(); ++i){
			if (status[i] == 0){
				status[i] = 1; 
				if (!check(g, i, status))
					return false;
			}
		}
		return true;
	}

	bool check(unordered_map<int, unordered_set<int>>& g, int i, unordered_map<int, int>& status){
		int curstate = status[i]; 
		for (int nxt : g[i]){
			if (status[nxt] == curstate)
				return false; 
			if (status[nxt] == 0){
				status[nxt] = -1 * curstate; 
				if (!check(g, nxt, status))
					return false;
			}
		}
		return true; 
	}
}; 

class Solution4 {
public:
	bool isBipartite(vector<vector<int>>& graph) {
		int n = graph.size(); 
		vector<int> state(n, 0); 

		for (int i = 0; i < n; ++i){
			if (state[i] == 0){
				state[i] = 1; 
				if (!check(graph, i, state))
					return false; 
			}
		}
		return true; 
	}
	bool check(vector<vector<int>>& g, int i, vector<int>& state){
		int c = state[i]; 
		for (int nxt : g[i]){
			if (state[nxt] == c)
				return false; 
			if (state[nxt] == 0){
				state[nxt] = -1 * c; 
				if (!check(g, nxt, state))
					return false; 
			}
		}
		return true; 
	}
}; 

// wrong ans. BFS only consider one connected component. It fails if there are multiple.  
class Solution5 {
public:
	bool isBipartite(vector<vector<int>>& graph) {
		int n = graph.size(); 
		vector<int> status(n, 0); 
		queue<int> q; 
		status[0] = 1; 
		q.push(0); 

		while (!q.empty()){
			int f = q.front(); 
			q.pop(); 
			int curstate = status[f]; 

			for (int nxt : graph[f]){
				if (status[nxt] == curstate)
					return false; 
				if (status[nxt] == 0){
					status[nxt] = -1 * curstate; 
					q.push(nxt); 
				}
			}
		}

		return true; 
	}
};

class Solution6 {
public:
	unordered_map<int, int> color;
	bool isBipartite(vector<vector<int>>& graph) {
		for (int i = 0; i < graph.size(); ++i){
			if (color[i] == 0){
				if (dfs(graph, i, 1) == false)
					return false; 
			}
		}
		return true; 
	}
	bool dfs(vector<vector<int>>& g, int i, int col){
		color[i] = col; 
		for (int nxt : g[i]){
			if (color[nxt] == col)
				return false; 
			if (color[nxt]==-1*col)
				continue;
			if (!dfs(g, nxt, -1 * col))
				return false; 
		}
		return true; 
	}
}; 

int main(){
	Solution6 a; 
	Solution3 a2; 

	vector<vector<int>> m = {
		{ 1, 3 },
		{ 0, 2 },
		{ 1, 3 },
		{ 0, 2 }
	};

	cout << a2.isBipartite(m) << endl; 
	cout << a.isBipartite(m) << endl; 


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

