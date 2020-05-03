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
// Given a grid where each entry is only 0 or 1, find the number of corner rectangles.

// A corner rectangle is 4 distinct 1s on the grid that form an axis-aligned rectangle. Note that only the corners need to have the value 1. Also, all four 1s used must be distinct.

//  

// Example 1:

// Input: grid = 
// [[1, 0, 0, 1, 0],
//  [0, 0, 1, 0, 1],
//  [0, 0, 0, 1, 0],
//  [1, 0, 1, 0, 1]]
// Output: 1
// Explanation: There is only one corner rectangle, with corners grid[1][2], grid[1][4], grid[3][2], grid[3][4].

//  

// Example 2:

// Input: grid = 
// [[1, 1, 1],
//  [1, 1, 1],
//  [1, 1, 1]]
// Output: 9
// Explanation: There are four 2x2 rectangles, four 2x3 and 3x2 rectangles, and one 3x3 rectangle.

//  

// Example 3:

// Input: grid = 
// [[1, 1, 1, 1]]
// Output: 0
// Explanation: Rectangles must have four distinct corners.

// pass AC
class Solution {
public:
	int countCornerRectangles(vector<vector<int>>& grid) {
		if (grid.empty() || grid[0].empty())
			return 0; 

		int res = 0; 
		int n = grid.size(), m = grid[0].size(); 

		for (int i = 0; i < n; ++i){
			for (int j = i + 1; j < n; ++j){
				int cnt = 0; 
				for (int k = 0; k < m; ++k){
					if (grid[i][k] == 1 && grid[j][k] == 1)
						++cnt; 
				}
				res += cnt*(cnt - 1)/2;
			}
		}

		return res; 
	}
};


class Solution2 {
public:
	int countCornerRectangles(vector<vector<int>>& grid) {
		if (grid.empty() || grid[0].empty())
			return 0; 

		int n = grid.size(), m = grid[0].size(), cnt = 0; 
		for (int i = 0; i < n; ++i){
			vector<int> ones; 
			for (int k = 0; k < m; ++k)
				if (grid[i][k] == 1)
					ones.push_back(k); 


			for (int j = i + 1; j < n; ++j){
				int cur = 0; 
				for (auto k : ones)
					if (grid[j][k] == 1)
						cur += 1; 

				cnt += cur*(cur - 1) / 2; 
			} 
		}
		return cnt; 
	}
}; 


class Solution3 {
public:
	int countCornerRectangles(vector<vector<int>>& grid) {
		int res = 0; 
		int n = grid.size(), m = grid[0].size(); 
		for (int i = 0; i < n; ++i){
			for (int j = i + 1; j < n; ++j){
				int both_one = 0; 
				for (int k = 0; k < m; ++k){
					if (grid[i][k] == 1 && grid[j][k] == 1)
						both_one += 1; 
				}
				res += (both_one - 1)*(both_one - 2); 
			}
		}
		return res; 
	}
};

class Solution4 {
public:
	int countCornerRectangles(vector<vector<int>>& grid) {
		int res = 0; 
		int n = grid.size(), m = grid[0].size(); 
		for (int i = 0; i < n; ++i){
			vector<int> pos_of_one; 
			for (int k = 0; k < m; ++k)
				if (grid[i][k])
					pos_of_one.push_back(k); 

			for (int j = i + 1; j < n; ++j){
				int match = 0; 
				for (auto pos : pos_of_one){
					if (grid[j][pos])
						match += 1;
				}

				res += match*(match - 1) / 2; 
			}
		}
		return res; 
	}
};


int main(){
	Solution a; 
	Solution2 a2; 

	vector<vector<int>> b = {
		{ 1, 0, 0, 1, 0 },
		{ 0, 0, 1, 0, 1 },
		{ 0, 0, 0, 1, 0 },
		{ 1, 0, 1, 0, 1 }
	}; 
		
	cout << a.countCornerRectangles(b) << endl; 
	cout << a2.countCornerRectangles(b) << endl; 

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

