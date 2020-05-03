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


// passed 
//
// binary indexed tree
//
class NumMatrix {
	vector<vector<int>> f; 								
	vector<vector<int>> bit; 
public:
	NumMatrix(vector<vector<int>> &matrix){

		if (matrix.empty() || matrix[0].empty()){
			f = matrix; 
			return; 
		}

		f = vector<vector<int>>(matrix.size()+1, vector<int>(matrix[0].size() + 1));
		bit = vector<vector<int>>(matrix.size()+1, vector<int>(matrix[0].size() + 1));
		
		for (int i = 1; i < f.size(); ++i)
			for (int j = 1; j < f[0].size(); ++j)
				update(i - 1, j - 1, matrix[i - 1][j - 1]); 
		
	}

	void update(int row, int col, int val) {
		if (f.empty() || f[0].empty())
			return; 

		int diff = val - f[row + 1][col + 1]; 
		for (int i = row + 1; i < f.size(); i += i & (-i))
			for (int j = col + 1; j < f[0].size(); j += j & (-j))
				bit[i][j] += diff; 
		f[row + 1][col + 1] = val; 
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		return getSum(row2, col2) 
				- getSum(row2, col1 - 1) 
				- getSum(row1 - 1, col2) 
				+ getSum(row1 - 1, col1 - 1); 
	}

	int getSum(int row, int col){
		if (f.empty() || f[0].empty())
			return 0;

		int res = 0; 
		for (int i = row + 1; i > 0; i -= i & (-i))
			for (int j = col + 1; j > 0; j -= j & (-j))
				res += bit[i][j]; 
		return res; 
	}
};


// pass! pay attention to empty matrix situation!
class NumMatrix2 {
public:
	vector<vector<int>> f; 
	vector<vector<int>> bit; 

	NumMatrix2(vector<vector<int>> matrix) {
		if (matrix.empty() || matrix[0].empty()){
			f = bit = vector<vector<int>>(); 
			return; 
		}

		int n = matrix.size(), m = matrix[0].size(); 

		f = bit = vector<vector<int>>(n + 1, vector<int>(m + 1, 0));

		for (int i = 0; i < n; ++i){
			for (int j = 0; j < m; ++j){
				update(i, j, matrix[i][j]); 
			}
		}
	}

	void update(int row, int col, int val) {
		if (bit.empty() || bit[0].empty()){
			return; 
		}

		int diff = val - f[row + 1][col + 1]; 
		f[row + 1][col + 1] = val; 
		for (int i = row + 1; i < bit.size(); i += (i&(-i))){
			for (int j = col + 1; j < bit[0].size(); j += (j&(-j))){
				bit[i][j] += diff; 
			}
		}
	}


	int cumsum(int row, int col){
		if (bit.empty() || bit[0].empty()){
			return 0; 
		}
		int res = 0; 
		for (int i = row + 1; i > 0; i -= (i&(-i))){
			for (int j = col + 1; j > 0; j -= (j&(-j))){
				res += bit[i][j]; 
			}
		}
		return res; 
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		if (bit.empty() || bit[0].empty()){
			return 0; 
		}
		return cumsum(row2, col2)
			- cumsum(row2, col1 - 1)
			- cumsum(row1 - 1, col2)
			+ cumsum(row1 - 1, col1 - 1); 
	}
};

class NumMatrix {
public:
	int n, m; 
	vector<vector<int>> copy; 
	vector<vector<int>> bit; 

    NumMatrix(vector<vector<int>> matrix) {
		       
    }
    
    void update(int row, int col, int val) {
        
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        
    }
};


int main()
{
	vector<vector<int>> a = { { 3, 0, 1, 4, 2 }, 
							  { 5, 6, 3, 2, 1 }, 
							  { 1, 2, 0, 1, 5 }, 
							  { 4, 1, 0, 1, 7 }, 
							  { 1, 0, 3, 0, 5 } };
	NumMatrix b(a);

	cout << b.sumRegion(2, 1, 4, 4); 

	NumMatrix2 c(a);

	cout << c.sumRegion(2, 1, 4, 4); 
}

