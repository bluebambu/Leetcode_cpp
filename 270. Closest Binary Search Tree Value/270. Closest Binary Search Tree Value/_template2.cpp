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
	int closest(TreeNode* root, double target){
		return closest(root, target, nullptr)->val;
	}

	TreeNode* closest(TreeNode* node, double target, TreeNode* prev){
		if (prev == nullptr)
			prev = node; 

		TreeNode* res = fabs(prev->val - target) > fabs(node->val - target) ? node : prev; 

		if (node->left && target < node->val)
			return closest(node->left, target, prev);
		else if (node->right && target>node->val)
			return closest(node->right, target, prev); 
		return res; 
	}


	int closestValue(TreeNode* root, double target){
		TreeNode *prev = root, *cur = root; 
		while (cur){
			if (fabs(cur->val - target) < fabs(prev->val - target))
				prev = cur; 

			if (cur->left && cur->val > target)
				cur = cur->left;
			else if (cur->right&&cur->right->val < target)
				cur = cur->right;
			else
				return cur->val; 
		}

		return prev->val;; 
	}
};


class Solution2 {
public:
	int closest(TreeNode* root, double target){
		if (!root)
			return 0; 

		return dfs(root, target, double(root->val)); 
	}

	int dfs(TreeNode* n, double target, double closest){
		if (!n)
			return closest; 

		if (n->val > target)
			return dfs(n->left, target, 
			fabs(n->val - target) < fabs(closest-target) ? n->val : closest); 

		else if (n->val < target)
			return dfs(n->right, target,
			fabs(n->val - target) < fabs(closest - target) ? n->val : closest);
		else
			return n->val; 
	}
}; 



int main(){
	Solution a; 
	Solution2 a2; 

	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/

	cout << a.closest(tree,  0.99) << endl; 
	cout << a2.closest(tree, 0.99) << endl; 


	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

