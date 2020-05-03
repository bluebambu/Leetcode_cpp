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
// Given two sparse matrices A and B, return the result of AB.
// You may assume that A's column number is equal to B's row number.
// Example:
// A = [
// 		[1, 0, 0],
// 		[-1, 0, 3]
// ]

// B = [
// 		[7, 0, 0],
// 		[0, 0, 0],
// 		[0, 0, 1]
// ]


// 		| 1 0 0 |    | 7 0 0 |   | 7 0 0 |
// AB = | -1 0 3 | x | 0 0 0 | = | -7 0 3 |
// 				     | 0 0 1 |



// pass AC. 不用hashmap也行， 直接遍历vector 判断， 会慢一点。 
class Solution {
public:
	vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
		vector<unordered_map<int, int>> am(A.size()), bm(B[0].size()); 
		for (int i = 0; i < A.size(); ++i){
			for (int j = 0; j < A[0].size(); ++j){
				if (A[i][j] != 0)
					am[i][j] = A[i][j]; 
			}
		}
		for (int j = 0; j < B[0].size(); ++j){
			for (int i = 0; i < B.size(); ++i){
				if (B[i][j] != 0)
					bm[j][i] = B[i][j]; 
			}
		}

		vector<vector<int>> res(am.size(), vector<int>(bm.size(), 0)); 
		for (int i = 0; i < am.size(); ++i){
			for (int j = 0; j < bm.size(); ++j){
				// am[i]  bm[j]
				int cur = 0;
				for (auto& v : am[i]){
					int pos = v.first, val = v.second; 
					if (bm[j].count(pos)){
						cur += val*bm[j][pos]; 
					}
				}
				res[i][j] = cur; 
			}
		}
		return res; 
	}
};



int main() {
	Solution a;

	// TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/

}

