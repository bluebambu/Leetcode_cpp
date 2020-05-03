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
#include <string>
#include <cmath>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }


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
		for (int i = 0; i<n; ++i){
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


class Solution {
public:
	bool isOneEditDistance(string s1, string t1) {
		if (s1.empty() && t1.empty())
			return false;
		if (s1.empty() || t1.empty())
			return s1.empty() ? t1.size() == 1 : s1.size() == 1;
		if (s1.size() > t1.size())
			return isOneEditDistance(t1, s1);
		if ((t1.size() - s1.size()) > 1)
			return false;

		int n1 = 0, n2 = 0;
		while (n1 < s1.size() || n2 < t1.size()){
			if (s1[n1] == t1[n2])
				++n1, ++n2;
			else{
				if (s1.substr(n1, s1.size() - n1) == t1.substr(n2 + 1, t1.size() - (n2 + 1))
					|| s1.substr(n1 + 1, s1.size() - (n1 + 1)) == t1.substr(n2 + 1, t1.size() - (n2 + 1)))
					return true;
				else
					return false;
			}
		}
		return false;
	}

};

class Solution2 {
public:
	bool isOneEditDistance(string s1, string t1) {
		if (s1.size() > t1.size())
			return isOneEditDistance(t1, s1);

		return check(s1, s1.size() - 1, t1, t1.size() - 1, 1);
	}
	unordered_map<int, unordered_map<int, bool>> m; 
	bool check(string& s1, int si, string& t1, int ti, int rem){
		if (m.count(si) && m[si].count(ti)) return m[si][ti]; 
		if (si == -1)
			return rem == ti + 1;
		if (ti == -1)
			return rem == si + 1;

		if (!rem)
			return s1.substr(0, si + 1) == t1.substr(0, ti + 1);

		if (s1[si] == t1[ti])
			return check(s1, si - 1, t1, ti - 1, rem);

		m[si][ti] = check(s1, si, t1, ti - 1, rem - 1) || check(s1, si - 1, t1, ti - 1, rem - 1);
		return m[si][ti]; 
	}

};

class Solution3 {
public:
	bool isOneEditDistance(string s1, string t1) {
		int i = 0, j = 0; 
		while (i < s1.size() && j < t1.size()){
			if (s1[i] == t1[j]) ++i, ++j; 
			else
			return s1.substr(i + 1) == t1.substr(j + 1) ||
				s1.substr(i) == t1.substr(j + 1) ||
				s1.substr(i + 1) == t1.substr(j); 
		}
		if (i == s1.size()) return j == t1.size() - 1; 
		if (j == t1.size()) return i == s1.size() - 1; 
	}
}; 


class Solution4 {
public:
	bool isOneEditDistance(string s1, string t1) {
		if (abs(s1.size() - t1.size()) > 1) return false; 
		int i = 0; 
		for (; i < s1.size() && i < t1.size(); ++i)
			if (s1[i] != t1[i])
				break; 

		if (i == s1.size()) return t1.size() == s1.size() + 1; 
		if (i == t1.size()) return s1.size() == t1.size() + 1; 

		return (s1.substr(i) == t1.substr(i + 1)) ||
			(s1.substr(i + 1) == t1.substr(i)) ||
			(s1.substr(i + 1) == t1.substr(i + 1)); 
	}
};


int main() {
	Solution b;
	Solution3 b2;

	cout << b.isOneEditDistance("a", "ac") << endl; 
	cout << b2.isOneEditDistance("a", "ac") << endl;

	cout << b.isOneEditDistance("abc", "ac") << endl; 
	cout << b2.isOneEditDistance("abc", "ac") << endl;

	cout << b.isOneEditDistance("a", "") << endl; 
	cout << b2.isOneEditDistance("a", "") << endl;
}

