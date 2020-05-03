// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <functional>
#include <numeric>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a < b ? a : b; }


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
		for (int i = 0; i < n; ++i){
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


template <typename C>
void prt1Layer(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void prt2Layer(C v){
	for (auto i : v){
		for (auto j : i)
			cout << j << " ";
		cout << endl; 
	}
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
// Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.

// Note:

//     Each of the array element will not exceed 100.
//     The array size will not exceed 200.

// Example 1:
// Input: [1, 5, 11, 5]
// Output: true
// Explanation: The array can be partitioned as [1, 5, 5] and [11].

// Example 2:
// Input: [1, 2, 3, 5]
// Output: false
// Explanation: The array cannot be partitioned into equal sum subsets.


// passed
class Solution {
public:
	bool canPartition(vector<int>& nums) {
		int total = accumulate(nums.begin(), nums.end(), 0); 
		if (total % 2)
			return false; 

		int half = total / 2; 
		vector<bool> dp(half + 1, false);
		dp[0] = true; 

		for (int i = 0; i < nums.size(); ++i){
			for (int j = half; j >= nums[i]; --j){
				dp[j] = dp[j] || dp[j - nums[i]]; 
			}
		}

		return dp[half]; 
	}
};


// 这道题还可以用bitset来做，感觉也十分的巧妙，bisets的大小设为5001，
// 为啥呢，因为题目中说了数组的长度和每个数字的大小都不会超过100，那么
// 最大的和为10000，那么一半就是5000，前面再加上个0，就是5001了。我们
// 初始化把最低位赋值为1，然后我们算出数组之和，然后我们遍历数字，对于
// 遍历到的数字num，我们把bits向左平移num位，然后再或上原来的bits，这
// 样所有的可能出现的和位置上都为1。举个例子来说吧，比如对于数组[2,3]来
// 说，初始化bits为1，然后对于数字2，bits变为101，我们可以看出来bits[2]
// 标记为了1，然后遍历到3，bits变为了101101，我们看到bits[5],bits[3],
// bits[2]都分别为1了，正好代表了可能的和2，3，5，这样我们遍历玩整个数组
// 后，去看bits[sum >> 1]是否为1即可，参见代码如下：

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        bitset<5001> bits(1);
        int sum = accumulate(nums.begin(), nums.end(), 0);
        for (int num : nums) bits |= bits << num;
        return (sum % 2 == 0) && bits[sum >> 1];
    }
};






int main(){
	Solution a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/



	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

