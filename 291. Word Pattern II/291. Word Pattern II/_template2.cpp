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

// Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty substring in str.

// Examples:
//     pattern = "abab", str = "redblueredblue" should return true.
//     pattern = "aaaa", str = "asdasdasdasd" should return true.
//     pattern = "aabb", str = "xyzabcxzyabc" should return false.

class Solution {
public:
	bool wordPatternMatch(string pattern, string str) {
		unordered_map<string, char> scm; 
		unordered_map<char, string> csm; 

		return dfs(pattern, 0, str, 0, scm, csm);
	}

	bool dfs(string& pattern, int pi, string& str, int si, unordered_map<string, char>& scm, unordered_map<char, string>& csm){
		if (pi == pattern.size() && si == str.size()){
			return true; 
		}
		else if (pi == pattern.size() || si == str.size()){
			return false; 
		}

		bool res = false; 
		
		for (int i = si; i < str.size(); ++i){
			string substr = str.substr(si, i - si + 1); 

			char pch = pattern[pi]; 
			if (scm.count(substr) == 0 && csm.count(pch) == 0){
				scm[substr] = pch, csm[pch] = substr;
				res |= dfs(pattern, pi + 1, str, i + 1, scm, csm); 
				scm.erase(substr), csm.erase(pch); 
			}
			else if (scm.count(substr) == 0 || csm.count(pch) == 0)
				continue;
			else if (scm[substr] != pch || csm[pch] != substr)
				continue;
			else
				res |= dfs(pattern, pi + 1, str, i + 1, scm, csm); 
		}

		return res; 
	}
};


class Solution2 {
public:
	bool wordPattern(string pattern, string str) {
		unordered_map<char, string> m;
		return dfs(pattern, 0, str, 0, m);
	}

	bool dfs(string& pattern, int pi, string tgt, int ti, unordered_map<char, string>& m){
		if (pi == pattern.size() && ti == tgt.size())
			return true;
		else if (pi == pattern.size() || ti == tgt.size())
			return false;

		char curp = pattern[pi];
		if (m.count(curp)){
			string ps = m[curp], cand = tgt.substr(ti, ps.size());
			if (cand != ps)
				return false;
			return dfs(pattern, pi + 1, tgt, ti + ps.size(), m);
		}
		else{
			for (int j = ti + 1; j <= tgt.size(); ++j){
				string cand = tgt.substr(ti, j - ti);
				m[curp] = cand;
				if (dfs(pattern, pi + 1, tgt, j, m))
					return true;
				else{
					m.erase(curp);
				}
			}
			return false;
		}
	}
};


class Solution3 {
public:
	bool wordPattern(string pattern, string str) {
		unordered_map<char, string> dict; 
		return dfs(pattern, 0, str, 0, dict);
	}

	bool dfs(string& pat, int pi, string& ss, int si, unordered_map<char, string>& dict){
		if (pi == pat.size() && si == ss.size())
			return true; 
		if (pi >= pat.size() || si >= ss.size())
			return false; 
		if (pi == pat.size() && si < ss.size())
			return false;

		char c = pat[pi];
		if (dict.count(c)){
			int len = dict[c].size();
			if (ss.substr(si, len) != dict[c])
				return false;
			if (dfs(pat, pi + 1, ss, si + len, dict))
				return true;
			else
				return false;
		}
		else{
			for (int j = si; j < ss.size(); ++j){
				string subss = ss.substr(si, j - si + 1);
				dict[c] = subss;
				if (dfs(pat, pi + 1, ss, j + 1, dict))
					return true;
				else{
					dict.erase(c);
					continue;
				}
			}
		}

		return false; 
	}
}; 


// roughly OK, not check. 
class Solution4 {
public:
	bool wordPattern(string pattern, string str) {
		unordered_map<char, string> m; 
		return dfs(pattern, 0, str, 0, m); 
	}
	bool dfs(string& p, int pi, string& s, int si, unordered_map<char, string>& m){
		if (pi == p.size() && si == s.size())
			return true; 
		if (pi >= p.size() || si >= s.size())
			return false; 

		char c = p[pi]; 
		if (m.count(c)){
			string w = m[c];
			if (s.substr(si, w.size()) == w){
				return dfs(p, pi + 1, s, si + w.size(), m); 
			}
			else
				return false; 
		}
		else{
			for (int sj = si + 1; sj <= s.size(); ++sj){
				string potential = s.substr(si, sj - si); 
				m[c] = potential; 
				if (dfs(p, pi + 1, s, si + potential.size(), m))
					return true; 
				m.erase(c); 
			}
		}

		return false; 
	}
};



int main(){
	Solution a;
	Solution4 a2;

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	cout << a.wordPatternMatch("aba", "aaaaaaaaa")<<endl; 
	cout << a2.wordPattern("aba", "aaaaaaaaa")<<endl;


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

