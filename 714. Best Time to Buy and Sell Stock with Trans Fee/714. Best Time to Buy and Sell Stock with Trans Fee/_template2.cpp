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
// Your are given an array of integers prices, for which the i - th element is the price of a given stock on day i; and a non - negative integer fee representing a transaction fee.

// You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.You may not buy more than 1 share of a stock at a time(ie.you must sell the stock share before you buy again.)

// Return the maximum profit you can make.

// Example 1:

// Input : prices = [1, 3, 2, 8, 4, 9], fee = 2
// Output : 8
// 	 Explanation : The maximum profit can be achieved by :
// Buying at prices[0] = 1
// Selling at prices[3] = 8
// Buying at prices[4] = 4
// Selling at prices[5] = 9
// The total profit is((8 - 1) - 2) + ((9 - 4) - 2) = 8.

// Note :
// 	 0 < prices.length <= 50000.
// 	 0 < prices[i] < 50000.
// 	 0 <= fee < 50000.


// pass AC
class Solution {
public:
	int maxProfit(vector<int>& prices, int fee) {
		// local[i] = max( global[i-1] + p[i]-p[i-1], local[i-1] + p[i]-p[i-1] - fee); 
		// global[i] = max( global[i-1], local[i] ); 
		if (prices.empty())
			return 0; 

		int n = prices.size(); 
		vector<int> l(n+1, 0), g = l; 
		l[1] = -fee; 
		
		for (int i = 2; i <= n; ++i){
			int lastDay = prices[i-1] - prices[i - 2]; 
			l[i] = max(g[i - 1] + lastDay - fee, l[i - 1] + lastDay); 
			g[i] = max(g[i - 1], l[i]); 
		}

		return g[n]; 
	}
};

class Solution2 {
public:
	int maxProfit(vector<int>& prices, int fee) {
		// g[i] = max( g[i-1] , max( j E 0->i: g[j-1] + p[i] - p[j] - fee )
		if (prices.empty())
			return 0; 

		int n = prices.size(); 
		vector<int> g(n, 0); 
		int m = INT_MIN; 
		for (int i = 1; i < n; ++i){
			m = max(m, (i - 2 < 0) ? (-prices[i - 1]) : (g[i - 2] - prices[i - 1])); 
			g[i] = max(g[i - 1], prices[i] + m - fee); 
		}

		return g.back(); 
	}
};





int main(){
	Solution a; 
	Solution2 a2; 

	vector<int> b = { 1, 3, 2, 8, 4, 9 }; 

	cout << a.maxProfit(b, 2)<<endl ; 
	cout << a2.maxProfit(b, 2)<<endl; 

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

