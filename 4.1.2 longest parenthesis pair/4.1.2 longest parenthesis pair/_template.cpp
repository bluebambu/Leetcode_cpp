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
	int LongestParen(string s){
		vector<int> dp(s.size(), 0); 
		int res = 0;

		for (int i = 0; i < s.size(); ++i){
			if (s[i] == '(')
				continue;; 
			if (i - 1 >= 0 && i - dp[i - 1] - 1 >=0 &&  s[i - dp[i - 1] - 1] == '('){
				dp[i] = dp[i - 1] + 2;
				if (i - dp[i] >= 0)
					dp[i] += dp[i - dp[i]]; 
			}
			res = max(res, dp[i]); 
		}

		return res;
	}

};

int main()
{
	Solution a;

	cout << a.LongestParen("()()))(((()))())()"); 


}

