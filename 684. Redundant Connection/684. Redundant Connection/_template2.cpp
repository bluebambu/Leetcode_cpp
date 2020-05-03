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

// pass
struct UF{
	int n; 
	vector<int> root, rank; 
	UF(int x) :n(x), root(n, 0), rank(n, 1){
		for (int i = 0; i < n; ++i)
			root[i] = i; 
	}

	int find(int i){
		while (i != root[i]){
			root[i] = root[root[i]]; 
			i = root[i]; 
		}
		return i;
	}

	void unify(int i, int j){
		int ri = find(i), rj = find(j);
		if (ri == rj)
			return; 
		if (rank[ri] > rank[rj]){
			root[ri] = rj; 
			rank[rj] += rank[ri]; 
		}
		else{
			root[rj] = ri; 
			rank[ri] += rank[rj]; 
		}
	}
};

class Solution {
public:
	vector<int> findRedundantConnection(vector<vector<int>>& edges) {
		int n = 0; 
		for (auto e : edges)
			n = max(n, max(e[0], e[1])); 

		UF uf(n+1); 
		for (auto e : edges){
			if (uf.find(e[0]) == uf.find(e[1]))
				return e; 
			uf.unify(e[0], e[1]); 
		}

		return{}; 
	}
};


class UF2{
	vector<int> core; 
public:
	UF2(int sz) :core(sz){
		for (int i = 0; i < sz; ++i){
			core[i] = i; 
		}
	}

	void unify(int i, int j){
		int ri = find(i), rj = find(j);
		if (ri == rj)
			return; 

		core[ri] = rj; 
	}

	int find(int i){
		while (core[i] != i){
			core[i] = core[core[i]]; 
			i = core[i]; 
		}
		return i; 
	}
};

class Solution2 {
public:
	vector<int> findRedundantConnection(vector<vector<int>>& edges) {
		int m = INT_MIN; 
		for (auto e : edges)
			m = max(m, e[1]); 

		UF2 uf(m); 
		for (int i = 0; i < edges.size(); ++i){
			vector<int>& c = edges[i]; 
			if (uf.find(c[0]-1) == uf.find(c[1]-1))
				return c; 
			uf.unify(c[0]-1, c[1]-1); 
		}

		return{}; 
	}
}; 


int main(){
	Solution a; 
	Solution2 a2; 

	vector<vector<int>> b = {
		{ 3, 7 }, { 1, 4 }, { 2, 8 }, { 1, 6 }, { 7, 9 }, { 6, 10 }, { 1, 7 }, { 2, 3 }, { 8, 9 }, { 5, 9 } 
	};

	auto c = a.findRedundantConnection(b); 
	prt1Layer(c);

	auto c2 = a2.findRedundantConnection(b); 
	prt1Layer(c2);
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

