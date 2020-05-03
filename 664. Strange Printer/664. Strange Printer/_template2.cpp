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
//  There is a strange printer with the following two special requirements:

//     The printer can only print a sequence of the same character each time.
//     At each turn, the printer can print new characters starting from and ending at any places, and will cover the original existing characters.

// Given a string consists of lower English letters only, your job is to count the minimum number of turns the printer needed in order to print it.

// Example 1:

// Input: "aaabbb"
// Output: 2
// Explanation: Print "aaa" first and then print "bbb".

// Example 2:

// Input: "aba"
// Output: 2
// Explanation: Print "aaa" first and then print "b" from the second place of the string, which will cover the existing character 'a'.

// Hint: Length of the given string will not exceed 100.


class Solution {
public:
	int strangePrinter(string s) {
		unordered_map<string, int> m; 
		return helper(s, m); 
	}
	int helper(string s, unordered_map<string, int>& m) {
		if (s.empty())
			return 0; 
		if (s.size() == 1)
			return 1; 
		if (m.count(s))
			return m[s]; 

		int res = INT_MAX; 
		int last = s.size() - 1; 
		for (int i=s.size()-2; i >= 0; --i){
			if (s[i] == s[last]){
				string right = s.substr(i + 1, last - i - 1); 
				string left = s.substr(0, i + 1); 
				res = min(res, helper(right, m) + helper(left, m)); 
			}
		}

		res = min(res, 1 + helper(s.substr(0, s.size() - 1), m)); 
		m[s] = res; 
		return res; 
	}
};



int main(){
	Solution a; 
	cout << a.strangePrinter("aabbaaababb"); 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


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

