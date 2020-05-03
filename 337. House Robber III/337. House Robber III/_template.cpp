// _template.cpp : Defines the entry point for the console application.
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


// 											    3
// 										   4		 5
// 									    1	  3	   1	5
// 									2	  2	 1 3  6	9  1  2

//
//		 这道题最大的特点： 计算和的时候， 节点中间要隔一个。 因此递归的时候， 选了root， 就不能选 root->left, root->right. 所以是 root 和 root->left, right 的children 分为一组， root->left, root->right 分为另一组
//
//
//
//
// naive recurtion, TLE
class Solution
{
public:
	int rob(TreeNode* root) {
		if (!root)
			return 0; 
		int val = 0; 
		if (root->left)
			val += rob(root->left->left) + rob(root->left->right); 
		if (root->right)
			val += rob(root->right->left) + rob(root->right->left); 

		return max(val + root->val, rob(root->left) + rob(root->right));
	}
};

// improvement, memorization, pass
class Solution2 {
public:
	int rob(TreeNode* root){
		unordered_map<TreeNode*, int> mem; 
		return rob(root, mem); 
	}
	int rob(TreeNode* root, unordered_map<TreeNode*, int>& mem){
		if (!root)
			return 0;
		if (mem.find(root) != mem.end())
			return mem[root]; 

		int val = 0; 
		if (root->left)
			val += rob(root->left->left, mem) + rob(root->left->right, mem); 
		if (root->right)
			val += rob(root->right->left, mem) + rob(root->right->right, mem); 

		int res = max(val + root->val, rob(root->left, mem) + rob(root->right, mem)); 
		mem[root] = res; 
		return res; 
	}
};


// pass
class Solution3 {
public:
	int rob(TreeNode* root){
		int cur, lower; 
		post(root, cur, lower); 
		return cur;
	}

	void post(TreeNode* node, int& cur, int& lower){
		if (!node){
			cur = lower = 0; 
			return; 
		}

		int lc, rc, llow, rlow; 
		post(node->left, lc, llow); 
		post(node->right, rc, rlow); 
		cur = max(node->val + llow + rlow, lc + rc); 
		lower = lc + rc; 
	}
};


// pass
typedef pair<int, int> PII;
class Solution4 {
public:
	int rob(TreeNode* root){
		PII p = post(root); 
		return p.first; 
	}

	PII post(TreeNode* node){
		if (!node)
			return{ 0, 0 }; 

		auto left = post(node->left); 
		auto right = post(node->right); 
		int cur = max(left.first + right.first, left.second + right.second + node->val); 
		int prev = left.first + right.first; 
		return{ cur, prev }; 
	}
}; 


class Solution5 {
public:
	int rob(TreeNode* root){
		return dp(root); 
	}
	int dp(TreeNode *node){
		if (!node)
			return 0; 

		int take_cur_node = node->val; 
		if (node->left)
			take_cur_node += dp(node->left->left) + dp(node->left->right); 
		if (node->right)
			take_cur_node += dp(node->right->left) + dp(node->right->right); 

		return max(take_cur_node, dp(node->left) + dp(node->right)); 
	}
}; 



int main()
{
	Solution4 a;
	Solution5 a2; 

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9

	*/


	cout << a.rob(tree) << endl; 
	cout << a2.rob(tree) << endl; 

}

