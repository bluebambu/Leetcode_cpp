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
// ////////////////////////////////////////////////////////////////
// Find the sum of all left leaves in a given binary tree.
// Example:
//    3
//   / \
//   9  20
//  / \
// 15   7

// There are two left leaves in the binary tree, with values 9 and 15 respectively.Return 24.


/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/
// wrong!!! leaves are only at the lowest layer!!!
class Solution2 {
public:
	int sumOfLeftLeaves(TreeNode* root) {
		int res = 0; 
		traverse(root, res); 
		return res; 
	}

	void traverse(TreeNode* node, int& res){
		if (node == nullptr)
			return; 

		if (node->left){
			res += node->left->val; 
			traverse(node->left, res);
		}
		if (node->right){
			traverse(node->right, res); 
		}
	}
};


// pass AC
class Solution2 {
public:
	int sumOfLeftLeaves(TreeNode* root) {
		int res = 0; 
		traverse(root, false, res); 
		return res; 
	}

	void traverse(TreeNode* node, bool flag, int& res){
		if (node == nullptr)
			return; 
		if (!node->left && !node->right && flag){
			res += node->val; 
		}

		if (node->left){
			traverse(node->left, res);
		}
		if (node->right){
			traverse(node->right, res); 
		}
	}
};

// better clearer solution
class Solution2 {
public:
	int sumOfLeftLeaves(TreeNode* root) {
		if (!root) return 0;
		if (root->left && !root->left->left && !root->left->right) {
			return root->left->val + sumOfLeftLeaves(root->right);
		}
		return sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
	}
};


int main()
{
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

