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

// Design a hit counter which counts the number of hits received in the past 5 minutes.

// Each function accepts a timestamp parameter(in seconds granularity) and you may assume that calls are being made to the system in chronological order(ie, the timestamp is monotonically increasing).You may assume that the earliest timestamp starts at 1.

// It is possible that several hits arrive roughly at the same time.

// Example:
// HitCounter counter = new HitCounter();

// // hit at timestamp 1.
// counter.hit(1);

// // hit at timestamp 2.
// counter.hit(2);

// // hit at timestamp 3.
// counter.hit(3);

// // get hits at timestamp 4, should return 3.
// counter.getHits(4);

// // hit at timestamp 300.
// counter.hit(300);

// // get hits at timestamp 300, should return 4.
// counter.getHits(300);

// // get hits at timestamp 301, should return 3.
// counter.getHits(301);
// Follow up :
// What if the number of hits per second could be very large ? Does your design scale ?

class Solution
{
public:
	void flatten(TreeNode* root) {

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

