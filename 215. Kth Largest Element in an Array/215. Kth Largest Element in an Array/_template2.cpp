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
class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		return helper(nums, 0, nums.size(), nums.size() - k); 
	}

	int helper(vector<int>& nums, int start, int end, int k){
		//if (start == end - 1)
		//	return nums[start]; 

		int i = start + 1; 
		for (; i < end; ++i){
			if (nums[i]<nums[start])
				continue;

			int j = i + 1; 
			while (j < end && nums[j] >= nums[start]) ++j; 
			if (j==end)
				break;
			swap(nums[i], nums[j]); 
		}
		swap(nums[start], nums[i - 1]); 
		if (i - 1 == k)
			return nums[i - 1];
		if (i == start + 1)
			return helper(nums, start + 1, end, k); 
		else if (i - 1>k)
			return helper(nums, start, i - 1, k);
		else
			return helper(nums, i - 1, end, k); 
	}
};


// pass
class Solution3 {
public:
	int findKthLargest(vector<int>& nums, int k) {
		int left = 0, right = nums.size() - 1;
		while (left < right){
			int cur = check(nums, left, right);

			//prt1Layer(nums); 
			//cout << cur << endl;

			if (cur == k - 1)
				return nums[cur];
			else if (cur < k - 1)
				left = cur + 1;
			else
				right = cur - 1;
		}
		return nums[left];
	}

	int check(vector<int>& nums, int l, int r){
		int x = l;
		int piv = nums[l];
		l += 1;
		while (l <= r){
			while (l <= r && nums[l] > piv) ++l;
			while (r >= l && nums[r] < piv) --r;
			if (l >= r)
				break;
			swap(nums[l], nums[r]);
			++l, --r;
		}
		swap(nums[x], nums[l - 1]);
		return l - 1;
	}
};


class Solution2 {
public:
	int findKthLargest(vector<int>& nums, int k) {
		int l = 0, r = nums.size(); 
		while (l < r){
			int rk = rank(nums, l, r); 
			if (rk == k - 1)
				return nums[rk];
			else if (rk > k - 1)
				r = rk;
			else
				l = rk + 1; 
		}
		return -1; 
	}

	int rank(vector<int>& nums, int left, int right){
		int target = nums[left], i = left + 1; 

		while (i < right){
			while (i < right && nums[i] >= target) ++i; 
			while (i < right && nums[right - 1] <= target) --right; 
			if (i == right)
				break; 

			swap(nums[i], nums[right - 1]); 
		}

		swap(nums[left], nums[i - 1]); 

		return i - 1; 
	}
}; 


int main(){
	Solution3 a; 
	Solution2 a2; 

	vector<int> b = { -1, 2, 0 }; 

	cout << a.findKthLargest(b, 1) << endl; 
	cout << a2.findKthLargest(b, 1) << endl; 

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

