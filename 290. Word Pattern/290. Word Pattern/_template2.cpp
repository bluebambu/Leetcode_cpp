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
// Given a pattern and a string str, find if str follows the same pattern.

// Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str.

// Examples:

//     pattern = "abba", str = "dog cat cat dog" should return true.
//     pattern = "abba", str = "dog cat cat fish" should return false.
//     pattern = "aaaa", str = "dog cat cat dog" should return false.
//     pattern = "abba", str = "dog dog dog dog" should return false.

// Notes:
// You may assume pattern contains only lowercase letters, and str contains lowercase letters separated by a single space. 

// wrong answer
class Solution {
public:
	bool wordPattern(string pattern, string str) {
		vector<string> dict(256, ""); 
		str = " " + str; 

		int j = 0; 
		for (int i = 0; i < pattern.size(); ++i){
			char p = pattern[i]; 
			
			int jj = j+1; 
			if (jj == str.size())
				return false; 
			while (jj < str.size() && str[jj] != ' ') ++jj; 

			string cur = str.substr(j, jj - j); 
			
			if (dict[p] == "")
				dict[p] = cur; 
			else if (dict[p] == cur)
				;
			else
				return false; 

			j = jj; 
		}
		return true; 
	}
};


class Solution2 {
public:
	bool wordPattern(string pattern, string str) {
		str = " " + str; 
		int pi = -1; 
		unordered_map<string, char> m1; 
		unordered_map<char, string> m2; 

		for (int i = 0; i < str.size(); ++i){
			int j = i + 1; 
			while (j < str.size() && str[j] != ' ') ++j;

			string cur = str.substr(i, j - i); 
			
			if (pi == pattern.size() - 1)
				return false;
			char pch = pattern[++pi]; 

			if (m1.count(cur) == 0 && m2.count(pch) == 0){
				m1[cur] = pch, m2[pch] = cur; 
			}
			else if (m1.count(cur) == 0 || m2.count(pch) == 0){
				return false; 
			}
			else{
				if (m1[cur] != pch || m2[pch] != cur)
					return false;
			}

			i = j - 1; 
		}
		return pi==pattern.size()-1; 
	}
};





int main(){
	Solution2 a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	cout << a.wordPattern("abba", "dog cat cat fish"); 
	cout << a.wordPattern("abba", "dog cat cat dog"); 


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

