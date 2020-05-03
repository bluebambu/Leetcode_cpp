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
	TreeNode* lca(TreeNode* root){
		int dep;
		return lcaOfDeep(root, dep);
	}

	TreeNode* lcaOfDeep(TreeNode* node, int& lvl){
		if (!node){
			lvl = 0;
			return nullptr;
		}

		int ldep, rdep;
		TreeNode* left = lcaOfDeep(node->left, ldep);
		TreeNode* right = lcaOfDeep(node->right, rdep);
		lvl = 1 + max(ldep, rdep);

		if (ldep == rdep) return node;
		else if (ldep < rdep) return right;
		else return left;
	}
};


class Solution2 {
public:
	TreeNode* lca(TreeNode* root){
		return lcaOfDeep(root).first;
	}

	pair<TreeNode*, int> lcaOfDeep(TreeNode* node){
		if (!node)
			return{ nullptr, 0 };
		auto left = lcaOfDeep(node->left),
			right = lcaOfDeep(node->right);

		if (left.second == right.second)
			return{ node, 1 + max(left.second, right.second) };
		else if (left.second < right.second)
			return{ right.first, 1 + right.second };
		else
			return{ left.first, 1 + left.second };
	}
};



// iterative
class Solution3 {
public:
	TreeNode* lca(TreeNode* root){
		TreeNode *head, *tail;
		unordered_map<TreeNode*, TreeNode*> parent;

		queue<TreeNode*> que;
		que.push(root);
		parent[root] = nullptr;

		while (!que.empty()){
			int sz = que.size();
			head = nullptr, tail = nullptr;

			for (int i = 0; i < sz; ++i){
				TreeNode* front = que.front();
				que.pop();

				if (head == nullptr)
					head = front;
				if (i == sz - 1)
					tail = front;

				if (front->left){
					que.push(front->left);
					parent[front->left] = front;
				}
				if (front->right){
					que.push(front->right);
					parent[front->right] = front;
				}
			}
		}

		while (head != tail){
			head = parent[head];
			tail = parent[tail];
		}

		return head;
	}
};


class Solution4 {
public:
	TreeNode* lca(TreeNode* root){
		int d = 0;
		return dfs(root, d);
	}

	TreeNode* dfs(TreeNode* n, int& d){
		if (!n)
			return n;
		if (!n->left && !n->right)
			return n;

		int ld = d + 1, rd = d + 1;
		TreeNode *l = dfs(n->left, ld), *r = dfs(n->right, rd);
		if (!l || !r){
			d = !l ? rd : ld;
			return !l ? r : l;
		}

		if (ld == rd){
			d = ld;
			return n;
		}
		else{
			d = ld > rd ? ld : rd;
			return ld > rd ? l : r;
		}
	}
};


class Solution5 {
public:
	TreeNode* lcaDeep(TreeNode* root){
		return dfs(root, 0).first;
	}

	pair<TreeNode*, int> dfs(TreeNode *root, int dep){
		if (!root)
			return{ nullptr, dep - 1 };

		auto l = dfs(root->left, dep + 1), r = dfs(root->right, dep + 1);
		if (l.second == r.second)
			return{ root, l.second };
		else
			return{ l.second > r.second ? l.first : r.first, max(l.second, r.second) };
	}
};


class Solution6 {
public:
	TreeNode* lca(TreeNode* root){
		int d = 0;
		return dfs(root, d);
	}

	TreeNode* dfs(TreeNode* n, int& d){
		if (!n){
			d = d - 1;
			return nullptr;
		}

		int ld = d + 1, rd = d + 1;
		TreeNode *l = dfs(n->left, ld), *r = dfs(n->right, rd);
		if (ld == rd){
			d = ld;
			return n;
		}
		else{
			d = max(ld, rd);
			return ld > rd ? l : r;
		}
	}
};


class Solution7 {
public:
	TreeNode* lca(TreeNode* root){
		auto res = dfs(root, 0);
		return res.second;
	}

	pair<int, TreeNode*> dfs(TreeNode* n, int depth){
		if (!n)
			return{ depth, nullptr };

		auto l = dfs(n->left, depth + 1),
			r = dfs(n->right, depth + 1);

		if (l.first == r.first)
			return{ l.first, n };
		else{
			TreeNode* deeper = l.first > r.first ? l.second : r.second;
			return{ max(l.first, r.first), deeper };
		}
	}
};

class Solution8{
public:
	TreeNode* lca(TreeNode* root){
		int i = 0;
		return dfs(root, i);
	}

	TreeNode* dfs(TreeNode* n, int& depth){
		if (!n)
			return nullptr;

		int ld = depth + 1, rd = depth + 1;
		TreeNode *l = dfs(n->left, ld), *r = dfs(n->right, rd);
		if (ld == rd){
			depth = ld;
			return n;
		}
		else{
			depth = max(ld, rd);
			return ld > rd ? l : r;
		}
	}
};

// iterative
class Solution9{
public:
	TreeNode* lca(TreeNode* root){
		queue<TreeNode*> q; 
		unordered_map<TreeNode*, TreeNode*> parent; 
		q.push(root); 

		while (!q.empty()){
			int sz = q.size(); 
			for (int i = 0; i < sz; ++i){
				TreeNode *front = q.front(); 
				q.pop(); 

				if (q->)
			}
		}
	}
};


int main(){
	Solution a;
	Solution8 a2;


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

	cout << a.lca(tree)->val << endl;

	Solution6 aa;
	cout << aa.lca(tree)->val << endl;;

	cout << a2.lca(tree)->val << endl;;



	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

