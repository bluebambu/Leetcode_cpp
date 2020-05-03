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

template <typename T>
void vprt(vector<T> v){
	for (auto i : v)
		cout << v << " ";
	cout << endl;
}

template <typename T>
void vvprt(vector<vector<T>> v){
	for (auto i : v){
		for (auto j : i){
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <typename C>
void setprt(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
// Given n nodes labeled from 0 to n - 1 and a list of undirected edges(each edge 
// 	is a pair of nodes), write a function to find the number of connected components 
// 	in an undirected graph.

// Example 1:
// 0            3
// |		    |
// 1 -- - 2     4
// Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], return 2.

// Example 2 :
// 0            4
// |		    |
// 1 -- - 2 --- 3
// Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [3, 4]], return 1.
// Note :
// 	 You can assume that no duplicate edges will appear in edges.Since all edges are undirected, 
// 	 [0, 1] is the same as[1, 0] and thus will not appear together in edges.

// classic UF
class UF{
public:
	vector<int> root; 
	int sz;

	UF(int n) :root(n, -1) {}

	void unify(pair<int, int>& p){
		if (root[p.second] == -1){
			cout << "Invalid!" << endl; 
			return; 
		}
		root[p.second] = p.first; 
	}

	int findRoot(int n){
		while (root[n] != n){
			// int tmp = root[n]; 并不是必须的
			root[n] = root[root[n]];
			n = root[n]; // 可以直接这么跳着找， 路径压缩! 
			/// n = tmp;
		}
		return n; 
	}

	bool isCon(int n, int m){
		return findRoot(m) == findRoot(n); 
	}
};

// what if elem are strings and other non-number stuff? 
class ncUF{
public:
	unordered_map<string, int> mstr; 
	vector<int> vint; 
	int sz; 

	ncUF(int n) {}

	void unify(string s1, string s2){
		if (mstr.count(s1) == 0){
			mstr[s1] = vint.size(); 
			vint.push_back(0); 
		}
		if (mstr.count(s2) == 0){
			mstr[s2] = vint.size(); 
			vint.push_back(0);
		}
		vint[mstr[s1]] = vint[mstr[s2]]; 
	}

	int findRoot(string s){
		if (mstr.count(s) == 0){
			return -1; 
		}
		int idx = mstr[s]; 
		while (vint[idx] != idx){
			vint[idx] = vint[vint[idx]];
			idx = vint[idx];
		}
		return idx; 
	}

	int connected(string s1, string s2){

	}

};

// dfs
class Solution {
public:
	int countComponents(int n, vector<pair<int, int>>& edges) {
		int res = 0; 
		vector<vector<bool>> g(n, vector<bool>(n, false)); 

		for (auto& i : edges){
			g[i.first][i.second] = true; 
			g[i.second][i.first] = true; 
		}

		vector<bool> visited(n, false);

		for (int i = 0; i < n; ++i){
			if (!visited[i]){
				helper(g, i, visited);
				++res;
			}
		}
		return res; 
	}

	void helper(vector<vector<bool>>& g, int i, vector<bool>& visited){
		if (visited[i])
			return ; 

		visited[i] = true; 
		for (int j = 0; j < visited.size(); ++j){
			if (!visited[j] && (g[i][j] || g[j][i])){
				// visited[j] = true; 写在这里是不对的， 因为一次recursion， 应该只改变一次visited。 
				// 写在这里会把下一步给block住。： 
				helper(g, j, visited); 
			}
		}
	}
};




int main() {
	Solution a;
	vector<pair<int, int>> b = { { 0, 1 }, { 1, 2 }, { 3, 4 } }; 

	cout << a.countComponents(5, b) << endl; 

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

