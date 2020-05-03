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


// A peak element is an element that is greater than its neighbors.
// 
// Given an input array where num[i] ≠ num[i + 1], find a peak element and return its index.
// 
// The array may contain multiple peaks, in that case return the index to any one of the peaks is fine.
// 
// You may imagine that num[-1] = num[n] = -∞.
// 
// For example, in array[1, 2, 3, 1], 3 is a peak element and your function should return the index number 2.
// 
// click to show spoilers.
// 
// Credits:
// Special thanks to @ts for adding this problem and creating all test cases.
// 
// 这道题是求数组的一个峰值，这个峰值可以是局部的最大值，这里用遍历整个数组找最大值肯定会出现
// Time Limit Exceeded，我们要考虑使用类似于二分查找法来缩短时间，由于只是需要找到任意一个峰
// 值，那么我们在确定二分查找折半后中间那个元素后，和紧跟的那个元素比较下大小，如果大于，则说
// 明峰值在前面，如果小于则在后面。这样就可以找到一个峰值了，代码如下：

// 这道题的要求是找出数组中的峰值元素，返回其下标。其中峰值元素是指该元素大于相邻元素（num[-1] = num[n] = -∞），
// 而且数组中相邻元素无重复。如果有多个峰值，返回任意一个即可。而且要求对O(logn)杂度。
// 
// 直接思路就是遍历一边数组，不过这样复杂度是O(n)。至于要达到O(logn)，就首先想到二分了。找到中间元素nums[m]，可以
// 与两边元素比较，如果nums[m]大于两边的，那nums[m]就直接是峰值了；否则，选取大于nums[m]的一侧接着二分即可。由于每
// 次会选出左侧或者右侧，因此无需与两侧元素都进行比较，只需要比较一侧即可（这里选择与nums[m]的右侧元素nums[m + 1]进行比较）。
// 
// 具体做法：取数组左右端点l和r，然后令中值m1等于(l + r) / 2，m2等于m1 + 1，这样比较nums[m1]和nums[m2]的大小：
// 
// 如果nums[m1]小于nums[m2]，那么说明nums[m1]肯定不可能是峰值，而m1的右侧一定存在峰值，因为如果nums[m2]大于nums[m2 + 1]，
// 那么m2处就是峰值，否则nums[m2 + 1]可能就是峰值（如果大于nums[m2 + 2]的话），以此类推，可以确定这部分一定存在峰值。因此
// 可以令l等于m2，接着进行二分搜索。
// 
// 如果nums[m1]大于nums[m2]，那么说明nums[m2]肯定不可能是峰值，而m2的左侧一定存在峰值，理由同上。因此可以令r等于m1，接着进行二分搜索。
// 
// 最后l等于r时结束，返回l即可。
// 
// 时间复杂度：O(logn)
// 
// 空间复杂度：O(1)

class Solution {
public:
	int findPeakElement(vector<int>& nums) {
		if (nums.empty())
			return 0; 

		int left = 0, right = nums.size() - 1; 
		while (left < right){
			int mid = left + (right - left) / 2;
			if (nums[mid] < nums[mid + 1])
				left = mid + 1;
			else
				right = mid; 
		}
		return left; 
	}
};



// directly find the global max
// 
class Solution2 {
public:
	int findPeakElement(vector<int>& nums) {
		if (nums.empty())
			return 0;

		int res = nums[0], ind = 0;
		for (int i = 1; i<nums.size(); ++i){
			if (nums[i]>res){
				res = nums[i];
				ind = i;
			}
		}
		return ind;
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

