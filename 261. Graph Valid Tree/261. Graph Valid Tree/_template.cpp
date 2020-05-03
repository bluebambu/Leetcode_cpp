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

// Given n nodes labeled from 0 to n - 1 and a list of undirected edges(each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.
// 
// For example :
// 
// Given n = 5 and edges = [[0, 1], [0, 2], [0, 3], [1, 4]], return true.
// 
// Given n = 5 and edges = [[0, 1], [1, 2], [2, 3], [1, 3], [1, 4]], return false.
// 
// Hint :
// 
// 	 Given n = 5 and edges = [[0, 1], [1, 2], [3, 4]], what should your return ? Is this case a valid tree ?
// 	 According to the definition of tree on Wikipedia : “a tree is an undirected graph in which any two vertices are connected by exactly one path.In other words, any connected graph without simple cycles is a tree.”
// 
//  Note : you can assume that no duplicate edges will appear in edges.Since all edges are undirected, [0, 1] is the same as[1, 0] and thus will not appear together in edges.

// dfs的解法就是， 1. 没有环  2. 没有 unconnected component。 第一个用visited array 或者hashtable记录， 第二个也可以用visited来表示
// 图的题目， 一开始要搞一个邻接表， 可以用vector， 也可以hashtable， 也可以linkedlist， 也可以matrix。 这里因为都是int， 所以vector<int> 就可以

// passed,beat 23.82%
class Solution {
public:
	bool validTree(int n, vector<pair<int, int>>& edges) {
		vector<vector<int>> graph(n, vector<int>());
		vector<bool> visited(n, false); 

		for (auto edge : edges){
			graph[edge.first].push_back(edge.second); 
			graph[edge.second].push_back(edge.first); 
		}

		if (!dfs(graph, visited, 0, -1))
			return false; 

		for (auto i : visited)
			if (!i)
				return false; 
		return true; 
	}

	bool dfs(vector<vector<int>>& graph, vector<bool>& visited, int cur, int pre){
		if (visited[cur])
			return false; 
		visited[cur] = true; 

		for (auto i : graph[cur])
			if (i!=pre)	   // 我本来以为pre是为了防止child指向自己的，实际上不对，是为了rule out undirected connection，
							// 即不让 bidirection connection 影响 dfs。 比如 【0，1】， 0 dfs 到1， 1按理说应该dfs回0， 
							// 但是 0 是visited， 会报错， 这时pre就把这种错误消除掉。  
				if (!dfs(graph, visited, i, cur))
					return false; 
		return true; 
	}
};


// passed,  with adj matrix, but very slow, beat 0.25% .........
class Solution {
public:
	bool validTree(int n, vector<pair<int, int>>& edges) {
		vector<vector<bool>> adj(n, vector<bool>(n, false)); 
		vector<bool> visited(n, false); 

		for (auto e : edges){
			adj[e.first][e.second] = true; 
			adj[e.second][e.first] = true; 
		}

		if (!dfs(adj, visited, 0, -1))
			return false; 

		for (auto i : visited)
			if (!i)
				return false; 

		return true; 
	}

	bool dfs(vector<vector<bool>>& adj, vector<bool>& visited, int cur, int pre)	{
		if (visited[cur])
			return false; 
		visited[cur] = true; 
		for (int i = 0; i < adj[cur].size(); ++i){
			if (i != pre){
				if (adj[cur][i] && !dfs(adj, visited, i, cur))
					return false; 
			}
		}
		return true; 
	}
};

// bfs,   // 错错错！！！
class Solution {
public:
	bool validTree(int n, vector<pair<int, int>>& edges) {
		vector<vector<int>> g(n, vector<int>()); 
		vector<bool> visited(n, false); 

		for (auto i : edges){
			g[i.first].push_back(i.second); 
			g[i.second].push_back(i.first);
		}

		if (!bfs(g, visited, 0))
			return false; 

		for (auto i : visited)
			if (!i)
				return false; 

		return true; 
	}

	bool bfs(vector<vector<int>>& g, vector<bool>& visited, int cur){
		queue<int> q; 
		q.push(cur); 
		visited[cur] = true; 
		int pre = -1; 

		while (!q.size()){  // 错错错！！！
			int tmp = q.front(); 
			q.pop();
			int sz = q.size(); 

			for (int j = 0; j < sz; ++j){
				for (auto i : g[tmp]){
					if (i != pre){
						if (visited[i])
							return false;
						else{
							visited[i] = true;
							q.push(i);
						}
					}
				}
			}

			pre = tmp; 
		}


		/*
		while (!q.size()){
			int tmp = q.front(); 
			q.pop(); 

			for (auto a : g[tmp]){
				if (a != tmp){	// 这么写是错误的， 错误得理解了pre的意义！！！
					if (visited[a])
						return false; 
					else{
						visited[a] = true; 
						q.push(a); 
					}
				}
			}
		}
		*/

		return true; 
	}

};


// bfs , pass
class Solution {
public:
	bool validTree(int n, vector<pair<int, int>>& edges) {
		vector<int> status(n, 0); 
		vector<vector<int>> g(n, vector<int>()); 
		for (auto i : edges){
			g[i.first].push_back(i.second); 
			g[i.second].push_back(i.first); 
		}

		int count = 0;
		if (!bfs(g, status, 0, count))
			return false; 

		return count == n; 

	}

	bool bfs(vector<vector<int>>& g, vector<int>& status, int cur, int& count){
		queue<int> q; 
		q.push(cur); 
		status[cur] = 1; 

		while (!q.empty()){
			int tmp = q.front(); 
			q.pop();
			++count;

			for (auto i : g[tmp]){
				if (status[i] == 1)
					return false; 
				else if (status[i] == 0){
					status[i] = 1;
					q.push(i);
				}
			}

			status[tmp] = 2; 
		}
	}
};



// union-find , pass
// quick-union, 69%, path compression
class Solution {
public:

	vector<int> root;

	bool validTree(int n, vector<pair<int, int>>& edges) {
		root = vector<int>(n, 0); 
		for (int i = 0; i < n; ++i){
			root[i] = i; 
		}

		for (auto i : edges){
			int fR = find(i.first), sR = find(i.second); 
			if (fR == sR)
				return false; 
			root[fR] = sR;
		}

		for (int i = root[0], j = 1; j < n; ++j)
			if (find(root[j]) != find(i))
				return false; 
		return true; 
	}

	int find(int i){
		while (i != root[i]){
			root[i] = root[root[i]]; 
			i = root[i]; 
		}
		return i; 
	}

};

// 最快的 uf
class Solution {
public:
	bool validTree(int n, vector<pair<int, int>>& edges) {
		vector<int> roots(n, -1);
		for (auto a : edges) {
			int x = find(roots, a.first), y = find(roots, a.second);
			if (x == y) return false;
			roots[x] = y;
		}

		return edges.size() == n - 1;	// 判定条件很重要！！
	}

	int find(vector<int> &roots, int i) {
		while (roots[i] != -1) 
			i = roots[i];
		return i;
	}
};



int main()
{
	Solution a;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/

	a.flatten(tree);


}

