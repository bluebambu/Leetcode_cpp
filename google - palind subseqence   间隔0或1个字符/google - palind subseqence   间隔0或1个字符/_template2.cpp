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

struct unit{
	int len; 
	string str; 
	unit(int x, string y) :len(x), str(y) {}
};

class PalinSeq{
public:
	vector<string> solve(string s){
		vector<string> res;
		if (s.empty())
			return res;

		int n = s.size();
		struct unit{
			int len;
			string str;
			unit(int x, string y) :len(x), str(y) {}
		};
		vector<vector<unit>> dp(n);
		dp[0].push_back(unit(1, string() + s[0]));
		for (auto x : dp[0]){
			res.push_back(x.str);
		}

		for (int i = 1; i < n; ++i){
			if (dp[i - 1].size()){
				vector<unit>& pre = dp[i - 1];
				for (unit& u : pre){
					int len = u.len;
					string ss = u.str;
					string potential = string() + s[i] + ss + s[i];
					if (i - len - 1 >= 0 && s[i - len - 1] == s[i]){
						dp[i].push_back(unit(len + 2, potential));
					}
					if (i - len - 2 >= 0 && s[i - len - 2] == s[i]){
						dp[i].push_back(unit(len + 3, potential));
					}
				}
			}
			if (i - 2 >= 0 && dp[i - 2].size()){
				vector<unit>& ppre = dp[i - 2];
				for (unit& u : ppre){
					int len = u.len;
					string ss = u.str;
					string potential = string() + s[i] + ss + s[i];
					if (i - len - 2 >= 0 && s[i - len - 2] == s[i]){
						dp[i].push_back(unit(len + 3, potential));
					}
					if (i - len - 3 >= 0 && s[i - len - 3] == s[i]){
						dp[i].push_back(unit(len + 4, potential));
					}
				}
			}

			dp[i].push_back(unit(1, string() + s[i]));

			for (auto x : dp[i]){
				res.push_back(x.str);
			}
		}

		return res;
	}
};



int main() {

	PalinSeq a;
	string z = "zaxbayzz";

	auto x = a.solve(z);

	prt1Layer(x);

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

