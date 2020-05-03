// _template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <functional>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <set>
#include <unordered_set>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a < b ? a : b; }

struct TreeNode {
	TreeNode(int a) :val(a), left(nullptr), right(nullptr) { parent = nullptr;  }
	TreeNode(int a, TreeNode* x, TreeNode* y) :val(a), left(x), right(y) {
		if (x) left->parent = this; 
		if (y) right->parent = this; 
		parent = nullptr; 
	}
	TreeNode() :val(0), left(nullptr), right(nullptr) { parent = nullptr;  }

	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent; 
};


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
			cout << j << "\t";
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


vector<vector<int>> dirs{ { 0, -1 }, { 0, 1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 


void preorder(TreeNode* root){
	cout << endl; 

	TreeNode *p = root, *last = nullptr; 

	while (p){
		while (p->left){
			cout << p->val << " ";
			p = p->left;
		}

		cout << p->val << " ";

		if (p->right)
			p = p->right; 
		else{
			while (p->parent && p == p->parent->right)
				p = p->parent; 
			if (p->parent == nullptr)
				return; 
			p = p->parent->right; 
		}
	}
}


void inorder(TreeNode* root){
	cout << endl; 

	TreeNode *p = root; 

	while (p){
		while (p->left){
			p = p->left; 
		}

		cout << p->val << " "; 

		if (p->right){
			p = p->right; 
		}
		else{
			while (p->parent && p == p->parent->right){
				p = p->parent; 
			}
			while (p->parent && p == p->parent->left){
				cout << p->parent->val << " "; 
				if (p->parent->right)
					break;
				p = p->parent; 
			}
			if (p->parent == nullptr)
				return; 

			p = p->parent->right; 
		}
	}
}

void postorder(TreeNode* root){
	cout << endl; 
	TreeNode *p = root; 

	while (p){
		while (p->left){
			p = p->left; 
		}

		if (p->right)
			p = p->right; 
		else{
			while (true){
				cout << p->val << " "; 
				if (p->parent && p == p->parent->right)
					p = p->parent; 
				else
					break;
			}
			while (p->parent && p == p->parent->left){
				if (p->parent->right)
					break;
				cout << p->parent->val << " "; 
				p = p->parent; 
			}
			if (p->parent==nullptr)
				return;
			
			p = p->parent->right; 
		}
	}
}


int main() {
	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
														new TreeNode(4)),
									new TreeNode(8, new TreeNode(7),
														new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/
	TreeNode* tree2 = new TreeNode(6, new TreeNode(3, new TreeNode(1), nullptr), nullptr); 

	TreeNode* tree3 = new TreeNode(6, nullptr,
									new TreeNode(8, nullptr,
														new TreeNode(9)));
	/*      6
		       8
					9
	*/
	postorder(tree); 
	postorder(tree2); 
	postorder(tree3); 
	postorder(nullptr); 
}

