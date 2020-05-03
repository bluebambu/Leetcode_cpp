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
// Given two integer arrays A and B, return the maximum length of an subarray that appears in both arrays.

// Example 1:

// Input:
// A: [1,2,3,2,1]
// B: [3,2,1,4,7]
// Output: 3
// Explanation: 
// The repeated subarray with maximum length is [3, 2, 1].

// Note:
//     1 <= len(A), len(B) <= 1000
//     0 <= A[i], B[i] < 100

// pass ac
class Solution {
public:
	int findLength(vector<int>& A, vector<int>& B) {
		// dp[i][j] = a[i]==a[j] : dp[i-1][j-1]
		//            a[i]!=a[j] : 
		int n = A.size(), m = B.size(); 
		vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0)); 

		int res = 0; 

		for (int i = 1; i < n + 1; ++i){
			for (int j = 1; j < m + 1; ++j){
				if (A[i-1] == B[j-1]){
					dp[i][j] = dp[i - 1][j - 1] + 1; 
					res = max(res, dp[i][j]); 
				}
			}
		}
		return res; 
	}
};







int main(){
	Solution a; 

	vector<int> b = { 4, 1, -9, 0  }; 
	vector<int> c = { 3, 4, 1, -9, 0  }; 
	a.findLength(b, c); 


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

