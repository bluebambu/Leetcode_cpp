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
// Given a 2D binary matrix filled with 0's and 1's, find the largest square containing only 1's and return its area. 
// For example, given the following matrix :
// 1 0 1 0 0
// 1 0 1 1 1
// 1 1 1 1 1
// 1 0 0 1 0
// Return 4.


// pass AC. O(n^3) , calculate cumulative value for columns. 
class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int res = 0; 
		for (int i = 0; i < matrix.size(); ++i){
			vector<int> cum(matrix[i].size(), 0); 
			for (int j = i; j < matrix.size(); ++j){
				for (int k = 0; k < matrix[j].size(); ++k){
					if (matrix[j][k] == '1')
						++cum[k]; 
				}

				res = max(res, area(cum, j - i + 1)); 
			}
		}
		return res; 
	}

	int area(vector<int>& cum, int k){
		int count = 0; 
		for (int i = 0; i < cum.size(); ++i){
			if (cum[i] == k){
				++count; 
			}
			else{
				count = 0; 
				continue;
			}

			if (count == k)
				return k*k; 
		}

		return 0; 
	}
};


// DP method, O(N^2) , cool! 
// dp[i][j] 的值代表的是边长！！ 所以最后return 需要是 res*res!!!!!
// 其实可以不需要整个dp二维数组，一维数组不断迭代就可以。 dp的常见优化策略。： 
// The hardest part is still to find the **transition formula** !!!!
class Solution2 {
public:
	int maximalSquare(vector<string>& matrix) {
		if (matrix.empty())
			return 0; 

		int n = matrix.size(), m = matrix[0].size(); 
		int res = 0; 
		vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

		for (int i = 1; i < n + 1; ++i){
			for (int j = 1; j < m + 1; ++j){
				if (matrix[i - 1][j - 1] == '1'){
					dp[i][j] = min(dp[i - 1][j - 1], min(dp[i - 1][j], dp[i][j - 1])) + 1; 
					res = max(res, dp[i][j]); 
				}
			}

			vvprt(dp); 

			cout << endl << "=============================\n\n"; 
		}

		return res*res; 
	}
}; 

class Solution3{
public:
	int maximalSqure(vector<vector<char>>& matrix){
		int res = 0; 
		if (matrix.empty())
			return res; 

		for (int i = 0; i < matrix.size(); ++i){
			vector<int> cum(matrix[0].size(), 0); 
			for (int j = i; j < matrix.size(); ++j){
				for (int k = 0; k < matrix[0].size(); ++k){
					if (matrix[j][k] == '1')
						cum[k] += 1; 
				}

				int count = 0, cur_h = j - i + 1;
				for (int k = 0; k < matrix[0].size(); ++k){
					if (cum[k] != cur_h){
						count = 0; 
						continue;
					}

					++count; 

					if (count == cur_h)
						res = max(res, cur_h*cur_h); 
				}
			}
		}

		return res; 
	}
};



class Solution4{
public:
	int maximalSquare(vector<string>& matrix){
		if (matrix.empty() || matrix[0].empty())
			return 0; 

		int n = matrix.size(), m = matrix[0].size(); 
		vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0)); 
		int res = 0; 

		for (int i = 1; i <= n; ++i){
			for (int j = 1; j <= m; ++j){
				if (matrix[i - 1][j - 1] == '0')
					dp[i][j] = 0;
				else if (dp[i - 1][j - 1] == '0')
					dp[i][j] = 1; 
				else{
					int lastSqSz = dp[i - 1][j - 1]; 
					dp[i][j] = 1; 
					for (int side = 0; side < lastSqSz; ++side){
						if (matrix[i - side - 2][j - 1] == '0' ||
							matrix[i - 1][j - side - 2] == '0'
							)
							break; 
						dp[i][j] += 1; 
					}
					res = max(res, dp[i][j] * dp[i][j]); 
				}
			}
		}
		return res; 
	}
};

class Solution5{
public:
	int maximalSquare(vector<string>& matrix){
		if (matrix.empty() || matrix[0].empty())
			return 0; 

		int n = matrix.size(), m = matrix[0].size(); 
		vector<vector<int>> left(n+1, vector<int>(m+1, 0)), up = left; 
		for (int i = 0; i < n; ++i){
			int sum = 0; 
			for (int j = 0; j < m; ++j){
				if (matrix[i][j] == '0')
					sum = 0; 
				else{
					sum += 1; 
					left[i+1][j+1] = sum; 
				}
			}
		}
		for (int j = 0; j < m; ++j){
			int sum = 0; 
			for (int i = 0; i < n; ++i){
				if (matrix[i][j] == '0')
					sum = 0; 
				else{
					sum += 1; 
					up[i+1][j+1] = sum; 
				}
			}
		}

		vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0)); 
		int res = INT_MIN; 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				int x = i + 1, y = j + 1; 
				if (matrix[i][j] == '0')
					dp[x][y] = 0;
				else
					dp[x][y] = min(1 + dp[x - 1][y - 1], min(up[x][y], left[x][y])); 

				res = max(res, dp[x][y]);
			}
		}

		return res*res; 
	}
}; 


class Solution6 {
public:
	int maximalRectangle(vector<vector<char>>& matrix) {
		if (matrix.empty() || matrix[0].empty())
			return 0; 

		int n = matrix.size(), m = matrix[0].size(); 
		vector<vector<int>> rowsum(n, vector<int>(m + 1, 0)); 
		for (int i = 0; i < n; ++i){
			for (int j = m-1; j>=0; --j){
				if (matrix[i][j] == '1')
					rowsum[i][j] = 1 + rowsum[i][j+1];
				else
					rowsum[i][j] = 0; 
			}
		}

		for (auto i : matrix){
			for (auto j : i){
				cout << j << ' '; 
			}
			cout << endl; 
		}
		
		cout << endl; 

		for (auto i : rowsum){
			for (auto j : i){
				cout << j << ' '; 
			}
			cout << endl; 
		}

		int res = INT_MIN; 
		for (int j = 0; j < m; ++j){
			for (int i = 0; i < n; ++i){
				int curmax = INT_MIN, minwid = INT_MAX; 
				for (int k = i; k < n; ++k){
					minwid = min(minwid, rowsum[k][j]); 
					curmax = max(curmax, minwid*(k - i + 1)); 
				}
				res = max(res, curmax); 
			}
		}

		return res; 
	}
};


class Solution7{
public:
	int maximalRectangle(vector<vector<char>>& matrix){
		if (matrix.empty() || matrix[0].empty())
			return 0; 

		int n = matrix.size(), m = matrix[0].size(); 
		int res = INT_MIN; 
		vector<int> colsum(m, 0); 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				if (matrix[i][j] == '1')
					colsum[j] += 1;
				else
					colsum[j] = 0; 
			}

			//for (auto i : colsum)
			//	cout << i << ' '; 
			//cout << endl << endl; 

			res = max(res, maxRct(colsum)); 
		}
		return res; 
	}

	int maxRct(vector<int> nums){
		vector<int> stk; 
		int res = INT_MIN; 

		nums.push_back(0); 
		int n = nums.size(); 
		for (int i = 0; i < n; ++i){
			while (!stk.empty() && nums[stk.back()] >= nums[i]){
				int topop = stk.back(); 
				stk.pop_back(); 
				res = max(res, stk.empty() ? i*nums[topop] : (i - stk.back()-1)*nums[topop]);
			}
			stk.push_back(i); 

			//for (auto i : stk)
			//	cout << nums[i] << ' '; 
			//cout << endl << endl; 
		}

		return res; 
	}
};


int main() {
	Solution7 a;

	vector<vector<char>> b = { 
		{ '1', '0', '1', '0', '0' },
		{ '1', '0', '1', '1', '1' },
		{ '1', '1', '1', '1', '1' },
		{ '1', '0', '0', '1', '0' },
	};

	cout << a.maximalRectangle(b) << endl;

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

