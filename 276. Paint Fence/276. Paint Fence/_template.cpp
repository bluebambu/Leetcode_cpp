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


class Solution {
public:
	int numWays(int n, int k) {
		if (n == 0) return 0;
		int same = 0, diff = k;
		for (int i = 2; i <= n; ++i){
			int olddiff = diff;
			diff = (olddiff + same) * (k - 1);
			same = olddiff;
		}
		return same + diff;
	}
};


class Solution {
public:
	int numWays(int n, int k) {
		vector<int> same(n, 0), dif(n, 0); 
		same[0] = 0, dif[0] = k; 
		for (int i = 1; i < n; ++i){
			dif[i] = (k - 1)*(dif[i - 1] + same[i - 1]); 
			same[i] = diff[i - 1]; 
		}

		return same.back() + dif.back(); 
	}

};

// pass
class Solution4 {
public:
	int numWays(int n, int k) {
		if (n == 0) return 0;
		int same = 0, diff = k;
		for (int i = 2; i <= n; ++i){
			int old_same = same;
			same = diff;
			diff = (old_same + diff) * (k - 1);
		}
		return same + diff;
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

