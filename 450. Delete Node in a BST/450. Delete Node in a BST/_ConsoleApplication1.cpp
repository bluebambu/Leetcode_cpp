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
    TreeNode* deleteNode(TreeNode* root, int key) {
		if (!root) return nullptr; 
		TreeNode *p = root; 
		del(p, key); 
		return root; 
    }
	void del(TreeNode *&p, int key){
		if (p->val > key)
			del(p->left, key);
		else if (p->val < key)
			del(p->right, key); 
		else{
			if (!p->right){
				TreeNode *tmp = p; 
				p = p->left; 
				delete tmp; 
			}
			else{
				TreeNode *r = p->right; 
				while (r->left)
					r = r->left; 
				swap(r->val, p->val); 
			}
		}
	}
};



class Solution2 {
public:
	TreeNode* deleteNode(TreeNode* root, int key) {
		return del(root, key); 
	}
	TreeNode* del(TreeNode *node, int key){
		if (!node)return nullptr; 
		if (node->val < key){
			node->right = del(node->right, key);
			return node; 
		}
		else if (node->val > key){
			node->left = del(node->left, key); 
			return node; 
		}
		else{
			if (node->right == nullptr){
				TreeNode *t = node->left; 
				delete node; 
				node = t; 
				return t; 
			}
			else{
				TreeNode *r = node->right; 
				while (r->left)
					r = r->left; 
				swap(r->val, node->val); 
				node->right = del(node->right, r->val); 
				return node; 
			}
		}
	}
}; 

class Solution3 {
public:
	TreeNode* deleteNode(TreeNode* root, int key) {
		del(root, key); 
		return root; 
	}
	void del(TreeNode *&n, int k){
		if (!n) return; 
		if (n->val < k)
			del(n->right, k);
		else if (n->val > k)
			del(n->left, k); 
		else{
			if (!n->right){
				auto t = n; 
				n = n->left; 
				delete t; 
			}
			else{
				auto p = n->right; 
				while (p->left) p = p->left; 
				n->val = p->val; 
				del(n->right, p->val); 
			}
		}
	}
};


class Solution4 {
public:
	TreeNode* deleteNode(TreeNode* root, int key) {
		if (!root) return nullptr; 
		if (root->val > key){
			root->left = deleteNode(root->left, key); 
		}
		else if (root->val < key){
			root->right = deleteNode(root->right, key); 
		}
		else{
			if (!root->left && !root->right){
				delete root; 
				return nullptr; 
			}
			else if (!root->right || !root->left){
				TreeNode *valid = root->right ? root->right : root->left; 
				delete root; 
				return valid; 
			}
			else{
				TreeNode *r = root->right; 
				while (r->left) r = r->left; 
				root->val = r->val; 
				root->right = deleteNode(root->right, root->val); 
			}
		}

		return root; 
	}
};


int main(){
	Solution3 a;

	vector<int> b = { 1, 2, 3, 4, 5 }; 



	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6,
		new TreeNode(3, new TreeNode(1),
						new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
						new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/

	tree = a.deleteNode(tree, 3); 

	print(tree); 


	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

