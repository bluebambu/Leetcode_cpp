// _template4.cpp : Defines the entry point for the console application.
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

typedef vector<int> VI; 
typedef vector<VI> VVI; 
typedef pair<int, int> PII; 

VVI dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 

class Solution {
public:
    bool isIsomorphic(string s, string t) {
		if (s.size() != t.size()) return false; 

		unordered_map<char, char> m;
		unordered_map<char, char> r;
		for (int i = 0; i < s.size(); ++i){
			if (m.count(s[i]) && m[s[i]] != t[i])
				return false;
			if (r.count(t[i]) && r[t[i]] != s[i])
				return false; 

			m[s[i]] = t[i]; 
			r[t[i]] = s[i]; 
		}
		return true;
    }
};


class Solution {
public:
	bool isIsomorphic(string s, string t) {
		if (s.size() != t.size())
			return false; 

		unordered_map<char, char> gmap, bmap; 
		for (int i = 0; i < s.size(); ++i){
			char a = s[i], b = t[i]; 
			if (gmap.count(a) && gmap[a] != b)
				return false; 
			if (bmap.count(b) && bmap[b] != a)
				return false; 

			gmap[a] = b; 
			bmap[b] = a; 
		}
		return true; 
	}
};

class Solution2 {
public:
	bool isIsomorphic(string s, string t) {
		unordered_map<char, char> st, ts; 
		if (s.size() != t.size()) return false; 
		for (int i = 0; i < s.size(); ++i){
			char c1 = s[i], c2 = t[i]; 
			if (st.count(c1) && st[c1] != c2)
				return false; 
			if (ts.count(c2) && ts[c2] != c1)
				return false; 
			st[c1] = c2, ts[c2] = c1; 
		}
		return true; 
	}
};


int main(){
	Solution a;

	vector<int> b = { 1, 2, 3, 4, 5 }; 



	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6,
		new TreeNode(3, new TreeNode(1),
						new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
						new TreeNode(9,
		                               new TreeNode(10),
		                               nullptr)));
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

