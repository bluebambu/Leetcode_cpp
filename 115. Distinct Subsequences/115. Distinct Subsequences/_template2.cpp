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
// Given a string S and a string T, count the number of distinct subsequences of S which equals T.
// A subsequence of a string is a new string which is formed from the original string by deleting some(can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
// Here is an example :
// S = "rabbbit", T = "rabbit"
// Return 3.


// passAC
class Solution {
public:
	int numDistinct(string s, string t) {
		if (s.empty() || t.empty())
			return 0; 

		int m = s.size(), n = t.size(); 
		vector<vector<int>> dp(m+1, vector<int>(n+1, 0)); 

		// this condition is necessary and tricky!!!!
		for (int i = 0; i < m + 1; ++i)
			dp[i][0] = 1;

		// order of i and j can be changed.
		for (int i = 1; i <= m; ++i){
			for (int j = 1; j <= n; ++j){
				if (s[i - 1] != t[j - 1])
					dp[i][j] = dp[i - 1][j];
				else
					dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1]; 
			}
		}

		return dp[m][n];
	}
};


// 2D -> 1D, pass
class Solution2 {
public:
	int numDistinct(string s, string t) {
		if (s.empty() || t.empty())
			return 0; 

		int m = s.size(), n = t.size(); 
		vector<int> dp(n + 1, 0); 
		dp[0] = 1; 

		for (int i = 1; i <= m; ++i){
			for (int j = n; j>0; --j){
				if (s[i - 1] == t[j - 1])
					dp[j] = dp[j] + dp[j - 1]; 
			}
		}
		return dp.back(); 
	}
};

class Solution4 {
public:
    int numDistinct(string s, string t) {
		// dp[i][j]  = s[i]==t[j] -> dp[i-1][j] + dp[i-1][j-1] 
		//			   s[i]!=t[j] -> dp[i-1][j] 
		// dp[0][0] = s[0]==t[0], dp[0][1] = 0; 
		int n = s.size(), m = t.size(); 
		vector<vector<int>> dp(n, vector<int>(m, 0)); 
		dp[0][0] = s[0] == t[0]; 

		for (int i = 1; i < n; ++i){
			dp[i][0] = dp[i - 1][0] + (t[0] == s[i]); 
			for (int j = 1; j < m; ++j){
				dp[i][j] = dp[i - 1][j] + ((s[i] == t[j]) ? (dp[i - 1][j - 1]) : 0 );
			}
		}

		return dp[n - 1][m - 1]; 
    }
};
	
class Solution5 {
public:
	int numDistinct(string s, string t) {
		// dp[i][j]  = s[i]==t[j] -> dp[i-1][j] + dp[i-1][j-1] 
		//			   s[i]!=t[j] -> dp[i-1][j] 
		// dp[0][0] = s[0]==t[0], dp[0][1] = 0; 
		if (s.empty() || t.empty())
			return 0; 

		int n = s.size(), m = t.size();
		vector<int> dp(m, 0); 
		dp[0] = s[0] == t[0]; 

		for (int i = 1; i < n; ++i){
			for (int j = m - 1; j >= 1; --j){
				dp[j] = dp[j] + ((s[i] == t[j]) ? dp[j - 1] : 0); 
			}
			dp[0] = dp[0] + (s[i] == t[0]); 
		}

		return dp.back(); 
	}
};

int main(){
	Solution a;
	Solution5 a2;

	string s = "aabbccc", t = "abce"; 

	cout << a.numDistinct(s, t) << endl; 
	cout << a2.numDistinct(s, t) << endl; 


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

