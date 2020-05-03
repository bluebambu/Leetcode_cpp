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


class Solution
{
public:
	bool isMatch(string a, string b){
		return rec(a, a.size() - 1, b, b.size() - 1);
	}

	bool rec(string& a, int ia, string& b, int ib){
		if (ia == -1 && ib == -1)
			return true;
		if (ia == -1){
			if (b[ib] == '*'){
				return rec(a, ia, b, ib - 2);  // for cases :   [], [c*c*]
			}
			return false;
		}
		if (ib == -1)
			return rec(b, ib, a, ia);


		if (a[ia] != '*' && b[ib] != '*')
			return (a[ia] == '.' || b[ib] == '.' || a[ia] == b[ib]) && rec(a, ia - 1, b, ib - 1);


		if (a[ia] == '*' && b[ib] == '*'){
			if (a[ia - 1] == b[ib - 1])
				return rec(a, ia - 2, b, ib - 2);
			else
				return rec(a, ia, b, ib - 2) || rec(a, ia - 2, b, ib);
		}


		if (a[ia] == '*')
			return rec(b, ib, a, ia);

		//if (b[ib] == '*'){
		char rep = b[ib - 1];

		if (rep != '.'){
			bool tmp = false;
			for (; ia >= -1 && a[ia] == rep; --ia){  // for case: [aaa], [a*b*a*], you cannot simply skip all 'a', you have to check position one by one. 
				tmp |= rec(a, ia, b, ib - 2);
				if (tmp)
					return true;
			}
			return rec(a, ia, b, ib - 2);
		}
		else{
			bool tmp = false;
			for (; ia >= -1; --ia){		// for case: [aaa], [.*]. Here [.*] means [....] which can mean any equivalently long strings. 
				tmp |= rec(a, ia, b, ib - 2);
				if (tmp)
					return true;
			}
			return false;
		}
	//	}
	}
};

// DP solution, the same as wildcard match
//

class Solution2 {
public:
	bool isMatch(string s, string t){
		int m = s.size(), n = t.size(); 
		vector<vector<bool>> dp(m + 1, vector<bool>(n+1, false)); 

		dp[0][0] = true; 
		for (int j = 1; j < n + 1; ++j){
			if (j % 2 == 0 && t[j-1] == '*')
				dp[0][j] = dp[0][j - 2]; 
		}

		for (int i = 1; i < m + 1; ++i){
			for (int j = 1; j < n + 1; ++j){
				if (t[j - 1] == '*'){
					if (dp[i][j - 2])
						dp[i][j] = true;
					else if (dp[i - 1][j] && ((s[i - 1] == t[j - 2]) || (t[j - 2] == '.'))) // 要考虑 "a", ".*" 的case。 此处 t[j-2]=='.' 不可少。 注意是t-2, 不是 t-1 
						dp[i][j] = true; 
				}
				else if (s[i - 1] == t[j - 1] || t[j - 1] == '.')
					dp[i][j] = dp[i-1][j-1]; 
			}
		}
		return dp[m][n];
	}
};




int main()
{
	Solution2 a;

	cout << a.isMatch("aa", ".*");

}

