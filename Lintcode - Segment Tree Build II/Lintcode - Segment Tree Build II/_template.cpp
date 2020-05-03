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

// Implement a build method with a given array, so that we can create a corresponding segment tree with every node value represent the corresponding interval max value 
// in the array, return the root of this segment tree.

// /**
// * Definition of SegmentTreeNode:
 class SegmentTreeNode {
 public:
     int start, end, max;
     SegmentTreeNode *left, *right;
     SegmentTreeNode(int start, int end, int max) {
         this->start = start;
         this->end = end;
         this->max = max;
         this->left = this->right = nullptr;
     }
 }

class Solution {
public:
	/**
	*@param A: a list of integer
	*@return: The root of Segment Tree
	*/
	SegmentTreeNode * build(vector<int>& A) {
		// write your code here
		return build(A, 0, A.size() - 1);
	}

	SegmentTreeNode* build(vector<int>& A, int start, int end){
		if (A.empty())
			return nullptr;
		if (start == end)
			return new SegmentTreeNode(start, end, A[start]);

		SegmentTreeNode* left = build(A, start, (end + start) / 2);
		SegmentTreeNode* right = build(A, (end + start) / 2 + 1, end);

		SegmentTreeNode* node = new SegmentTreeNode(start, end, max(left->max, right->max));
		node->left = left;
		node->right = right;
		return node;
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

