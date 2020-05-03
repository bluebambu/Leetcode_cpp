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
// Given a non - empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix such that its sum is no larger than k.

// Example:

// Given matrix = [
// 	[1, 0, 1],
// 	[0, -2, 3]
// ]
// k = 2

// The answer is 2. Because the sum of rectangle[[0, 1], [-2, 3]] is 2 and 2 is the max number no larger than k(k = 2).

// Note:

// The rectangle inside the matrix must have an area > 0.
// What if the number of rows is much larger than the number of columns ?


class Solution {
public:
	int maxSumSubmatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.empty() || matrix[0].empty())
			return 0; 

		int n = matrix.size(), m = matrix[0].size(); 
		vector<vector<int>> cumsum(n + 1, vector<int>(m + 1, 0)); 

		int res = INT_MIN; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				cumsum[i + 1][j + 1] += cumsum[i + 1][j] + cumsum[i][j + 1] - cumsum[i][j] + matrix[i][j]; 

				for (int l = 0; l < i + 1; ++l){
					for (int k = 0; k < j + 1; ++k){
						int curRec = cumsum[i + 1][j + 1] - cumsum[i + 1][k] - cumsum[l][j + 1] + cumsum[l][k]; 
						if (curRec > res && curRec <= target){
							res = curRec; 
						}
					}
				}
			}
		}

		prt2Layer(cumsum); 

		return res; 
	}
};


// wrong solution. Calculate max subarray is not right here, b/c max subarray might be bigger than target. 
class Solution2{
public:
	int maxSumSubmatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.empty() || matrix[0].empty())
			return 0; 

		int n = matrix.size(), m = matrix[0].size(); 
		vector<int> colSum(m, 0); 

		int res = INT_MIN; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				colSum[j] += matrix[i][j]; 
			}

			int cur = colSum[0]; 
			for (int j = 1; j < m; ++j){
				if (cur < 0)
					cur = colSum[j];
				else
					cur += colSum[j]; 

				if (cur > res && cur <= target)
					res = cur; 
			}
		}
		return res; 
	}
};

// pass , brute force
class Solution3{
public:

	int area(vector<vector<int>>& cum, int a, int b, int c, int d){
		return cum[c + 1][d + 1] - cum[a][d + 1] - cum[c + 1][b] + cum[a][b]; 
	}
	int maxSumSubmatrix(vector<vector<int>>& matrix, int target) {
		int n = matrix.size(), m = matrix[0].size(); 
		vector<vector<int>> cum(n + 1, vector<int>(m + 1, 0)); 
		int res = INT_MIN; 
		for (int i = 1; i <= n; ++i){
			for (int j = 1; j <= m; ++j){
				cum[i][j] = cum[i - 1][j] + cum[i][j - 1] - cum[i - 1][j - 1] + matrix[i - 1][j - 1]; 
			}
		}

		for (int a = 0; a < n; ++a){
			for (int b = 0; b < m; ++b){
				for (int c = a; c < n; ++c){
					for (int d = b; d < m; ++d){
						int tmp = area(cum, a, b, c, d); 
						if (tmp <= target && tmp > res)
							res = tmp; 
					}
				}
			}
		}

		return res; 
	}
};


class Solution4{
public:
	int maxSumSubmatrix(vector<vector<int>>& matrix, int target) {
		int n = matrix.size(), m = matrix[0].size(); 
		vector<vector<int>> cumsum(n + 1, vector<int>(m + 1, 0));
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				cumsum[i + 1][j + 1] = cumsum[i][j + 1] + cumsum[i + 1][j] - cumsum[i][j] + matrix[i][j]; 
			}
		}

		prt2Layer(cumsum); 

		int res = INT_MIN;
		for (int i = 0; i < n; ++i){
			for (int ii = i; ii < n; ++ii){
				set<int> pre;
				pre.insert(0);
				for (int j = 0; j < m; ++j){
					int curSum = cumsum[ii + 1][j + 1] - cumsum[i][j + 1]; 

					cout << i << ":" << ii << ":" << j << ":" << curSum << endl; 
					if (pre.lower_bound(curSum - target) != pre.end()){
						int cand = *(pre.lower_bound(curSum - target)); 
						res = max(res, curSum-cand); 
					}
					pre.insert(curSum);
				}
			}
		}

		return res; 
	}
};



class Solution5 {
public:
	int maxSumSubmatrix(vector<vector<int>>& matrix, int target) {
		if (matrix.empty() || matrix[0].empty())
			return 0; 

		int n = matrix.size(), m = matrix[0].size(); 
		vector<vector<int>> cum(n + 1, vector<int>(m + 1, 0)); 

		int res = INT_MIN; 
		for (int i = 1; i <= n; ++i){
			for (int j = 1; j <= m; ++j){
				cum[i][j] = cum[i - 1][j] + matrix[i - 1][j - 1]; 
			}

			for (int ii = 1; ii <= i; ++ii){
				set<int> cache;
				int cumsum = 0; 
				for (int j = 0; j <= m; ++j){
					cumsum += cum[i][j] - cum[ii - 1][j]; 
					if (j > 0){
						auto jj = cache.lower_bound(cumsum - target);
						if (jj != cache.end()){
							res = max(res, cumsum - *jj); 
						}
					}
					cache.insert(cumsum); 
				}
				cout << endl; 
			}
		}
		return res; 
	}
};

int main(){
	Solution4 a; 
	Solution5 a2; 

	vector<vector<int>> b = { 
		{ 1, 0, 1 }, 
		{ 0, -2, 3 }
	};

	vector<vector<int>> bb = { { 2, 2, -1 } }; 

	cout << a.maxSumSubmatrix(b, 3) << endl;
	cout << a2.maxSumSubmatrix(b, 3) << endl;


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

