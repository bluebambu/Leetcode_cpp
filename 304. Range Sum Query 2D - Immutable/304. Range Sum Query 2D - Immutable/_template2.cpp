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
// Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2).

// The above rectangle (with the red border) is defined by (row1, col1) = (2, 1) and (row2, col2) = (4, 3), which contains sum = 8. 
// Example:
// Given matrix = [
//   [3, 0, 1, 4, 2},
//   [5, 6, 3, 2, 1],
//   [1, 2, 0, 1, 5],
//   [4, 1, 0, 1, 7],
//   [1, 0, 3, 0, 5]
// ]

// sumRegion(2, 1, 4, 3) -> 8
// sumRegion(1, 1, 2, 2) -> 11
// sumRegion(1, 2, 2, 4) -> 12




class NumMatrix {
public:
	vector<vector<int>> sums; 

	NumMatrix(vector<vector<int>> matrix){
		int n = matrix.size(), m = matrix[0].size(); 
		sums = vector<vector<int>>(n+1, vector<int>(m+1, 0)); 

		for (int i = 1; i <= n; ++i){
			int tmp = 0; 
			for (int j = 1; j <= m; ++j){
				tmp += matrix[i - 1][j - 1]; 
				sums[i][j] = tmp; 
			}
		}

	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		int res = 0; 
		for (int i = row1; i <= row2; ++i){
			res += sums[i+1][col2 + 1] - sums[i+1][col1]; 
		}
		return res; 
	}
};

/**
* Your NumMatrix object will be instantiated and called as such:
* NumMatrix obj = new NumMatrix(matrix);
* int param_1 = obj.sumRegion(row1,col1,row2,col2);
*/






int main(){

	vector<int> b = { 7, 2, 5, 10, INT_MAX };

	vector<vector<int>> matrix = \
	{
		{3, 0, 1, 4, 2},
		{5, 6, 3, 2, 1},
		{1, 2, 0, 1, 5},
		{4, 1, 0, 1, 7},
		{1, 0, 3, 0, 5}
	}; 

	NumMatrix a(matrix); 

	cout << a.sumRegion(2, 1, 4, 3); 

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

