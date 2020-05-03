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
// Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively. 
// Below is one possible representation of s1 = "great": 
//     great
//    /    \
//   gr    eat
//  / \    /  \
// g   r  e   at
//            / \
//           a   t
// To scramble the string, we may choose any non-leaf node and swap its two children. 
// For example, if we choose the node "gr" and swap its two children, it produces a scrambled string "rgeat". 
//     rgeat
//    /    \
//   rg    eat
//  / \    /  \
// r   g  e   at
//            / \
//           a   t
// We say that "rgeat" is a scrambled string of "great". 
// Similarly, if we continue to swap the children of nodes "eat" and "at", it produces a scrambled string "rgtae". 
//     rgtae
//    /    \
//   rg    tae
//  / \    /  \
// r   g  ta  e
//        / \
//       t   a
// We say that "rgtae" is a scrambled string of "great". 
// Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1. 



// recursion + memorization
// works, but TLE
class Solution {
public:
	bool isScramble(string s1, string s2) {
		if (s1.size() != s2.size())
			return false; 
		if (s1.empty() && s2.empty())
			return true; 
		if (s1.empty() || s2.empty())
			return false; 
		if (s1.size() == 1)
			return s1 == s2;

		int n = s1.size(); 
		vector<vector<vector<bool>>> m(n, vector<vector<bool>>(n, vector<bool>(n, 0))); 
		bool res = false; 
		for (int i = 1; i < s1.size(); ++i){
			res |= helper(s1, s2, 0, 0, i, m) && helper(s1, s2, i, i, n-i, m); 
			if (!res) // if no this statement, the time is much much longer!!!!!
				res |= helper(s1, s2, i, 0, n - i, m) && helper(s1, s2, 0, n - i, i, m);
		}
		return res; 
	}

	bool helper(string& s, string& t, int si, int ti, int len, vector<vector<vector<bool>>>& m){
		if (len == 0)
			return true; 
		if (len == 1)
			return s[si] == t[ti]; 
		if (m[si][ti][len])
			return m[si][ti][len];

		bool res = false; 
		for (int i = 1; i<len; ++i){
			res |= helper(s, t, si, ti, i, m) && helper(s, t, si + i, ti + i, len - i, m);
			if (!res) // if no this statement, the time is much much longer!!!!!
				res |= helper(s, t, si, ti + len - i, i, m) && helper(s, t, si + i, ti, len - i, m);
		}
		m[si][ti][len] = res; 
		return res; 
	}
};


// surprisingly, this is much faster than above........ 
// passed.... 
class Solution2 {
public:
	bool isScramble(string s1, string s2) {
		if (s1.size() != s2.size())
			return false;
		if (s1.empty() && s2.empty())
			return true;
		if (s1.empty() || s2.empty())
			return false;
		if (s1.size() == 1)
			return s1 == s2;

		unordered_map<string, unordered_map<string, bool>> m; 
		return helper(s1, s2, m); 

	}

	bool helper(string s, string t, unordered_map<string, unordered_map<string, bool>>& m ){
		if (s.size() == 1)
			return s == t; 
		if (m.count(s) && m[s].count(t))
			return m[s][t]; 

		int n = s.size(); 
		bool res = false; 
		for (int i = 1; i < s.size(); ++i){
			res |= helper(s.substr(0, i), t.substr(0, i), m) && helper(s.substr(i), t.substr(i), m); 
			res |= helper(s.substr(0, i), t.substr(n - i), m) && helper(s.substr(i), t.substr(0, n-i), m); 
		}
		m[s][t] = res; 
		return res; 
	}
};



int main(){
	Solution a;

	vector<int> b = { 7, 2, 5, 10, INT_MAX };
	
	cout << a.isScramble("rg", "gr"); 
		

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

	cout << a.isScramble("bbbbabccccbbbabcba", "bbbbabccccbbbabcba");

	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds/1000000 << " seconds elapsed..." << endl;
}

