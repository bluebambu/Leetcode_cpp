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
// For a undirected graph with tree characteristics, we can choose any node as the root.The result 
// graph is then a rooted tree.Among all possible rooted trees, those with minimum height are called 
// minimum height trees(MHTs).Given such a graph, write a function to find all the MHTs and return a 
// list of their root labels.

// Format
// The graph contains n nodes which are labeled from 0 to n - 1. You will be given the number n and a 
// list of undirected edges(each edge is a pair of labels).
// You can assume that no duplicate edges will appear in edges.Since all edges are undirected, [0, 1] 
// is the same as[1, 0] and thus will not appear together in edges.

// Example 1:
// Given n = 4, edges = [[1, 0], [1, 2], [1, 3]]
//   0
//   |
//   1
//  / \
// 2   3
// return[1]

// Example 2:
// Given n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]
// 0  1  2
// \ | /
//   3
//   |
//   4
//   |
//   5
// return[3, 4]

// Note:
// 	(1) According to the definition of tree on Wikipedia : “a tree is an undirected graph in 
// 		which any two vertices are connected by exactly one path.In other words, any connected 
// 		graph without simple cycles is a tree.”
// 	(2) The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.


// finally pass AC! 
class Solution {
public:
	vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
		if (edges.size() == 0)
			return vector<int>(1); 

		// undirectional graph
		vector<unordered_set<int>> g(n, unordered_set<int>(0)); 
		// indegree to decide if i is the most outside vertex or not
		vector<int> degree(n, 0); 
		for (auto p : edges){
			g[p.first].insert(p.second);
			g[p.second].insert(p.first);
			++degree[p.first];
			++degree[p.second]; 
		}

		// the num of vertex that has been visited. 
		int vNum = 0;

		vector<bool> visited(n, false); 
		queue<int> q; 
		for (size_t i = 0; i < degree.size(); ++i){
			if (degree[i] == 1){
				q.push(i);
				visited[i] = true; 
				++vNum; 
			}
		}


		// condition is hard to think! Consider the termination condition!!!
		while (!((n - vNum) ==0 && q.size()<3)){
			int sz = q.size(); 
			for (int i = 0; i < sz; ++i){
				int front = q.front(); 
				q.pop(); 

				for (auto i : g[front]){
					// need to update indegree over running time!!!
					--degree[front]; 
					--degree[i]; 

					// you should only enqueue those degree==1 or ==0 vertex!! 
					if (!visited[i] && degree[i]<=1){
						visited[i] = true; 
						q.push(i);
						++vNum;
					}
				}
			}
		}

		// the last one or two vertex in queue should be the answer!!
		vector<int> res; 
		while (q.size()){
			res.push_back(q.front());
			q.pop();
		}
		return res;
	}
}; 


//pass AC, visited array is not needed. 
class Solution2 {
public:
	vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges) {
		vector<vector<bool>> g(n, vector<bool>(n, false));
		vector<int> degree(n, 0);
		for (auto i : edges){
			g[i.first][i.second] = g[i.second][i.first] = true;
			degree[i.first] += 1;
			degree[i.second] += 1;
		}

		queue<int> q;
		for (int i = 0; i < degree.size(); ++i){
			if (degree[i] == 1)
				q.push(i);
		}

		while (!q.empty()){
			vector<int> curSet;
			int sz = q.size();

			for (int i = 0; i < sz; ++i){
				int f = q.front();
				q.pop();
				curSet.push_back(f);

				for (int j = 0; j < n; ++j){
					if (g[f][j] && degree[j]){
						degree[f] -= 1;
						degree[j] -= 1;
						if (degree[j] == 1){
							q.push(j);
						}
					}
				}
			}
			if (q.empty())
				return curSet;
		}

		return{ 0 };
	}
};





int main()
{
	Solution a;

	vector<pair<int, int>> t = { { 1, 0 }, { 1, 2 }, { 1, 3 } }; 

	auto b = a.findMinHeightTrees(4, t);

	setprt(b);

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

