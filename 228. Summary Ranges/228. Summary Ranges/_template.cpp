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


// passed
// 这里 for loop  i[0, Size)  配上
// 
// j = i + 1;
// while (j < nums.size() && nums[j] == nums[j - 1] + 1) ++j;
// 
// if (j - 1 == i)
//		...... 
// 
// 能够完美包括 OUT of range 的情况， 应该熟记

class Solution
{
public:
	vector<string> summaryRanges(vector<int>& nums) {
		vector<string> res; 
		if (nums.empty())
			return res; 

		for (int i = 0; i < nums.size(); ++i){
			int j = i+1; 
			while (j < nums.size() && nums[j] == nums[j - 1] + 1) ++j; 
			
			if (j - 1 == i)
				res.push_back(to_string(nums[i]));
			else
				res.push_back(to_string(nums[i]) + "->" + to_string(nums[j - 1])); 
			
			i = j - 1; 
		}
		return res; 
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

