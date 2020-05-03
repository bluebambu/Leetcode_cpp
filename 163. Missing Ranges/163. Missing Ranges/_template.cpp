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


// 先把 lower， upper 整合到原数组中， 注意corner case	。 再用recursion 找range。 
// 但是有个问题..... 在整合lower upper的过程中， 应该也按 二分 来找位置...... 
// 不过即便如此， 在 array insert的时候， 还是 O(n), 没有意义..... 
//
//
// Attention!! 用recursion 做二分、两边都考虑， 复杂度实际上是 N .... 直接遍历也是  N ！！！！！ 	貌似没有意义.....
// 
// This does not work well, did not pass corner case like [], 1, 1

class Solution {
public:
	vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
		vector<string> res;
		if (nums.empty()){
			if (lower != upper)
				res.push_back(to_string(lower) + "->" + to_string(upper));
			else
				res.push_back(to_string(lower));
			return res;
		}
		else if (lower > nums.back() || upper < nums.front())
			return res;

		int left = min(nums[0], lower), right = max(nums.back(), upper);
		int ind = 0;

		for (int i = left; i <= right; ++i){
			if (ind == nums.size()){
				res.push_back(to_string(i) + "->" + to_string(right));
				break;
			}
			if (i == nums[ind]){
				++ind;
			}
			else if (i >= lower && i <= upper){
				string tmp;
				tmp += to_string(i);;
				if (i + 1 < nums[ind]){
					tmp += "->";
					tmp += to_string(nums[ind] - 1);
					i = nums[ind] - 1;
				}
				res.push_back(tmp);
			}
		}
		return res;
	}
};

//
class Solution2 {
public:
	vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
		vector<string> res; 
// 		if (nums.empty())			  这两句话在这里是错的， 参考 [ ] ， 0， 1    
// 			return res; 

		int left = lower; 
		for (int i = 0; i <= nums.size(); ++i){		// for 循环应该是index based， 而不是 integer value based， 否则复杂度太大了！！！ 这是一个指导思想
			int right = (i < nums.size() && nums[i]<=upper) ? nums[i] : upper + 1; 			// 这里 range 是 [left,  right), 相当于是  [lower, upper] 
			if (left == right)	++left; 
			else if (left < right){
				string tmp = left + 1 == right ? to_string(left) : to_string(left) + "->" + to_string(right - 1); 
				left = right + 1; 
			}
		}
		return res; 
	}
};

int main()
{
	Solution a;

	vector<int> b = { 0, 1, 3, 50, 75 };
	int lower = 0, upper = 99; 

	auto c = a.findMissingRanges(b, lower, upper); 

	for (auto i : c)
		cout << i << endl; 


}

