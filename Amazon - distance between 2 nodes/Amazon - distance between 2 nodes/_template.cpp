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




// 关于两个节点的最低公共祖先(LCA)问题，可以参考：寻找二叉树两个节点的最低公共祖先
// 
// 通过观察可以总结出下面的公式, lca是两个节点的最低公共祖先节点:
// 
// Dist(n1, n2) = Dist(root, n1) + Dist(root, n2) - 2 * Dist(root, lca)
class Solution
{
public:
	void distance(TreeNode* root, int a, int b) {

	}

	int dist(TreeNode* root, int a, int b){
		if (!root)
			return -1; 
		if (root->val == a || root->val == b)
			return 1; 

		int left = dist(root->left, a, b); 
		int right = dist(root->right, a, b); 

		if (left == -1 && right == -1)
			return -1;
		else if (left > 0 && right > 0)
			return left + right; 
		else{

		}
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

	a.flatten(tree);


}

