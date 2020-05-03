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


class Solution {
public:
	int threeSumSmaller(vector<int>& nums, int target) {
		if (nums.empty() || nums.size() < 3)
			return 0;
		sort(nums.begin(), nums.end());
		int res = 0;

		for (int i = 0; i < nums.size() - 2; ++i){
			for (int j = i + 1, k = nums.size() - 1; j < k;){
				int tot = nums[i] + nums[j] + nums[k];
				if (tot < target){
					res += k - j;	 // 和 3sum不同的是， 一旦 total < target， j  to k 所有数字都满足 total<target。 注意一点， j只能取值到k-1， 所以这里是k-j 而不是 k-j+1
					++j;
				}
				else if (tot >= target)
					--k;

			}
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




}

