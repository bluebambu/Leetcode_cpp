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

// 
// Given an unsorted array nums, reorder it such that nums[0] < nums[1] > nums[2] < nums[3]....
// 
// Example:
// (1) Given nums = [1, 5, 1, 1, 6, 4], one possible answer is[1, 4, 1, 5, 1, 6].
// (2) Given nums = [1, 3, 2, 2, 3, 1], one possible answer is[2, 3, 1, 3, 1, 2].
// 
// Note :
// 	 You may assume all input has valid answer.
// 
// 	 Follow Up :
// Can you do it in O(n) time and / or in - place with O(1) extra space ?
// 
// Credits :
// 		Special thanks to @dietpepsi for adding this problem and creating all test cases.


// 与wiggle sort I不同的是， 对于连续、相等的几个数的处理。 比如 111222， wiggle I 无法排序， wiggle II要求排成 121212
// 因此这里， wiggle I 的那种局部性质可传递性不存在了。 只能用排序或者其他高级方法做。 

class Solution {
public:
	void wiggleSort(vector<int>& nums) {
		vector<int> sorted(nums);
		sort(sorted.begin(), sorted.end());
		for (int i = nums.size() - 1, j = 0, k = i / 2 + 1; i >= 0; i--)
			nums[i] = sorted[i & 1 ? k++ : j++];
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

