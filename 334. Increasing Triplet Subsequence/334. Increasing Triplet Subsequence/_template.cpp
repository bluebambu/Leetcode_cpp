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
// Given an unsorted array return whether an increasing subsequence of length 3 exists or not in the array.
// Formally the function should :
// Return true if there exists i, j, k
// such that arr[i] < arr[j] < arr[k] given 0 ≤ i < j < k ≤ n - 1 else return false.

// Your algorithm should run in O(n) time complexity and O(1) space complexity.
// Examples :
// 		 Given[1, 2, 3, 4, 5],
// 		 return true.
// 		 Given[5, 4, 3, 2, 1],
// 		 return false.


class Solution {
public:
	bool increasingTriplet(vector<int>& nums) {
		int m1 = INT_MAX, m2 = INT_MAX;
		for (auto a : nums){
			if (a <= m1)
				m1 = a;
			else if (a <= m2)
				m2 = a;
			else
				return true;
		}
		return false; 
	}
};



class Solution2 {
public:
	bool increasingTriplet(vector<int>& nums) {
		int min1 = 0, min2 = -1; 
		for (int i = 0; i < nums.size(); ++i){
			if (nums[min1] >= nums[i])
				min1 = i;
			else if (min2 == -1)
				min2 = i;
			else if (nums[min2] >= nums[i])
				min2 = i;
			else
				return true; 
		}
		return false; 
	}
}; 


int main()
{
	Solution2 a;
	vector<int> b = { 5, 4, 3, 2, 1 }; 
	vector<int> b2 = { 1, 2, 3, 4, 5 };
	cout << a.increasingTriplet(b) << endl;
	cout << a.increasingTriplet(b2) << endl;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/


}

