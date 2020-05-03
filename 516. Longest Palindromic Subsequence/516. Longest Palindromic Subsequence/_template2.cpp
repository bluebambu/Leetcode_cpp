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
// Given a string s, find the longest palindromic subsequence's length in s. You may assume that the maximum length of s is 1000. 
// Example 1:
// Input: 
// "bbbab"
// Output: 
// 4
// One possible longest palindromic subsequence is "bbbb". 

// Example 2:
// Input: 
// "cbbd"
// Output: 
// 2
// One possible longest palindromic subsequence is "bb". 


// can do the work, but memory limit reached......
class Solution {
public:
	int longestPalindromeSubseq(string s) {
		// local[i][j]  = s[i]==s[j] ? global[i+1][j-1]+1 : 0; 
		// global[i][j]	= local[i][j] ? local[i][j] : max(global[i-1][j], global[i][j-1])
		// so first loop J, second loop I

		int n = s.size(); 
		vector<vector<int>> local(n + 1, vector<int>(n + 1, 0));
		vector<vector<int>> global = local; 

		for (int j = 1; j <= n; ++j){
			for (int i = j; i >=1; --i){
				if (i == j){
					local[i][j] = 1; 
					global[i][j] = 1; 
					continue;
				}
				if (i == j - 1){
					local[i][j] = s[i - 1] == s[j - 1] ? 2 : 0;
					global[i][j] = s[i - 1] == s[j - 1] ? 2 : 1;
					continue;
				}
				local[i][j] = s[i - 1] == s[j - 1] ? global[i + 1][j - 1] + 2 : 0;
				global[i][j] = local[i][j] ? local[i][j] : max(global[i + 1][j], global[i][j - 1]);
				// from global[i][j] we can see clearly, local[n][n] is redundant. 
			}
		}

		prt2Layer(local); 
		cout << endl << endl;
		prt2Layer(global); 
		cout << endl << endl;

		return global[1][n]; 
	}
};



// still memory limit reached. 
class Solution2 {
public:
	int longestPalindromeSubseq(string s) {

		int n = s.size();
		vector<vector<int>> local(n + 1, vector<int>(n + 1, 0));
		vector<vector<int>> global = local;

		for (int j = 1; j <= n; ++j){
			for (int i = j; i >= 1; --i){
				if (i == j){
					global[i][j] = 1; 
					continue;
				}
				if (i == j - 1){
					global[i][j] = s[i - 1] == s[j - 1] ? 2 : 1;
					continue;
				}

				global[i][j] = s[i - 1] == s[j - 1] ? global[i + 1][j - 1] + 2 : max(global[i + 1][j], global[i][j - 1]); 
			}
		}

		return global[1][n]; 
	}
};


// passed !!!!
class Solution3 {
public:
	int longestPalindromeSubseq(string s) {

		int n = s.size();
		vector<int> global(n + 1, 0);
		vector<int> prev(n + 1, 0);

		for (int j = 1; j <= n; ++j){
			for (int i = j; i >= 1; --i){
				if (i == j){
					global[i] = 1;
					continue;
				}
				if (i == j - 1){
					global[i] = s[i - 1] == s[j - 1] ? 2 : 1;
					continue;
				}

				global[i] = s[i - 1] == s[j - 1] ? prev[i + 1] + 2 : max(global[i + 1], prev[i]);
			}
			prev = global; 
		}

		return global[1]; 
	}
}; 


class Solution4{
public:
	int longestPalindromeSubseq(string s){
		int n = s.size(); 
		vector<int> cur(n, 0), pre; 
		for (int i = n - 1; i >= 0; --i){
			pre = cur; 
			for (int j = i; j < n; ++j){
				if (i == j)
					cur[j] = 1;
				else if (s[i] == s[j])
					cur[j] = 2 + pre[j - 1];
				else
					cur[j] = max(pre[j], cur[j - 1]); 
			}
		}
		return cur.back(); 
	}
};

int main(){
	Solution4 a;

	vector<int> b = { 7, 2, 5, 10, INT_MAX };

	cout << a.longestPalindromeSubseq("xaybuibcca");

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

