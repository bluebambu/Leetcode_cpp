// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <functional>
#include <bitset>
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

class Solution {
public:
	bool canSubstitute(string a, string b){
		if (a.size() != b.size())
			return false;

		unordered_map<char, unordered_set<char>> g;
		unordered_map<char, int> status;
		int n = a.size();
		for (int i = 0; i < n; ++i){
			if (g[a[i]].size()>0 && !g[a[i]].count(b[i]))
				return false;
			g[a[i]].insert(b[i]);
		}

		for (auto p : a){
			char c = p;
			if (!dfs(c, g, status))
				return false;
		}

		return true;
	}

	bool dfs(char c, unordered_map<char, unordered_set<char>>& g, unordered_map<char, int>& status){
		if (status[c] == 1)
			return true;
		if (status[c] == -1)
			return false;

		status[c] = -1;
		for (auto j : g[c]){
			if (j != c && !dfs(j, g, status))
				return false;
		}
		status[c] = 1;
		return true;
	}
};
int main() {

	vector<pair<int, int>> b = { { 1, 0 }, { 1, 2 }, { 1, 3 } };
	vector<pair<int, int>> c = { { 0, 3 }, { 1, 3 }, { 2, 3 }, { 4, 3 }, { 5, 4 } };

	vector<vector<int>> d = {
		{ INT_MAX, -1, 0, INT_MAX },
		{ INT_MAX, INT_MAX, INT_MAX, -1 },
		{ INT_MAX, -1, INT_MAX, -1 },
		{ 0, -1, INT_MAX, INT_MAX },
	};

	Solution a;

	cout << a.canSubstitute("aaabcddef", "bbbcdddef") << endl;
	cout << a.canSubstitute("aaabcdde", "bbbcdeea") << endl;

}

