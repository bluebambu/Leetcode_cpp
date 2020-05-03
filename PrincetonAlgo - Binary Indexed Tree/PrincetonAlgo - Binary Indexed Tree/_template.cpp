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


class BIT
{
	vector<int> f;
	vector<int> bit; 
public:
	BIT(vector<int>& nums){
		if (nums.empty())
			return; 
		f.resize(nums.size() + 1); 
		bit.resize(nums.size() + 1); 
		for (int i = 0; i < nums.size(); ++i)
			update(i, nums[i]); 
	}

	void update(int i, int val){
		if (bit.empty())
			return; 
		int diff = val - f[i + 1]; 
		for (int j = i + 1; j < bit.size(); j += j&(-j))
			bit[j] += diff; 
		f[i + 1] = val; 
	}

	void rangeSum(int i, int j){
		return getSum(j + 1) - getSum(i); 
	}

	int getSum(int i){
		if (bit.empty())
			return 0; 
		int res = 0; 
		for (int j = i + 1; j > 0; j -= j&(-j))	  //  e.g., sum[1011] = bit[1011] + bit[1010] + bit[1000];
			res += bit[j]; 
		return res; 
	}

	int getCur(int i){
		// return f[i+1];
	}
};

class BIT2D{
	vector<vector<int>> f; 
	vector<vector<int>> bit; 
public:
	BIT2D(vector<vector<int>>& matrix){
		if (matrix.empty() || matrix[0].empty())
			return; 
		f = vector<vector<int>>(matrix.size() + 1, vector<int>(matrix[0].size() + 1)); 
		bit = vector<vector<int>>(matrix.size() + 1, vector<int>(matrix[0].size() + 1));

		for (int i = 0; i < matrix.size(); ++i)
			for (int j = 0; j < matrix[0].size(); ++j)
				update(i, j, matrix[i][j]);
	}

	void update(int i, int j, int val){
		if (bit.empty() || bit[0].empty())
			return; 
		int diff = val - f[i + 1][j + 1]; 
		for (int row = i + 1; row < bit.size(); row += row&(-row))
			for (int col = j + 1; col < bit[0].size(); col += col&(-col))
				bit[row][col] += diff; 
		f[i + 1][j + 1] = val; 
	}

	int getSum(int i, int j){
		int res = 0; 
		for (int row = i + 1; row > 0; row -= row&(-row))
			for (int col = j + 1; j > 0; col -= col&(-col))
				res += bit[row][col]; 
		return res; 
	}

	int rangeSum(int r1, int c1, int r2, int c2){
		return getSum(r2, c2) - getSum(r2, c1 - 1) - getSum(r1 - 1, c2) + getSum(r1 - 1, c1 - 1); 
	}


};

int main()
{



}

