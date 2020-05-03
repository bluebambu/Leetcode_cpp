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
	TreeNode(int a, TreeNode* x, TreeNode* y) :val(a), left(x), right(y) {
		if (x)
			x->parent = this;
		if (y)
			y->parent = this;
	}
	TreeNode() :val(0), left(nullptr), right(nullptr) {}

	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent; 

	void attachLeft(TreeNode* x){
		left = x; 
		x->parent = this; 
	}

	void attachRight(TreeNode* x){
		right = x; 
		x->parent = this; 
	}
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


// preorder
class Solution {
public:
	int leafSum(TreeNode* root){
		int res = 0; 

		TreeNode* cur = root; 

		while (cur){
			if (cur->left)
				cur = cur->left;
			else if (cur->right)
				cur = cur->right; 
			else{
				res += cur->val; 
				cout << cur->val << endl; 

				while (cur->parent && (cur->parent->right == cur || cur->parent->right == nullptr))
					cur = cur->parent; 

				if (cur->parent==nullptr)
					break;;

				cur = cur->parent->right; 
			}
		}

		return res; 
	}
};

// inorder
class inorder {
public:
	int leafSum(TreeNode* root){
		int res = 0;

		TreeNode* cur = root; 

		while (cur){
			if (cur->left)
				cur = cur->left;
			else{ // if left child not exist, print node directly
				res += cur->val;
				cout << cur->val << endl;

				if (cur->right){
					cur = cur->right;
				}
				else{ // if left child and right child both don't exist
					// backtracking
					while (cur->parent){ 
						if (cur == cur->parent->left){
							cout << cur->parent->val << endl; // left child to parent, print parent
							if (cur->parent->right) // if right sibling exist, break
								break;
							cur = cur->parent; // if right sibling doesn't exist, only back trace
						}
						else if (cur == cur->parent->right){
							cur = cur->parent; // right child to parent, not print parent
						}
					}

					if (cur->parent == nullptr)
						break;

					cur = cur->parent->right;
				}
			}
		}
		return res; 
	}
};

// postOrder
class postorder {
public:
	int leafSum(TreeNode* root){
		int res = 0; 
		TreeNode* cur = root; 

		while (cur){
			if (cur->left)
				cur = cur->left;
			else if (cur->right)
				cur = cur->right; 
			else{
				cout << cur->val << endl; // print leaf nodes

				while (cur->parent){ // backtracking
					if (cur == cur->parent->left){
						if (cur->parent->right)// if right sibling exist, break
							break;
						cout << cur->parent->val << endl; // if right sibling does not exist, print parent
						cur = cur->parent; 
					}
					else if (cur == cur->parent->right){
						cout << cur->parent->val << endl; // right child to parent, print parent
						cur = cur->parent; 
					}
				}

				if (cur->parent==nullptr)
					break;

				cur = cur->parent->right; 
			}
		}
		return res; 
	}
};

int main(){
	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree2 = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/
	TreeNode* tree = new TreeNode(6); 
	TreeNode* x = new TreeNode(3); 
	TreeNode* y = new TreeNode(1); 
	TreeNode* xx = new TreeNode(4); 
	TreeNode* yy = new TreeNode(2); 
	tree->attachLeft(x); 
	x->attachRight(y); 
	x->attachLeft(xx); 
	y->attachLeft(yy); 

	tree->parent = nullptr; 
	tree2->parent = nullptr; 

	Solution a; 

	cout << a.leafSum(tree) << endl; 

	cout << "INORDER:\n";
	inorder b; 
	b.leafSum(tree); 

	cout << "POSTORDER:\n";
	postorder c; 
	c.leafSum(tree); 

	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

