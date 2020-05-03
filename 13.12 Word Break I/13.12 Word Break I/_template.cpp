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
#include <unordered_set>

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



// passed leetcode, 
class Solution
{
public:
	bool wordBreak(string s, unordered_set<string>& wordDict) {
		if (s.empty())
			return wordDict.find("") != wordDict.end();

		vector<bool> dp(s.size(), false);

		for (int i = 0; i < s.size(); ++i){
			for (int j = i ; j >= 0; --j){
				dp[i] = dp[i] || ( (wordDict.find(s.substr(j, i - j+1)) != wordDict.end())	&&	(j==0 ? true : dp[j-1]) );
				if (dp[i])
					break;
			}
		}
		return dp.back();
	}

};

int main()
{
	Solution a;

	unordered_set<string> dict{ "leet", "code" }; 
	string b = "leetcode"; 

	cout << a.wordBreak(b, dict); 


}

