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
	void preorder(TreeNode* root){
		cout << endl; 
		TreeNode *p = root; 
		while (p){
			if (p->left == nullptr){
				cout << p->val << " "; 
				p = p->right; 
			}
			else{
				TreeNode *n = p->left; 
				while (n->right && n->right != p)
					n = n->right; 

				if (n->right == nullptr){
					n->right = p; 
					cout << p->val << " "; 
					p = p->left; 
				}
				else{
					n->right = nullptr; 
					p = p->right; 
				}
			}
		}
	}

	void inorder(TreeNode* root){
		cout << endl; 
		TreeNode* p = root; 

		while (p){
			if (p->left == nullptr){
				cout << p->val << " "; 
				p = p->right; 
			}
			else{
				TreeNode *n = p->left; 
				while (n->right && n->right != p)
					n = n->right; 

				if (n->right == nullptr){
					n->right = p; 
					p = p->left; 
				}
				else{
					n->right = nullptr; 
					cout << p->val << " "; 
					p = p->right; 
				}
			}
		}
	}
};


class Solution2 {
public:
	void preorder(TreeNode* root){
		cout << endl; 
		TreeNode *p = root; 

		while (p){
			if (p->left == nullptr){
				cout << p->val << " "; 
				p = p->right; 
			}
			else{
				TreeNode *n = p->left; 
				while (n->right && n->right != p)
					n = n->right; 

				if (n->right == nullptr){
					n->right = p; 
					cout << p->val << " "; 
					p = p->left; 
				}
				else{
					n->right = nullptr; 
					p = p->right; 
				}
			}
		}
	}

	void inorder(TreeNode* root){
		cout << endl; 
		TreeNode *p = root; 

		while (p){
			if (p->left == nullptr){
				cout << p->val << " "; 
				p = p->right; 
			}
			else{
				TreeNode *n = p->left; 
				while (n->right && n->right != p)
					n = n->right; 
				
				if (n->right == nullptr){
					n->right = p; 
					p = p->left; 
				}
				else{
					n->right = nullptr; 
					cout << p->val << " "; 
					p = p->right; 
				}
			}
		}
	}
}; 

int main(){
	Solution2 a;

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
	a.preorder(tree); 
	a.preorder(tree2); 
	a.preorder(tree3); 
	a.preorder(nullptr); 

	a.inorder(tree); 
	a.inorder(tree2); 
	a.inorder(tree3); 
	a.inorder(nullptr); 
}

