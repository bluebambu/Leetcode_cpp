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
	vector<int> minVertices(vector<vector<int>> board){
		unordered_map<int, unordered_set<int>> g; 
		unordered_map<int, int> indegree; 
		for (int i = 0; i < board.size(); ++i){
			for (int j = 0; j < board[i].size(); ++j){
				g[i].insert(board[i][j]); 
				indegree[i]; 
				indegree[board[i][j]] += 1; 
			}
		}

		vector<int> res; 
		unordered_set<int> v; 
		for (auto& p : indegree){
			int node = p.first, ind = p.second; 
			if (ind == 0){
				res.push_back(node); 
				dfs(g, node, v); 
			}
		}

		for (auto& p : indegree){
			int node = p.first, ind = p.second; 
			if (!v.count(node)){
				res.push_back(node); 
				dfs(g, node, v); 
			}
		}

		return res; 
	}

	void dfs(unordered_map<int, unordered_set<int>>& g, int n, unordered_set<int>& v){
		if (v.count(n))
			return; 

		v.insert(n); 
		for (int nxt : g[n])
			dfs(g, nxt, v); 
	}
};


int main(){
	Solution a;

	VVI g = {
		{1}, 
		{0}, 
		{3, 4}, 
		{},
		{},
		{6},
		{}
	}; 

	auto b = a.minVertices(g); 
	prt1Layer(b); 



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

