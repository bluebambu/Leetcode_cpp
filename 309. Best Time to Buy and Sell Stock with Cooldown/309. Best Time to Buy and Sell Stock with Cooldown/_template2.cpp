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
// Design an algorithm to find the maximum profit.You may complete as many transactions as you like(ie, buy one and sell one share of the stock multiple times) with the following restrictions :
// You may not engage in multiple transactions at the same time(ie, you must sell the stock before you buy again).
// After you sell your stock, you cannot buy stock on next day. (ie, cooldown 1 day)
// Example :
// 		prices = [1, 2, 3, 0, 2]
// 		maxProfit = 3
// 		transactions = [buy, sell, cooldown, buy, sell]


class Solution {
public:
	int maxProfit(vector<int>& prices) {
		int n = prices.size();
		if (prices.size() < 2)
			return 0;

		vector<int> buy(n, 0), sell(n, 0);
		buy[0] = -prices[0];
		buy[1] = -(min(prices[0], prices[1]));
		sell[1] = prices[1] > prices[0] ? prices[1] - prices[0] : 0;

		for (int i = 2; i < n; ++i){
			buy[i] = max(buy[i - 1], sell[i - 2] - prices[i]);
			sell[i] = max(sell[i - 1], buy[i - 1] + prices[i]);
		}
		return sell[n - 1];
	}
};


// passAC, O(1) space!
class Solution2 {
public:
	int maxProfit(vector<int>& prices) {
		int n = prices.size(); 
		if (prices.size() < 2)
			return 0; 

		int pre_buy = -prices[0], buy = -min(prices[0], prices[1]); 
		int pre_sell = 0, sell = prices[1] > prices[0] ? prices[1] - prices[0] : 0, prepre_sell=0; 

		for (int i = 2; i < n; ++i){
			prepre_sell = pre_sell; 
			pre_sell = sell; 
			sell = max(sell, buy + prices[i]); 
			buy = max(buy, prepre_sell - prices[i]); 
		}

		return sell; 
	}
};

// wrong solution
class Solution3 {
public:
	int maxProfit(vector<int>& prices) {
		int n = prices.size(); 
		vector<int> g(n + 1, 0); 

		int m = INT_MIN; 
		for (int i = 1; i <= n; ++i){ // 
			m = max(m, g[i - 2] - prices[i-1]); 
			g[i] = max(g[i - 1], prices[i-1] + m); 
		}
		return g.back(); 
	}
}; 


class Solution4 {
public:
	int maxProfit(vector<int>& prices) {
		if (prices.empty())
			return 0; 

		int n = prices.size(); 
		vector<int> g(n, 0); 
		g[0] = 0; 

		int m = INT_MIN; 
		for (int i = 1; i < n; ++i){
			m = max(m, (i < 3) ? (-prices[i - 1]) : (g[i - 3] - prices[i - 1])); 
			g[i] = max(g[i - 1], m + prices[i]);
		}

		return g.back(); 
	}
}; 


int main(){
	Solution2 a;
	Solution4 a2;

	vector<int> b = { 2, 1, 4 };
	vector<int> b2 = { 1, 2, 3, 0, 2 }; 
	vector<int> b3 = { 1, 0, 3, 2, 4 };

	cout << a.maxProfit(b2) << endl; 
	cout << a2.maxProfit(b2) << endl; 


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

