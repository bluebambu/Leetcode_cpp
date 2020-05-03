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
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>

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


//Given a list of non - negative numbers and a target integer k, write a function to check if the 
//array has a continuous subarray of size at least 2 that sums up to the multiple of k, that is, sums
//up to n*k where n is also an integer.
//
//Example 1:
//Input : [23, 2, 4, 6, 7], k = 6
//Output : True
//Explanation : Because[2, 4] is a continuous subarray of size 2 and sums up to 6.
//
//Example 2 :
//Input : [23, 2, 6, 4, 7], k = 6
//Output : True
//Explanation : Because[23, 2, 6, 4, 7] is an continuous subarray of size 5 and sums up to 42.
//

// specifically process k==0 case, in fact you don't have to do this.
class Solution {
public:
	bool checkSubarraySum(vector<int>& nums, int k) {
		if (k == 0){
			for (int i = 0; i < nums.size(); ++i){
				if (nums[i] == 0){
					int j = i+1; 
					for (; j < nums.size() && nums[j] == 0; ++j); 
					if (j-i >= 2)
						return true; 
					i = j - 1; 
				}
			}
			return false; 
		}

		unordered_map<int, int> sums; 
		sums[0] = -1; 

		long long cum = 0; 
		for (int i = 0; i < nums.size(); ++i){
			cum += nums[i]; 
			int target = cum%k;
			
			if (sums.count(target) && i - sums[target] >= 2)
				return true; 

			if (sums.count(target))
				sums[target] = min(sums[target], i);
			else
				sums[target] = i; 
		}
		return false; 
	}
};


// specifically process k==0 case, in fact you don't have to do this.
// 还有就是题目要求子数组至少需要两个数字，那么我们需要一个变量pre来记录之前的和，我们每次存入set中的是pre，而不是当前的累积和，
class Solution {
public:
	bool checkSubarraySum(vector<int>& nums, int k) {
		unordered_set<int> pre; 

		int last = 0; 

		int cum = 0; 
		for (int i = 0; i < nums.size(); ++i){
			cum += nums[i]; 

			int target = k == 0 ? cum : cum%k; 

			if (pre.count(target))
				return true; 
			pre.insert(last); 
			last = target; 
		}
		return false; 
	}
};




int main()
{
	Solution a;
	vector<int> b{ 2, 4, 5, 6, 7, 9 }; 
	cout<<a.checkSubarraySum(b, 9); 

}

