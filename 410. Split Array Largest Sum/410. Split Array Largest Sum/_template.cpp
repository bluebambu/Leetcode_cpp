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
#include <time.h>
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

template <typename T>
void vprt(vector<T> v){
	for (auto i : v)
		cout << v << " ";
	cout << endl;
}

template <typename T>
void vvprt(vector<vector<T>> v){
	for (auto i : v){
		for (auto j : i){
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <typename C>
void setprt(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
// Given an array which consists of non - negative integers and an integer m, you can split the array into m non - empty continuous subarrays.Write an algorithm to minimize the largest sum among these m subarrays.
// Note:
// If n is the length of array, assume the following constraints are satisfied :
// 1 ≤ n ≤ 1000
// 1 ≤ m ≤ min(50, n)

// Examples :
// 	 Input :
// 		   nums = [7, 2, 5, 10, 8]
// 		   m = 2

// 	   Output :
// 			  18

// 		  Explanation :
// 					  There are four ways to split nums into two subarrays.
// 					  The best way is to split it into[7, 2, 5] and[10, 8],
// where the largest sum among the two subarrays is only 18.


// plain dfs, memorization
class Solution {
public:
	vector<int> cums;
	Solution() :cums(0) {}

	int splitArray(vector<int>& nums, int m) {

		cums = vector<int>(nums.size() + 1, 0);

		int c = 0;
		for (int i = 0; i < nums.size(); ++i){
			c += nums[i];
			cums[i + 1] = c;
		}

		int res = INT_MAX;
		dfs(nums, 0, 0, m, res);
		return res;
	}

	void dfs(vector<int>& nums, int i, int temp, int m, int& res){
		if (m < 0)
			return;

		if (i == nums.size()){
			res = min(res, temp);
			return;
		}

		for (int j = i; j < nums.size(); ++j){
			int subsum = f(nums, i, j);
			int maxSub = max(temp, subsum);
			dfs(nums, j + 1, maxSub, m - 1, res);
		}
	}

	int f(vector<int>& nums, int i, int j){
		return cums[j + 1] - cums[i];
	}
};


class Solution2 {
public:
	int splitArray(vector<int>& nums, int m) {
		vector<long long> cum(nums.size() + 1, 0); 
		init(cum, nums); 
		unordered_map<int, unordered_map<int, long long>> map; 

		return dfs(nums, 0, m, cum, map); 
	}

	long long dfs(vector<int>& nums, int idx, int segNo, 
		vector<long long>& cums, unordered_map<int, unordered_map<int, long long>>& map){
		if (map.count(idx) && map[idx].count(segNo))
			return map[idx][segNo]; 
		if (idx >= nums.size())
			return 0; 
		if (segNo < 1)
			return 0; 
		if (segNo == 1)
			return cums[cums.size() - 1] - cums[idx]; 

		long long res = cums.back(); 
		for (int j = idx; j < nums.size(); ++j){
			long long s = subsum(cums, idx, j); 
			long long cur_r = max(s, dfs(nums, j + 1, segNo - 1, cums, map)); 
			res = min(res, cur_r); 
		}
		map[idx][segNo] = res; 
		return (res); 
	}


	void init(vector<long long>& cum, vector<int>& nums){
		long long c = 0; 
		for (int i = 0; i < nums.size(); ++i){
			c += nums[i]; 
			cum[i + 1] = c; 
		}
	}

	long long subsum(vector<long long>& cums, int i, int j){
		return cums[j + 1] - cums[i]; 
	}
};

// wrong ans!!!!
class Solution3 {
public:
	long long splitArray(vector<int>& nums, int m) {
		long long left = 0, right = 0; 
		for (auto i : nums) right += i; 

		while (left + 1 < right){
			long long mid = left + (right - left) / 2; 
			if (isLarger(nums, mid, m))
				right = mid;
			else
				left = mid; 
		}
		return left; 
	}

	bool isLarger(vector<int>& nums, long long cand, int m){
		long long c = cand; 
		for (int i = 0; i < nums.size(); ++i){
			if (m == 0)
				return false; 

			if (c < nums[i]){
				m -= 1; 
				c = cand; 
				--i; 
				continue;
			}
			else
				c -= nums[i]; 
		}

		return c == 0 ? false : true;
	}
};

typedef vector<vector<int>> VVI; 
typedef vector<int> VI; 
 
class Solution4 {
public:
	long long splitArray(vector<int>& nums, int m) {
		int n = nums.size(); 
		VVI dp(n + 1, VI(m + 1, 0)); 
		VI cum(n + 1, 0); 
		for (int i = 0; i < nums.size(); ++i)
			cum[i + 1] = cum[i] + nums[i]; 
		
		for (int i = 1; i <= n; ++i)
			dp[i][1] = cum[i]; 
		// dp[i][j] = maxOf { k in [1, i]: max(dp[i-k][j-1], cum[i]-cum[i-k])}
		for (int j = 2; j <= m; ++j){
			for (int i = 1; i <= n; ++i){
				int cur = INT_MAX; 
				for (int k = 1; k <= i; ++k){
					int tmp = max(dp[i - k][j - 1], cum[i] - cum[i - k]); 
					cur = min(cur, tmp); 
				}
				dp[i][j] = cur; 
			}
		}

		for (auto i : dp){
			for (auto j : i)
				cout << j << ' '; 
			cout << endl; 
		}
		
		return dp[n][m]; 
	}
};

class Solution5 {
public:
	long long splitArray(vector<int>& nums, int m) {
		int n = nums.size(); 
		vector<int> cum(n+1, 0); 
		for (int i = 0; i < n; ++i)
			cum[i + 1] = cum[i] + nums[i]; 

		int left = 0, right = cum[n]; 
		while (left + 1 < right){
			int mid = left + (right - left) / 2; 
			if (small_to_fit(nums, mid, m))
				left = mid;
			else
				right = mid; 
		}
		return right; 
	}

	bool small_to_fit(VI& nums, int gap, int m){
		int orig = gap, cnt = 1;
		int i = 0;
		for (; i < nums.size() ; ++i){
			if (orig < nums[i])
				return true; 
			if (gap < nums[i]){
				++cnt; 
				gap = orig; 
				--i; 
			}
			else{
				gap -= nums[i]; 
			}
		}
		return cnt > m; 
	}
}; 

int main(){
	Solution2 a;
	Solution5 a2;

	vector<int> b = { 7, 2, 5, 10, 8 };
	vector<int> b2 = { 1, INT_MAX }; 

	cout << a.splitArray(b, 3) << endl;
	cout << a2.splitArray(b, 3) << endl;



	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;

	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/

}

