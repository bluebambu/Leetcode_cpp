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


// wrong ans
class Solution {
public:
	int minDistance(string word1, string word2) {
		int r1 = minDistance2(word1, word2),
			r2 = minDistance2(word2, word1); 
		return min(r1, r2); 
	}
    int minDistance2(string word1, string word2) {
		int i = 0, j = 0; 
		for (; i < word1.size() && j < word2.size();){
			if (word1[i] == word2[j])
				++i, ++j;
			else
				++i; 
		}

		if (j == word2.size())
			return word1.size() - word2.size();
		else
			return word1.size() - j + (word2.size() - j); 
    }
};


class Solution2 {
public:
	int minDistance(string word1, string word2) {
		int n = word1.size(), m = word2.size(); 
		vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0)); 
		for (int i = 1; i <= n; ++i){
			for (int j = 1; j <= m; ++j){
				char c1 = word1[i - 1], c2 = word2[j - 1]; 
				if (c1 == c2)
					dp[i][j] = dp[i - 1][j - 1] + 1;
				else
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); 
			}
		}

		int lcs = dp.back().back(); 
		return n + m - 2 * lcs; 
	}
}; 


// wrong ans!!  hashtable won't keep the order of chars!!!
class Solution3 {
public:
	int minDistance(string word1, string word2) {
		unordered_map<char, int> cnt2; 
		for (auto c : word2) cnt2[c] += 1; 
		int r = 0; 
		for (auto c : word1){
			if (cnt2[c] == 0)
				r += 1;
			else
				cnt2[c] -= 1; 
		}
		for (auto p : cnt2)
			if (p.second)
				r += p.second; 
		return r; 
	}
}; 


int main(){
	Solution3 a;

	cout << a.minDistance("adef", "de") << endl; 
	cout << a.minDistance("aedf", "de") << endl; 
	cout << a.minDistance("mart", "karma") << endl; 
	cout << a.minDistance("park", "spake") << endl; 



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

