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
// Given an unsorted array nums, reorder it in - place such that nums[0] <= nums[1] >= nums[2] <= nums[3]....
// 
// For example, given nums = [3, 5, 2, 1, 6, 4], one possible answer is[1, 6, 2, 5, 3, 4].


// 4 - lines O(n) C++
// 
// The final sorted nums needs to satisfy two conditions :
// 
// If i is odd, then nums[i] >= nums[i - 1];
// If i is even, then nums[i] <= nums[i - 1].
// 
// The code is just to fix the orderings of nums that do not satisfy 1 and 2.

// nums[0], nums[1], nums[2]. 如果nums【1】比【0】高， 2比1还高， 2与1交换不会影响 【0】【1】之间的大小关系。 因为这个特性， 可以达到 O(n)水平

class Solution {
public:
	void wiggleSort(vector<int>& nums) {
		for (int i = 1; i < nums.size(); ++i){
			if (i % 2 == 0 && nums[i]>nums[i - 1] || i % 2 == 1 && nums[i] < nums[i - 1])
				swap(nums[i], nums[i - 1]);
		}
	}
};


class Solution2_naive{
public:
	void wiggleSort(vector<int>& nums) {
		sort(nums.begin(), nums.end()); 
		for (int i = 2; i < nums.size(); i+=2){
			swap(nums[i], nums[i - 1]); 
		}
	}

};

int main() {
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

