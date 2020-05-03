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
// Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.
// Example 1:
// Input :
// 	5
// 	/ \
// 	3   6
// 	/ \   \
// 	2   4   7

// 	Target = 9

// Output: True

// 		Example 2 :
// 	Input :
// 		  5
// 		  / \
// 		  3   6
// 		  / \   \
// 		  2   4   7

// 		  Target = 28

// 	  Output: False


/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/

// pass AC, recursion method. 
class Solution {
public:
	bool findTarget(TreeNode* root, int k) {
		return dfs(root, root, k);
	}

	bool dfs(TreeNode* cur, TreeNode* root, int k){
		if (cur == nullptr)
			return false; 
		return search(root, cur, k - cur->val) || dfs(cur->left, root, k) || dfs(cur->right, root, k); 
	}

	// 注意查重
	bool search(TreeNode* cur, TreeNode* pre, int v){
		if (cur == nullptr)
			return false; 
		if (cur->val == v && cur != pre)
			return true; 
		return search(cur->left, pre, v) || search(cur->right, pre, v);

	}
};


// if use stack method, remember only need to store lgN # of nodes into it. 
// pass AC
class Solution {
public:
	bool findTarget(TreeNode* root, int k) {
		vector<TreeNode*> preStk, postStk; 

		for (TreeNode* p = root; p; p = p->left){
			preStk.push_back(p);
		}
		for (TreeNode* p = root; p; p = p->right){
			postStk.push_back(p);
		}

		while (preStk.size() && postStk.size() && preStk.back() != postStk.back()){
			TreeNode *pretop = preStk.back(), *postop = postStk.back(); 
			int tmp = pretop->val + postop->val; 
			if (tmp == k)
				return true; 
			else if (tmp < k){
				preStk.pop_back(); 
				if (pretop->right){
					TreeNode* nn = pretop->right; 
					while (nn){
						preStk.push_back(nn); 
						nn = nn->left; 
					}
				}
			}
			else{
				postStk.pop_back(); 
				if (postop->left){
					TreeNode* ll = postop->left; 
					while (ll){
						postStk.push_back(ll); 
						ll = ll->right; 
					}
				}
			}
		}

		return false; 
	}
};


class Solution2 {
public:
    bool findTarget(TreeNode* root, int k) {
		unordered_map<int, unordered_set<TreeNode*>> val_node; 
		return dfs(root, k, val_node); 
    }
	bool dfs(TreeNode *n, int k, unordered_map<int, unordered_set<TreeNode*>>& val_node){
		if (!n) return false; 
		if (val_node.count(k - n->val))
			return true; 
		val_node[n->val].insert(n); 
		return dfs(n->left, k, val_node) || dfs(n->right, k, val_node); 
	}
};

class Solution3 {
public:
	bool findTarget(TreeNode* root, int k) {
		
	}
};



int main() {
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


}

