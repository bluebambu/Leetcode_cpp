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

vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 


class Solution {
public:
	bool isInterleave(string s1, string s2, string s3) {
		// 1-based:  [i,j] = s3[i+j]==s1[i]==s2[j]  -> [i-1, j] || [i, j-1]
		// dp[0][0] = true; 
		//
		// 1D:  dp[0] =  true; 
		int n = s1.size(), m = s2.size(); 
		if (n + m != s3.size())
			return false; 

		vector<bool> dp(m + 1, false); 
		dp[0] = true; 
		for (int i = 1; i <= m; ++i){
			dp[i] = (s2[i - 1] == s3[i - 1]) && dp[i - 1];
		}

		prt1Layer(dp); 

		for (int i = 1; i <= n; ++i){
			dp[0] = (s1[i - 1] == s3[i - 1]) && dp[0];
			for (int j = 1; j <= m; ++j){
				if (s3[i + j - 1] == s1[i - 1] && s3[i + j - 1] == s2[j - 1])
					dp[j] = (dp[j - 1] || dp[j]);
				else if (s3[i + j - 1] == s1[i - 1])
					dp[j] = dp[j];
				else if (s3[i + j - 1] == s2[j - 1])
					dp[j] = dp[j - 1];
				else
					dp[j] = false; 
			}
		prt1Layer(dp); 
		}

		return dp.back(); 
	}
};


int main(){
	Solution a;

	//string s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac", s4 = "aadbbbaccc"; 

	string s1 = "db", s2 = "b", s3 = "cbb", s4 = "aadbbbaccc"; 
	cout << a.isInterleave(s1, s2, s3) << endl; 
	cout << a.isInterleave(s1, s2, s4) << endl; 

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

