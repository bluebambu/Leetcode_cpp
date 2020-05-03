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
#include <string> 
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>

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


/**
* Definition of SegmentTreeNode:			  */
class SegmentTreeNode {
public:
	int start, end, max;
	SegmentTreeNode *left, *right;
	SegmentTreeNode(int start, int end, int max) {
		this->start = start;
		this->end = end;
		this->max = max;
		this->left = this->right = NULL;
	}
}


class Solution {
public:
	/**
	*@param root, index, value: The root of segment tree and
	*@ change the node's value with [index, index] to the new given value
	*@return: void
	*/
	void modify(SegmentTreeNode *root, int index, int value) {
		// write your code here
		if (!root || index < root->start || index > root->end) return; 

		if (root->start == index && root->end == index){
			root->max = value;
			return;
		}

		int mid = root->start + (root->end - root->start) / 2; 
		if (index <= mid)	   // 其实这里不需要分情况， 因为上面的判断已经分了情况。  可以直接写 modif（left，), modify(right,)
			modify(root->left, index, value);
		else
			modify(root->right, index, value); 

		root->max = max(root->left->max, root->right->max); 
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

