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
// Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.

// For example, given the following matrix :

// 1 0 1 0 0
// 1 0 1 1 1
// 1 1 1 1 1
// 1 0 0 1 0

// Return 6.


// this is wrong answer!!!
typedef pair<int, int> PII; 
class Solution {
public:
	int maximalRectangle(vector<vector<char>>& matrix) {
		if (matrix.empty() || matrix[0].empty())
			return 0; 

		int n = matrix.size(), m = matrix[0].size(); 

		vector<vector<PII>> dp(n + 1, vector<PII>(m + 1, { 0, 0 }));

		int res = 0; 

		for (int i = 1; i <= n; ++i){
			for (int j = 1; j <= m; ++j){
				if (matrix[i - 1][j - 1] == 0)
					dp[i][j] = {0,0};
				else{
					int prew = dp[i - 1][j - 1].first, prer = dp[i - 1][j - 1].second; 

					int curw = 1, curr = 1; 
					for (int ii = 0; j-2-ii >= 0 ; ++ii){
						if (matrix[i - 1][j-2-ii] == '0')
							break;
						curw += 1; 
					}
					for (int jj = 0; i-2-jj >= 0 ; ++jj){
						if (matrix[i - 2 - jj][j - 1] == '0')
							break;
						curr += 1; 
					}
					dp[i][j] = { curw, curr }; 

					res = max(res, curr*curw); 
				}
			}
		}

		return res; 
	}
};


int main(){
	Solution a; 

	vector<vector<char>> b = {
		{ '1', '0', '1', '0', '0' },
		{ '1', '0', '1', '1', '1' },
		{ '1', '1', '1', '1', '1' },
		{ '1', '0', '0', '1', '0' }
	};

	cout << a.maximalRectangle(b) << endl; 



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

