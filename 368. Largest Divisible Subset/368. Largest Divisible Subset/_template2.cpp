// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <functional>
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
// Discuss 
// Pick One 


// Given a set of distinct positive integers, find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies: Si % Sj = 0 or Sj % Si = 0. 
// If there are multiple solutions, return any subset is fine. 
// Example 1: 
// nums: [1,2,3]

// Result: [1,2] (of course, [1,3] will also be ok)

// Example 2: 
// nums: [1,2,4,8]

// Result: [1,2,4,8]



// passed. Complicated. 
class Solution {
public:
	vector<int> largestDivisibleSubset(vector<int>& nums) {
		if (nums.size() ==0)
			return {};

		sort(nums.begin(), nums.end(), less<int>());

		// b/c we need to find all the elems, so we have to track the whole path. It is like dfs
		// Use dp[i] to track the previous valid element, and in the end use while loop to resemble the whole path. 
		// pair: first - idx, second - prev
		vector<pair<int, int>> dp(nums.size(), { 0, -1 }); 

		// length as well as the last elem in the path are recorded. 
		int mxLen = 0, mxIdx=0; 

		for (int i = 1; i < nums.size(); ++i){
			for (int j = i-1; j >=0 ; --j){
				//  && curLen < dp[j]+1   is necessary!!
				if (nums[i] % nums[j] == 0 && dp[i].first < dp[j].first + 1){
					dp[i].first = dp[j].first + 1; 
					dp[i].second = j; 
					if (dp[i].first > mxLen){
						mxLen = dp[i].first; 
						mxIdx = i; 
					}
				}
			}
		}

		vector<int> res; 
		while (mxIdx != -1){
			res.push_back(nums[mxIdx]); 
			mxIdx = dp[mxIdx].second; 
		}
		return res; 
	}
};


class Solution2 {
public:
	vector<int> largestDivisibleSubset(vector<int>& nums) {
		if (nums.size() < 2)
			return nums; 

		int n = nums.size(); 
		sort(nums.begin(), nums.end()); 
		vector<vector<int>> dp(n, { 1, -1 }); 
		int len = -1, tail = -1; 
		for (int i = 1; i < n; ++i){
			for (int j = 0; j < i; ++j){
				if ((nums[i] % nums[j] == 0)&&(dp[j][0]+1>dp[i][0])){
					dp[i][0] = dp[j][0] + 1; 
					dp[i][1] = j; 
				}
			}
			if (len < dp[i][0]){
				len = dp[i][0]; 
				tail = i; 
			}
		}

		vector<int> res; 
		int i = tail; 
		while (i != -1){
			res.push_back(nums[i]); 
			i = dp[i][1]; 
		}
		reverse(res.begin(), res.end()); 

		return res; 
	}
};

int main(){
	Solution a;
	Solution2 a2;

	vector<int> b = { 1, 2, 4,3 };

	prt1Layer(a.largestDivisibleSubset(b)); 
	prt1Layer(a2.largestDivisibleSubset(b)); 



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

