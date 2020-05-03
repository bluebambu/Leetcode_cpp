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
//  Nearly every one have used the Multiplication Table. But could you find out the k-th smallest number quickly from the multiplication table?

// Given the height m and the length n of a m * n Multiplication Table, and a positive integer k, you need to return the k-th smallest number in this table.

// Example 1:

// Input: m = 3, n = 3, k = 5
// Output: 
// Explanation: 
// The Multiplication Table:
// 1	2	3
// 2	4	6
// 3	6	9

// The 5-th smallest number is 3 (1, 2, 2, 3, 3).

// Example 2:

// Input: m = 2, n = 3, k = 6
// Output: 
// Explanation: 
// The Multiplication Table:
// 1	2	3
// 2	4	6

// The 6-th smallest number is 6 (1, 2, 2, 3, 4, 6).

// Note:

//     The m and n will be in the range [1, 30000].
//     The k will be in the range [1, m * n]



// 1,2,3,4,5
// 2,4,6,8,10
// 3,6,9,12,15


// pass AC. very tricky, lots of corner case
class Solution {
public:
	int findKthNumber(int m, int n, int k) {
		int left = 0, right = m*n, mid; 
		while (left < right - 1){
			mid = left + (right - left) / 2; 
			int rank = getRank(m, n, mid); 
			if (k <= rank)
				right = mid;
			else
				left = mid; 
		}
		return right; 
	}

	int getRank(int m, int n, int num){
		// first, don't use 0-based index. Not necessary, and very complicated
		// second, j index must be checked, otherwise it might go out of boundary
		int cnt = 0, i = m, j = 1; 
		while (i >= 1 && j <= n){
			int preJ = j; 
			j = (num / i + 1) <= n ? (num / i + 1) : n + 1; 
			cnt += (j - preJ)*i; 
			i = num / j; 
		}
		return cnt; 
	}
};

// easier solution
class Solution2 {
public:
	int findKthNumber(int m, int n, int k) {
		int left = 1, right = m * n;
		while (left < right) {
			int mid = left + (right - left) / 2, cnt = 0;
			for (int i = 1; i <= m; ++i) {
				cnt += (mid > n * i) ? n : (mid / i);
			}
			if (cnt < k) left = mid + 1;
			else right = mid;
		}
		return left;
	}
};


class Solution2 {
public:
	int findKthNumber(int m, int n, int k) {
	
	}
};


int main(){
	Solution a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	cout << a.findKthNumber(2, 3, 6); 


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

