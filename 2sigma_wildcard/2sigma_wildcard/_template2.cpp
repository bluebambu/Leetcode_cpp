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

class Solution {
public:
	static bool match2(const string& a, const string& b){
		if (a.empty() && b.empty())
			return true; 
		if (a.empty() && !b.empty()){
			for (char i : b)
				if (i != '*')
					return false; 
			return true; 
		}
		if (b.empty())
			return false; 

		int alen = a.size(), blen = b.size(); 

		if (b.back() == '*')
			return match(a.substr(0, alen - 1), b) || match(a, b.substr(0, blen - 1));
		else if (b.back() == '?')
			return match(a.substr(0, alen - 1), b.substr(0, blen - 1));
		else
			return match(a.substr(0, alen - 1), b.substr(0, blen - 1)) && (a.back() == b.back()); 
	}

	static bool match3(const string& a, const string& b){
		return helper(a, a.size(), b, b.size());
	}
	static bool helper(string a, int ai, string b, int bi){
		if (ai == 0 && bi == 0)
			return true; 
		if (ai == 0 && bi != 0){
			for (int i = 0; i < bi; ++i)
				if (b[i] != '*')
					return false; 
			return true; 
		}
		if (bi == 0)
			return false; 

		if (b[bi - 1] == '*')
			return helper(a, ai, b, bi - 1) || helper(a, ai - 1, b, bi);
		else if (b[bi - 1] == '?')
			return helper(a, ai - 1, b, bi - 1); 
		else
			return (a[ai - 1] == b[bi-1]) && helper(a, ai - 1, b, bi - 1); 
	}

	static bool match4(const string& a, const string& b){
		// matrix[alen][blen]  
		if (a.empty() && b.empty())
			return true; 
		if (a.empty() && !b.empty()){
			for (char i : b)
				if (i != '*')
					return false; 
			return true; 
		}
		if (b.empty())
			return false; 

		int alen = a.size(), blen = b.size(); 
		vector<vector<bool>> mtrx(alen+1, vector<bool>(blen+1, false)); 

		mtrx[0][0] = true; 
		mtrx[1][0] = false; 
		mtrx[0][1] = (b[0]=='*'); 

		for (int i = 1; i < alen + 1; ++i)
			mtrx[i][0] = false; 
		for (int j = 1; j < blen + 1; ++j)
			mtrx[0][j] = (b[j-1] == '*') && mtrx[0][j - 1]; 

		for (int i = 1; i < alen + 1; ++i){
			for (int j = 1; j < blen + 1; ++j){
				if (b[j - 1] == '*')
					mtrx[i][j] = mtrx[i - 1][j] || mtrx[i][j - 1]; 
				else if (b[j - 1] == '?')
					mtrx[i][j] = mtrx[i - 1][j - 1];
				else
					mtrx[i][j] = (a[i - 1] == b[j - 1]) && mtrx[i - 1][j - 1]; 
			}
		}
		
		return mtrx[alen][blen]; 
	}

	static bool match(const string& a, const string& b){
		// matrix[alen][blen]  
		// 1D dp vector solution
		if (a.empty() && b.empty())
			return true; 
		if (a.empty() && !b.empty()){
			for (char i : b)
				if (i != '*')
					return false; 
			return true; 
		}
		if (b.empty())
			return false; 

		int alen = a.size(), blen = b.size(); 
		vector<bool> dp(blen + 1, false); 
		dp[0] = true; 

		for (int i = 1; i < blen + 1; ++i)
			dp[i] = (b[i - 1] == '*') && dp[i - 1]; 

		bool prev = true;
		for (int j = 1; j < alen + 1; ++j){
			for (int i = 1; i < blen + 1; ++i){
				if (b[i - 1] == '*'){
					prev = dp[i]; 
					dp[i] = dp[i] || dp[i - 1]; 
				}
				else if (b[i - 1] == '?'){
					bool tmp = prev; 
					prev = dp[i]; 
					dp[i] = tmp; 
				}
				else{
					bool tmp = prev; 
					prev = dp[i]; 
					dp[i] = tmp && (a[j - 1] == b[i - 1]); 
				}
			}
		}

		return dp.back(); 
	}
};




// int main(){
// 	Solution a; 

// 	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


// 	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
// 	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
// 		new TreeNode(4)),
// 		new TreeNode(8, new TreeNode(7),
// 		new TreeNode(9)));
// 	/*      6
// 		3       8
// 	1    4   7    9
// 	*/



// 	///////////////////////////
// 	auto start = std::chrono::high_resolution_clock::now();
// 	auto elapsed = std::chrono::high_resolution_clock::now() - start;
// 	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
// 	cout << endl << microseconds << " microseconds elapsed..." << endl;
// }

