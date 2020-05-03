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


//* Definition of SegmentTreeNode:  [left, right]
 class SegmentTreeNode {
 public:
     int start, end;
     SegmentTreeNode *left, *right;
     SegmentTreeNode(int start, int end) {
         this->start = start, this->end = end;
         this->left = this->right = NULL;
     }
 }

class Solution {
public:
	/**
	*@param start, end: Denote an segment / interval
	*@return: The root of Segment Tree
	*/
	SegmentTreeNode * build(int start, int end) {
		// write your code here
		if (start > end) return nullptr;
		if (start == end) return new SegmentTreeNode(start, end);

		SegmentTreeNode* left = build(start, (start + end) / 2);
		SegmentTreeNode* right = build((start + end) / 2 + 1, end);
		SegmentTreeNode* root = new SegmentTreeNode(start, end);

		root->left = left; root->right = right;
		return root;
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

