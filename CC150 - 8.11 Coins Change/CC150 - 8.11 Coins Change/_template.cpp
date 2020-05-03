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

vector<int> coins = { 3, 7, 405, 436 };

class Solution
{
public:
// 	This works, but it's not as optimal as it could be. The issueis that we will be recursively calling makeChange
// 		several times for the same values of amount and index.
//////////////////////根本算不出来，当 vector<int> coins= {3,7,405,436};   int money = 8839; 时， 太多步骤了 /////////////////////////////////////////////////////////////

	int sol(int n){
		return sol(coins, 0, n); 
	}
	int sol(vector<int> coins, int i, int n){
		if (n==0)
			return 1;
		if (i >= coins.size())
			return 0;
		int result = 0;
		for (int j = 0; j <= n / coins[i]; ++j){
			result += sol(coins, i + 1, n - coins[i] * j); 
		}
		return result; 
	}


	///// 貌似 memorization 也算不出来 -_-!!!
	int sol2(const int n){
		sort(coins.begin(), coins.end());
		vector<vector<int>> m(n+1, vector<int>(coins.size(), 0));
		return sol2(coins, 0, n, m);
	}
	int sol2(vector<int> coins, int i, int n, vector<vector<int>>& m){
		if (i >= coins.size())
			return 0;
		if (m[n][i] > 0)
			return m[n][i]; 
		if (n == 0)
			return 1;
		
		int result = 0;
		for (int j = 0; j <= n / coins[i]; ++j){
			result += sol2(coins, i + 1, n - coins[i] * j, m);
		}
		m[n][i] = result; 
		return result;
	}

	// DP   
	// 	dp[coins.size()][money+1] : 
	// 		dp[i][n] =  dp[i - 1][n - 0 * coins[i]]+
	// 					dp[i - 1][n - 1 * coins[i]]+
	//					.....
	int sol3(int n){
		vector<vector<int>> dp();
	}
};

int main()
{
	Solution a;

	cout << a.sol2(8839); 

}

