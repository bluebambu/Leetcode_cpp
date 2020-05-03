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
// Say you have an array for which the ith element is the price of a given stock on day i.
// Design an algorithm to find the maximum profit.You may complete at most k transactions.
// Note:
// You may not engage in multiple transactions at the same time(ie, you must sell the stock before you buy again).



// passAC, most basic solution. 
class Solution {
public:
	int maxProfit(int k, vector<int>& prices) {
		if (k > prices.size() / 2){ // degrade to a Buy/Sell Stock II problem
			int res = 0; 
			for (int i = 1; i < prices.size(); ++i){
				if (prices[i] > prices[i - 1])
					res += prices[i] - prices[i - 1]; 
			}
			return res; 
		}

		int n = prices.size(); 
		// global[i][k] = max(global[i-1][k], local[i][k])
		// local[i][k] = max(global[i-1][k-1], local[i-1][k]) + (prices[i]-prices[j])
		vector<vector<int>> global(n, vector<int>(k+1, 0)); 
		vector<vector<int>> local = global; 

		for (int i = 1; i < n; ++i){
			for (int j = 1; j <=k; ++j){
				local[i][j] = max(global[i - 1][j - 1], local[i - 1][j]) +
					(prices[i] - prices[i - 1]); 
				global[i][j] = max(global[i - 1][j], local[i][j]); 
			}
		}

		return global[n - 1][k]; 
	}
};


// 1st simplification
class Solution2 {
public:
	int maxProfit(int k, vector<int>& prices) {
		if (k > prices.size() / 2){ // degrade to a Buy/Sell Stock II problem
			int res = 0;
			for (int i = 1; i < prices.size(); ++i){
				if (prices[i] > prices[i - 1])
					res += prices[i] - prices[i - 1];
			}
			return res;
		}

		int n = prices.size();

		vector<int> l(k + 1, 0), g(k + 1, 0); 

		for (int i = 1; i < n ; ++i){
			int preG = 0, diff = prices[i] - prices[i - 1];
			for (int j = 1; j <= k; ++j){
				l[j] = max(l[j], preG) + diff; 
				preG = g[j]; 
				g[j] = max(g[j], l[j]); 
			}
		}
		return g[k]; 
	}
};


class Solution3 {
public:
	int maxProfit(int k, vector<int>& prices) {
		int n = prices.size(); 
		vector<vector<int>> maxp(n, vector<int>(n, 0)); 
		for (int i = 0; i < n; ++i){
			int lowest = prices[i]; 
			for (int j = i; j < n; ++j){
				lowest = min(lowest, prices[j]); 
				maxp[i][j] = prices[j] - lowest; 
			}
		}

		vector<vector<int>> dp(n, vector<int>(k + 1, 0)); 
		// dp[i][k] = max( j: i->0 :   maxp[j,i]+dp[j][k-1])
		for (int i = 0; i < n; ++i){
			for (int j = 1; j <= k; ++j){
				for (int k = 0; k < i; ++k){
					// ...
				}
			}
		}
	}
};

class Solution4 {
public:
	int maxProfit(int k, vector<int>& prices) {
		if (prices.empty())
			return 0; 
		int n = prices.size(); 
		vector<vector<int>> local(n, vector<int>(k+1, 0)), global = local; 
		for (int i = 1; i < n; ++i){
			for (int j = 1; j <= k; ++j){
				local[i][j] = prices[i] - prices[i - 1] + max(local[i - 1][j], global[i - 1][j - 1]); 
				global[i][j] = max(global[i - 1][j], local[i][j]); 
			}
		}
		return global[n - 1][k]; 
	}
}; 


int main(){
	Solution2 a;

	vector<int> b = { 5, 7, 8, 3, 1, 3, 1, 5, 11, 3 }; 

	cout << a.maxProfit(3, b) << endl; 

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

