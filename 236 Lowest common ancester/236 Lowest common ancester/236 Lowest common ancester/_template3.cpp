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

vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 


class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (!root) return nullptr; 
		TreeNode *left = lowestCommonAncestor(root->left, p, q),
			*right = lowestCommonAncestor(root->right, p, q); 

		if (root == p || root == q || (left && right))
			return root;
		else if (left || right)
			return left ? left : right;
		else
			return nullptr; 
	}
};


class Solution2 {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		TreeNode *tgt = nullptr; 
		dfs(root, p, q, tgt); 
		return tgt; 
	}

	bool dfs(TreeNode*root, TreeNode*p, TreeNode*q, TreeNode*& tgt){
		if (!root)
			return nullptr; 

		bool left = dfs(root->left, p, q, tgt),
			right = dfs(root->right, p, q, tgt); 

		if (root == p || root == q || (left && right))
			tgt = root; 
		
		return left || right || root == p || root == q; 
	}
};


class Solution3 {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (root == p || root == q || !root)
			return root; 

		TreeNode *l = lowestCommonAncestor(root->left, p, q),
			*r = lowestCommonAncestor(root->right, p, q); 

		if (l && r)
			return root;
		else if (l || r)
			return l ? l : r;
		else
			return nullptr;
	}
}; 


class Solution4 {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		TreeNode* res=nullptr; 
		lca(root, p, q, res); 
		return res;
	}
	bool lca(TreeNode* n, TreeNode*p, TreeNode*q, TreeNode*& res){
		if (!n)
			return false; 

		bool left = lca(n->left, p, q, res), right = lca(n->right, p, q, res); 
		if (n == p || n==q && (right || left)){
			res = n; 
			return true; 
		}
		if (left && right){
			res = n; 
			return true; 
		}
		if (n == p || n == q || left || right)
			return true; 

		return false; 
	}
}; 



int main(){
	Solution4 a;

	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));

	TreeNode *p = new TreeNode(7), *q = new TreeNode(4, nullptr, p); 
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
													 new TreeNode(4)),
									 new TreeNode(8, nullptr, q));
	/*      6
		3       8
	1    4   7    9
	*/

	auto r = a.lowestCommonAncestor(tree, p, q); 

	cout << r->val << endl; 




	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

