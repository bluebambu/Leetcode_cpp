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
// Given an integer array with all positive numbers and no duplicates, find the number of possible combinations that add up to a positive integer target.
// Example:
// nums = [1, 2, 3]
// target = 4

// The possible combination ways are :
// (1, 1, 1, 1)
// (1, 1, 2)
// (1, 2, 1)
// (1, 3)
// (2, 1, 1)
// (2, 2)
// (3, 1)

// Note that different sequences are counted as different combinations.

// Therefore the output is 7.

// Follow up :
// What if negative numbers are allowed in the given array ?
// How does it change the problem ?
// What limitation we need to add to the question to allow negative numbers ?


// TLE error. 
class Solution {
public:
	int combinationSum4(vector<int>& nums, int target) {
		sort(nums.begin(), nums.end());

		int res = 0; 
		vector<int> vtmp; 

		help(nums, 0, target, 0, vtmp, res); 
		return res; 
	}

	void help(vector<int>& nums, int idx, int target, int tmp, vector<int>& vtmp, int& res){
		if (tmp == target){
			res += 1; 
			setprt(vtmp); 
			return; 
		}
		if (tmp > target)
			return;

		for (int i = idx; i < nums.size(); ++i){
			vtmp.push_back(nums[i]); 
			help(nums, i, target, tmp + nums[i], vtmp, res); 
			vtmp.pop_back(); 
		}
	}
};


class Solution {
public:
	int combinationSum4(vector<int>& nums, int target) {
		vector<int> dp(target + 1); 
		dp[0] = 1;

		for (int i = 1; i <= target; ++i){
			for (int j : nums){
				if (j <= i)
					dp[i] += dp[i - j]; 
			}
		}
		return dp.back(); 
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

	vector<int> nums = { 1, 2, 3 }; 

	cout << a.combinationSum4(nums, 32)<<endl; 


}

