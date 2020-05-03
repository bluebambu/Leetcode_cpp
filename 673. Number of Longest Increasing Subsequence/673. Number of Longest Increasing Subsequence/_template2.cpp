// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
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
// Given an unsorted array of integers, find the number of longest increasing subsequence. 
// Example 1:
// Input: [1,3,5,4,7]
// Output: 2
// Explanation: The two longest increasing subsequence are [1, 3, 4, 7] and [1, 3, 5, 7].

// Example 2:
// Input: [2,2,2,2,2]
// Output: 5
// Explanation: The length of longest continuous increasing subsequence is 1, and there are 5 subsequences' length is 1, so output 5.

// Note: Length of the given array will be not exceed 2000 and the answer is guaranteed to be fit in 32-bit signed int. 


// tricky!! subsequence 本身是 dp， 实际上 subsequence count 也是dp！！！！
//
// pass AC, many details!!
class Solution {
public:
	int findNumberOfLIS(vector<int>& nums) {
		if (nums.empty())
			return 0; 
		if (nums.size()==1)
			return 1; 

		vector<int> dp(nums.size(), 1); 
		vector<int> cnt(nums.size(), 1); 
		// if cnt[] are init with 1, then when cnt[i]+=cnt[j], cnt[i] needs to be 0
		// if cnt[] are init with 0, then when nums[i] is the only elem in the sequence, 
		// cnt[i] needs to be 1. 
		// check example [2,2,2,2,2]

		int maxLen = 0; 

		for (int i = 1; i < nums.size(); ++i){
			for (int j = i - 1; j >= 0; --j){
				if (nums[j] < nums[i]) {
					dp[i] = max(dp[i], dp[j] + 1);
					cnt[i] = 0; // when cnt[i] is derived from before, set to 0
				}
			}
			for (int j = i - 1; j >= 0; --j){
				// here nums[j]<nums[i] is necessary!!!!!
				// because there might be different subsequnces having same Length. 
				if (dp[j] == dp[i] - 1 && nums[j]<nums[i])
					cnt[i] += cnt[j];
			}

			maxLen = max(maxLen, dp[i]); 
		}

		int res = 0; 
		for (int i = 0; i < cnt.size(); ++i){
			if (dp[i] == maxLen)
				res += cnt[i]; 
		}
		return res; 
	}
};


// best solution
class Solution2 {
public:
	int findNumberOfLIS(vector<int>& nums) {
		int n = nums.size(), maxlen = 1, ans = 0;
		vector<int> cnt(n, 1), len(n, 1);
		// init cnt[] with 1
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < i; j++) {
				if (nums[i] > nums[j]) {
					if (len[j] + 1 > len[i]) {
						len[i] = len[j] + 1;
						cnt[i] = cnt[j];
					}
					else if (len[j] + 1 == len[i])
						cnt[i] += cnt[j];
				}
				// else if (nums[i] == OR < nums[j]){
				//		cnt[i] = 1; // keep the original value
				// }
				// implicit statements are above 
			}
			maxlen = max(maxlen, len[i]);
		}
		// find the longest increasing subsequence of the whole sequence
		// sum valid counts
		for (int i = 0; i < n; i++)
			if (len[i] == maxlen) ans += cnt[i];
		return ans;
	}
};


// wrong ans!!
class Solution3 {
public:
	int findNumberOfLIS(vector<int>& nums) {
		vector<int> res; 
		for (int i = 0; i < nums.size(); ++i){
			if (res.empty())
				res.push_back(nums[i]); 
			else{
				int pos = bs(res, nums[i]); 
				if (pos == res.size())
					res.push_back(nums[i]);
				else if (nums[i] < res[pos])
					res[pos] = nums[i]; 
			}
		}
		return res.size(); 
	}

	int bs(vector<int>& arr, int piv){
		int left = 0, right = arr.size(); 
		while (left < right - 1){
			int mid = left + (right - left) / 2;
			if (arr[mid] <= piv)
				left = mid;
			else
				right = mid; 
		}
		return right; 
	}
};

class Solution4 {
public:
	int findNumberOfLIS(vector<int>& nums) {
		int n = nums.size(); 
		vector<int> dp(n, 1), cnt(n, 1); 
		int maxlen = INT_MIN; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < i; ++j){
				if (nums[i] > nums[j] && dp[j]+1 > dp[i]){
					dp[i] = dp[j] + 1; 
					cnt[i] = cnt[j]; 
				}
				else if (dp[j] + 1 == dp[i]){
					cnt[i] += cnt[j]; 
				}
			}
			maxlen = max(maxlen, dp[i]); 
		}

		int res = 0; 
		for (int i = 0; i < n; ++i){
			if (dp[i] == maxlen)
				res += cnt[i]; 
		}
		return res; 
	}
};

class Solution5{
public:
	int findNumberOfLIS(vector<int>& nums){
		int n = nums.size(); 
		vector<int> len(n, 1), num(n, 1); 
		len[0] = 1, num[0] = 1; 
		int longest = 1, res = 1; 
		for (int i = 1; i < n; ++i){
			for (int j = 0; j < i; ++j){
				if (nums[i] > nums[j]){
					if (len[i] < len[j] + 1){
						len[i] = len[j] + 1; 
						num[i] = num[j]; 
					}
					else if (len[i] == len[j] + 1){
						num[i] += num[j]; 
					}

				}

			}
			if (longest < len[i]){
				longest = len[i];
				res = num[i];
			}
			else if (longest == len[i]){
				res += num[i];
			}
		}
		return res; 
	}
};

int main(){

	Solution4 a;
	Solution5 a2;

	vector<int> b = { 1, 3, 5, 4, 7 }; 
	vector<int> b2 = { 2, 2, 2, 2, 2 }; 

	cout << a.findNumberOfLIS(b) << endl; 
	cout << a2.findNumberOfLIS(b) << endl; 


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

