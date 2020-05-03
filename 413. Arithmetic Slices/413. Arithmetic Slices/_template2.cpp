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
// A sequence of number is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
// For example, these are arithmetic sequence:
// 1, 3, 5, 7, 9
// 7, 7, 7, 7
// 3, -1, -5, -9
// The following sequence is not arithmetic.
// 1, 1, 2, 5, 7

// A zero-indexed array A consisting of N numbers is given. A slice of that array is any pair of integers (P, Q) such that 0 <= P < Q < N.
// A slice (P, Q) of array A is called arithmetic if the sequence:
// A[P], A[p + 1], ..., A[Q - 1], A[Q] is arithmetic. In particular, this means that P + 1 < Q.
// The function should return the number of arithmetic slices in the array A. 

// Example: 
// A = [1, 2, 3, 4]

// return: 3, for 3 arithmetic slices in A: [1, 2, 3], [2, 3, 4] and [1, 2, 3, 4] itself.




class Solution {
public:
	int numberOfArithmeticSlices(vector<int>& nums) {
		if (nums.size() < 3)
			return 0; 

		int cons = 1, res = 0, prev = nums[1] - nums[0];
		for (int i = 2; i < nums.size(); ++i){
			if (nums[i] - nums[i - 1] == prev){
				cons++; 
			}
			else{
				prev = nums[i] - nums[i - 1]; 
				if (cons >= 2)
					res += (cons)*(cons - 1) / 2; 
				cons = 1; 
			}
		}

		// specific for consecutive sequence at the end of nums; 
		if (cons >= 2)
			res += (cons)*(cons - 1) / 2;
		return res; 
	}
};


// DP solution! dp[i] is local dp value. 
class Solution {
public:
	int numberOfArithmeticSlices(vector<int>& A) {
		int n = A.size();
		if (n < 3) return 0;
		vector<int> dp(n, 0); // dp[i] means the number of arithmetic slices ending with A[i]
		if (A[2] - A[1] == A[1] - A[0]) dp[2] = 1; // if the first three numbers are arithmetic or not
		int result = dp[2];
		for (int i = 3; i < n; ++i) {
			// if A[i-2], A[i-1], A[i] are arithmetic, then the number of arithmetic slices ending with A[i] (dp[i])
			// equals to:
			//      the number of arithmetic slices ending with A[i-1] (dp[i-1], all these arithmetic slices appending A[i] are also arithmetic)
			//      +
			//      A[i-2], A[i-1], A[i] (a brand new arithmetic slice)
			// it is how dp[i] = dp[i-1] + 1 comes
			if (A[i] - A[i - 1] == A[i - 1] - A[i - 2])
				dp[i] = dp[i - 1] + 1;
			result += dp[i]; // accumulate all valid slices
		}
		return result;
	}
};


// DP solution! dp[i] is local dp value. 
class Solution {
public:
	int numberOfArithmeticSlices(vector<int>& A) {
		if (A.size() < 3)
			return 0; 

		int res = 0; 
		vector<int> dp(A.size(), 0); 
		for (int i = 2; i < A.size(); ++i){
			if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]){
				dp[i] = dp[i - 1] + 1;
				res += dp[i];
			}
		}
		return res; 
	}
};



int main(){
	Solution a;

	vector<int> b = { 1, 2, 3, 4 };

	cout << a.numberOfArithmeticSlices(b); 

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

