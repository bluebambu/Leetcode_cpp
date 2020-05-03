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
	TreeNode(int a, TreeNode* x, TreeNode* y) :val(a), left(x), right(y) {
		parent = nullptr; 
		if (left)
			left->parent = this;
		if (right)
			right->parent = this;
	}
	TreeNode() :val(0), left(nullptr), right(nullptr), parent(nullptr) {}

	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent; 

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
	void preOrder(TreeNode* root){
		TreeNode *cur = root;
		
		while (true){
			cout << cur->val << " "; 

			if (cur->left) cur = cur->left; 
			else if (cur->right) cur = cur->right; 
			else{
				while (cur->parent && (cur->parent->right == nullptr || cur->parent->right == cur))
					cur = cur->parent; 
				if (cur->parent==nullptr)
					break;
				cur = cur->parent->right; 
			}
		}
	}

	TreeNode* inorder_first(TreeNode* root){
		while (root->left)
			root = root->left; 
		return root; 
	}

	void inOrder(TreeNode *root){
		TreeNode *cur = inorder_first(root); 

		while (cur){
			cout << cur->val << " "; 

			if (cur->right)
				cur = inorder_first(cur->right); 
			else{
				while (cur->parent && cur==cur->parent->right){
					cur = cur->parent;
				}

				// this place is a bit tricky!!!
				if (cur->parent == nullptr)
					return; 
				// else if ( cur->parent && cur==cur->parent->left ) 
				cur = cur->parent; 
			}
		}
	}


////////////////////////////////////////////////////
	void postOrder(TreeNode* root){
		TreeNode*cur = root; 
		cur = postOrder_first(cur);

		while (cur){
			cout << cur->val << " "; 
			cur = postSuccessor(cur); 
		}
	}

	TreeNode* postSuccessor(TreeNode* node){
		if (!node->parent)
			return nullptr; 
		else{
			if (node == node->parent->left && node->parent->right)
				node = postOrder_first(node->parent->right);
			else
				node = node->parent; 
		}
		return node; 
	}

	TreeNode* postOrder_first(TreeNode *node){
		if (!node)
			return nullptr; 

		while (true){
			if (node->left)
				node = node->left;
			else if (node->right)
				node = node->right;
			else
				return node; 
		}

		return node; 
	}
};








int main(){
	Solution a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/

	a.inOrder(tree); 


	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

