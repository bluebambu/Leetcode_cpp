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
// Given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by array nums.You are asked to burst all the balloons.If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins.Here left and right are adjacent indices of i.After the burst, the left and right then becomes adjacent.
// Find the maximum coins you can collect by bursting the balloons wisely.
// Note:
// (1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
// (2) 0 ¡Ü n ¡Ü 500, 0 ¡Ü nums[i] ¡Ü 100
// Example :
// 		Given[3, 1, 5, 8]
// 		Return 167
// 		nums = [3, 1, 5, 8] -->[3, 5, 8] -->[3, 8]   -->[8]  -->[]
// 		coins = 3 * 1 * 5 + 3 * 5 * 8 + 1 * 3 * 8 + 1 * 8 * 1 = 167



class Solution {
public:
	int maxCoins(vector<int>& nums) {
		vector<int> inums(nums.size() + 2, 0); 
		int n = 1; 
		for (auto x : nums)
			if (x > 0)
				inums[n++] = x; 
		inums[0] = inums[n++] = 1; 

		vector<vector<int>> memo(n, vector<int>(n, 0)); 
		return burst(memo, inums, 0, n - 1); 
	}

	int burst(vector<vector<int>>& memo, vector<int>& nums, int left, int right){
		if (left + 1 == right)
			return 0; 
		if (memo[left][right]>0)
			return memo[left][right]; 

		int ans = 0; 
		for (int i = left + 1; i < right; ++i){
			ans = max(ans,
				nums[left] * nums[i] * nums[right] +
				burst(memo, nums, left, i) +
				burst(memo, nums, i, right));
		}
		memo[left][right] = ans; 
		return ans; 
	}
};


class Solution2 {
public:
	int maxCoins(vector<int>& nums) {
		vector<int> aug(1, 1); 
		aug.insert(aug.end(), nums.begin(), nums.end()); 
		aug.push_back(1); 

		int n = nums.size(); 

		vector<vector<int>> cache(n + 2, vector<int>(n + 2, -1)); 
		return divcog(aug, 0, n + 1, cache); 
	}

	int divcog(vector<int>& arr, int l, int r, vector<vector<int>>& cache){
		if (l + 1 >= r)
			return 0; 

		if (cache[l][r] > 0)
			return cache[l][r]; 

		int m = INT_MIN; 
		for (int k = l + 1; k < r; ++k){
			m = max(m, divcog(arr, l, k, cache) + arr[l] * arr[k] * arr[r] + divcog(arr, k, r, cache)); 
		}

		cache[l][r] = m; 
		return m; 
	}
}; 


int main(){
	Solution2 a;

	vector<int> b = { 3, 1, 5, 8 };

	cout << a.maxCoins(b) << endl; 


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

