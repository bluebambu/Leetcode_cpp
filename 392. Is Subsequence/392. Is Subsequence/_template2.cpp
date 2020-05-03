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
// Given a string s and a string t, check if s is subsequence of t. 
// You may assume that there is only lower case English letters in both s and t. t is potentially a very long (length ~= 500,000) string, and s is a short string (<=100). 
// A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ace" is a subsequence of "abcde" while "aec" is not). 
// Example 1:
// s = "abc", t = "ahbgdc" 
// Return true. 
// Example 2:
// s = "axc", t = "ahbgdc" 
// Return false. 
// Follow up:
// If there are lots of incoming S, say S1, S2, ... , Sk where k >= 1B, and you want to check one by one to see if T has its subsequence. In this scenario, how would you change your code?


// memory limited
class Solution {
public:
	bool isSubsequence(string s, string t) {
		// dp[ti][si] = t[i]==s[i] ? dp[ti-1][si-1] : dp[ti-1][si]; 
		// outer si loop, inner ti loop. 

		int n = t.size(), m = s.size(); 
		vector<vector<bool>> dp(n+1, vector<bool>(m+1, false)); 
		for (int i = 0; i < n + 1; ++i)
			dp[i][0] = true; 

		for (int j = 1; j < m + 1; ++j){
			for (int i = j; i < n+1; ++i){
				dp[i][j] = t[i - 1] == s[j - 1] ? dp[i - 1][j - 1] : dp[i - 1][j]; 
			}
		}

		prt2Layer(dp); 

		return dp[n][m]; 
	}
};


//
class Solution2 {
public:
	bool isSubsequence(string s, string t) {
		// dp[ti][si] = t[i]==s[i] ? dp[ti-1][si-1] : dp[ti-1][si]; 
		// outer si loop, inner ti loop. 

		if (s.empty()) // in this solution, this statement is necessary!!!
			return true; 

		int n = t.size(), m = s.size();
		vector<bool> dp(n + 1, false); 
		vector<bool> prev(n + 1, true); 

		for (int j = 1; j < m + 1; ++j){
			//in this solution, this statement is necessary!!!
			// because dp[i] ( i<j) should be 0, but in prev iteration, they were modified to TRUE. 
			dp = vector<bool>(n + 1, false); 

			for (int i = j; i < n + 1; ++i){
				dp[i] = t[i - 1] == s[j - 1] ? prev[i - 1] : dp[i - 1]; 
			}

			prev = dp; 
		}

		return dp[n]; 
	}
};


// But actually, it does not need to use DP at all!!!!!! faint.....
class Solution3 {
public:
	bool isSubsequence(string s, string t) {
		if (s.empty())
			return true; 

		int i = 0, j = 0; 
		while (j < t.size()){
			if (s[i] == t[j])
				++i, ++j;
			else
				++j;
		}
		return i == s.size(); 
	}
};

// Follow up:
// If there are lots of incoming S, say S1, S2, ..., Sk where k >= 1B, and 
// you want to check one by one to see if T has its subsequence.In this scenario, how would you change your code ?

class Solution4 {
public:
	bool isSubsequence(string s, string t) {
		int i = 0, j = 0; 
		while (j < t.size() && i<s.size()){
			if (s[i] == t[j])
				++i, ++j;
			else
				++j; 
		}
		return j <= t.size() && i==s.size(); 
	}
};




int main(){
	Solution a;
	Solution2 a2;
	Solution4 a3;

	vector<int> b = { 7, 2, 5, 10, INT_MAX };


	cout<<a.isSubsequence("axc", "ahbgdc")<<endl;
	cout<<a2.isSubsequence("axc", "ahbgdc")<<endl;
	cout<<a3.isSubsequence("axc", "ahbgdc")<<endl;

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

