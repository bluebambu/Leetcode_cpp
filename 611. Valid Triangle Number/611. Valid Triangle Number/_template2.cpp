// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <functional>
#include <bitset>
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
// Given an array consists of non-negative integers, your task is to count the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.

// Example 1:

// Input: [2,2,3,4]
// Output: 3
// Explanation:
// Valid combinations are: 
// 2,3,4 (using the first 2)
// 2,3,4 (using the second 2)
// 2,2,3

class Solution {
public:
	int triangleNumber(vector<int>& nums) {
		int res = 0; 
		sort(nums.begin(), nums.end());

		for (int i = nums.size() - 1; i >= 2; --i){
			int j = 0, k = i - 1; 
			while (j < k){
				int sum = nums[j] + nums[k]; 
				if (sum <= nums[i])
					++j;
				else{
					res += k - j; 
					--k; 
				}
			}
		}
		return res; 
	}
};


class Solution2 {
public:
	int triangleNumber(vector<int>& nums) {
		sort(nums.begin(), nums.end()); 
		int i = nums.size() - 1; 
		int res = 0; 
		
		for (; i >= 2; --i){
			int j = 0, k = i - 1, target = nums[i]; 

			while (j < k){
				int sum = nums[j] + nums[k]; 
				if (sum <= target)
					++j; 
				else{
					res += k - j; 
					--k; 
				}
			}
		}

		return res; 
	}
}; 


// wrong ans!!!!
class Solution3 {
public:
	int triangleNumber(vector<int>& nums) {
		sort(nums.begin(), nums.end()); 
		int res = 0; 
		for (int i = nums.size() - 1; i > 1; --i){
			int target = nums[i]; 
			int j = 0, k = i - 1; 
			while (j < k){
				int sum = nums[j] + nums[k]; 
				if (sum > target){
					--k; 
				}
				else{
					++j; 
				}
			}
		}
		return res; 
	}
};


class Solution4 {
public:
	int triangleNumber(vector<int>& nums) {
		sort(nums.begin(), nums.end()); 
		int res = 0; 
		for (int i = nums.size() - 1; i > 1; --i){
			int target = nums[i]; 
			int j = 0, k = i - 1; 
			while (j < k){
				int sum = nums[j] + nums[k]; 
				if (sum > target){
					res += k - j; 
					--k; 
				}
				else
					++j; 
			}
		}
		return res;
	}
};


// if you want to find pairs sum < target: 
class Solution5 {
public:
	int triangleNumber(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int res = 0;
		for (int i = nums.size() - 1; i > 1; --i){
			int target = nums[i]; 
			int j = 0, k = i - 1; 
			while (j<k) {
				int sum = nums[j] + nums[k]; 
				if (sum >= target)
					--k; 
				else{
					res += k - j; 
					++j; 
				}
			}
		}
		return res; 
	}
};


int main(){
	Solution a; 
	Solution4 a2; 

	vector<int> b = { 2, 2, 3, 4 }; 

	auto c = a.triangleNumber(b); 
	auto c2 = a2.triangleNumber(b); 
	
	cout << c << endl; 
	cout << c2 << endl; 


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

