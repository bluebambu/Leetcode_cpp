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
#include <numeric>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a < b ? a : b; }


struct TreeNode {
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

// pass
int M = 1e9 + 7; 
class Solution {
public:
	int distinctSubseqII(string S) {
		int n = S.size(); 
		vector<int> dp(n, 1); 
		for (int i = 1; i < n; ++i){
			char c = S[i]; 
			for (int j = i - 1; j >= 0; --j){
				if (S[j] != c){
					dp[i] = (dp[i] + dp[j]) % M;
				}
				else{
					dp[i] -= 1; 
					dp[i] = (dp[i] + dp[j]) % M;
					break;
				}
			}
		}

		prt1Layer(dp); 
		int res = 0; 
		for (int i : dp)
			res = (res + i) % M; 
		return res; 
	}
};


class Solution2{
public:
	int distinctSubseqII(string S) {
		int n = S.size(); 
		vector<int> dp(n, 1); 
		for (int i = 1; i < n; ++i){
			char c = S[i]; 
			for (int j = 0; j < i; ++j){
				if (S[j] != c){
					dp[i] = (dp[i] + dp[j]) % M; 
				}
			}
		}
		int res = 0; 
		for (int i : dp)
			res = (res + i) % M; 
		return res; 
	}
};


class Solution3{
public:
	int distinctSubseqII(string S) {
		vector<int> dp(26, 0); 
		for (auto c : S){
			dp[c - 'a'] = (accumulate(dp.begin(), dp.end(), 0L) + 1) % M;
		}
		return (accumulate(dp.begin(), dp.end(), 0L)) % M; 
	}
}; 


int main(){
	Solution2 a;

	string s = "abc"; 
	string s2 = "abcc"; 
	string s3 = "aaa"; 
	string s4 = "aba"; 
	string s5 = "zchmliaqdgvwncfatcfivphddpzjkgyygueikthqzyeeiebczqbqhdytkoawkehkbizdmcnilcjjlpoeoqqoqpswtqdpvszfaksn"; 

	cout << a.distinctSubseqII(s) << endl; 
	cout << a.distinctSubseqII(s2) << endl; 
	cout << a.distinctSubseqII(s3) << endl; 
	cout << a.distinctSubseqII(s4) << endl; 
	cout << a.distinctSubseqII(s5) << endl; 

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

