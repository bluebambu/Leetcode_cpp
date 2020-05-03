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
#include <string> 
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>

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

// Given a positive integer n, find the least number of perfect square numbers
// (for example, 1, 4, 9, 16, ...) which sum to n.

// For example, given n = 12, return 3 because 12 = 4 + 4 + 4; given n = 13, return 2 because 13 = 4 + 9.

// practise
class Solution {
public:
	int numSquares(int n) {
		vector<int> sq(n + 1, INT_MAX); // 0~n 
		sq[0] = 0; 

		for (int i = 0; i < n + 1; ++i){
			for (int j = 1; i + j*j <= n; ++j){
				int id = i + j*j;
				sq[id] = min(sq[id], sq[i] + 1);
			}
		}

		return sq[n];
	}
};


// DP
class Solution2 {
public:
	int numSquares(int n) {
		vector<int> dp(n + 1, INT_MAX);
		dp[0] = 0;
		for (int i = 0; i <= n; ++i) {
			for (int j = 1; i + j * j <= n; ++j) {
				dp[i + j * j] = min(dp[i + j * j], dp[i] + 1); // in case there are multiple combination for one number, 4 = 1+1+1+1 = 2*2
			}
		}
		return dp.back();
	}
};

//
class Solution3 {
public:
	int numSquares(int n) {
		if (n < 1)
			return 0;
		if (n == 1)
			return 1; 

		unordered_map<int, int> m; 
		return helper(n, m); 
	}

	int helper(int n, unordered_map<int, int>& m){
		if (n < 1)
			return 0;
		if (n == 1)
			return 1; 
		if (m.count(n))
			return m[n]; 

		int res = INT_MAX; 
		for (int i = sqrt(n); i >= 1; --i){
			res = min(res, helper(n - i*i, m)); 
		}
		m[n] = res+1; 
		return res+1; 
	}
};


// online good answer - BFS!!!
// 4.Breadth - First Search : 80ms
class Solution
{
public:
	int numSquares(int n)
	{
		if (n <= 0)
		{
			return 0;
		}

		// perfectSquares contain all perfect square numbers which 
		// are smaller than or equal to n.
		vector<int> perfectSquares;
		// cntPerfectSquares[i - 1] = the least number of perfect 
		// square numbers which sum to i.
		vector<int> cntPerfectSquares(n);

		// Get all the perfect square numbers which are smaller than 
		// or equal to n.
		for (int i = 1; i*i <= n; i++)
		{
			perfectSquares.push_back(i*i);
			cntPerfectSquares[i*i - 1] = 1;
		}

		// If n is a perfect square number, return 1 immediately.
		if (perfectSquares.back() == n)
		{
			return 1;
		}

		// Consider a graph which consists of number 0, 1,...,n as
		// its nodes. Node j is connected to node i via an edge if  
		// and only if either j = i + (a perfect square number) or 
		// i = j + (a perfect square number). Starting from node 0, 
		// do the breadth-first search. If we reach node n at step 
		// m, then the least number of perfect square numbers which 
		// sum to n is m. Here since we have already obtained the 
		// perfect square numbers, we have actually finished the 
		// search at step 1.
		queue<int> searchQ;
		for (auto& i : perfectSquares)
		{
			searchQ.push(i);
		}

		int currCntPerfectSquares = 1;
		while (!searchQ.empty())
		{
			currCntPerfectSquares++;

			int searchQSize = searchQ.size();
			for (int i = 0; i < searchQSize; i++)
			{
				int tmp = searchQ.front();
				// Check the neighbors of node tmp which are the sum 
				// of tmp and a perfect square number.
				for (auto& j : perfectSquares)
				{
					if (tmp + j == n)
					{
						// We have reached node n.
						return currCntPerfectSquares;
					}
					else if ((tmp + j < n) && (cntPerfectSquares[tmp + j - 1] == 0))
					{
						// If cntPerfectSquares[tmp + j - 1] > 0, this is not 
						// the first time that we visit this node and we should 
						// skip the node (tmp + j).
						cntPerfectSquares[tmp + j - 1] = currCntPerfectSquares;
						searchQ.push(tmp + j);
					}
					else if (tmp + j > n)
					{
						// We don't need to consider the nodes which are greater ]
						// than n.
						break;
					}
				}

				searchQ.pop();
			}
		}

		return 0;
	}
};

int main()
{
	Solution a;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/

	a.flatten(tree);
}

