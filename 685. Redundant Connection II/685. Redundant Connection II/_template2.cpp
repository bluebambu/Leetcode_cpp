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

// wrong ans
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
	vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
		int n = 0;
		for (auto e : edges)
			n = max(n, max(e[0], e[1]));

		UF uf(n + 1);
		for (auto e : edges){
			if (uf.find(e[0]) == uf.find(e[1]) || uf.rank[e[0]]<uf.rank[e[1]])
				return e;
			uf.unify(e[0], e[1]);
		}

		return{};
	}
};


class Solution2 {
public:
	vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
		int n = edges.size(); 
		vector<int> parent(n + 1, 0); 
		vector<int> candA, candB; 
		for (auto& e : edges){
			if (parent[e[1]] != 0){
				candA = { parent[e[1]], e[1] }; 
				candB = e; 
				e[1] = 0; 
			}
			else
				parent[e[1]] = e[0]; 
		}

		for (int i = 0; i < n+1; ++i) parent[i] = i; 
		for (auto&e : edges){
			int p = e[0], c = e[1]; 
			if (root(p, parent) == root(c, parent)){
				if (candB.empty())
					return e; 
				return candA; 
			}
			parent[c] = p; 
		}
		return candB; 
	}

	int root(int i, vector<int>& paren){
		if (paren[i] != i)
			return root(paren[i], paren); 
		
		return i; 
	}
};

// wrong ans
class Solution22 {
public:
	vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
		int n = edges.size(); 
		vector<int> root(n, -1); 
		
		vector<int> candA, candB; 
		for (auto& e : edges){
			if (root[e[1]] != -1){
				candA = { root[e[1] - 1] + 1, e[1] };
				candB = e; 
				continue;; 
			}
			root[e[1]-1] = e[0]-1; 
		}
		if (candA == vector<int>()) return edges.back(); 
		if (hasCycle(root)) return candA; 
		else return candB; 
	}
	bool hasCycle(vector<int>& root){
		vector<int> uf(root.size(), 0); 
		for (int i = 0; i < root.size(); ++i)
			uf[i] = i; 

		for (int i = 0; i < root.size(); ++i){
			int child = i, parent = root[i]; 
			if (find(uf, child) == find(uf, parent))
				return false; 
			uf[child] = parent; 
		}
		return true; 
	}
	int find(vector<int>& uf, int i){
		return 0;  
	}
}; 


class Solution3 {
public:
	vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
		int n = edges.size();  
		vector<int> root(n + 1, 0); 
		vector<int> candA, candB; 
		for (int i = 0; i < n + 1; ++i) root[i] = i; 
		bool success = false; 
		for (auto& e : edges){
			if (root[e[1]] != e[1]){
				candA = e; 
				candB = { root[e[1]], e[1] }; 
				continue;;
			}
			root[e[1]] = e[0]; 
		}
		if (candA != vector<int>())
			edges.erase(remove(edges.begin(), edges.end(), candA), edges.end()); 

		for (int i = 0; i < n + 1; ++i) root[i] = i; 
		for (auto& e : edges){
			if (find(root, e[1]) == find(root, e[0])){
				if (candA == vector<int>())
					return e;
				else
					return candB; 
			}
			root[e[1]] = e[0]; 
		}

		return candA; 
	}
	int find(vector<int>& root, int i){
		while (root[i] != i)
			i = root[i]; 
		return i; 
	}
}; 

class Solution4 {
public:
	vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
		int n = edges.size(); 
		vector<int> parent(n + 1, -1), candA, candB;
		for (auto& e : edges){
			if (parent[e[1]] != -1){
				candA = e; 
				candB = { parent[e[1]], e[1] }; 
				e[1] = 0; 
				continue;
			}
			parent[e[1]] = e[0]; 
		}

		for (int i = 0; i < n + 1; ++i) parent[i] = i; 
		for (auto& e : edges){
			if (find(parent, e[0]) == find(parent, e[1])){
				if (candA.empty())
					return e;
				else
					return candB; 
			}
			parent[e[1]] = e[0]; 
		}
		return candA; 
	}
	int find(vector<int>& parent, int i){
		while (i != parent[i]){
			parent[i] = parent[parent[i]]; 
			i = parent[i]; 
		}
		return i; 
	}
};

int main(){
	Solution4 a; 
	vector<vector<int>> c = { { 2, 1 }, { 3, 1 }, { 4, 2 }, { 1, 4 } }; 
	vector<vector<int>> cc = { { 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 1 }, { 1, 5 } }; 
	auto b = a.findRedundantDirectedConnection(cc); 
	prt1Layer(b); 


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

