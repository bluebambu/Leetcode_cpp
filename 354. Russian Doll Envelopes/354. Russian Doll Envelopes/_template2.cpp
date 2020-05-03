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
// You have a number of envelopes with widths and heights given as a pair of integers(w, h).
// One envelope can fit into another if and only if both the width and height of one 
// envelope is greater than the width and height of the other envelope.

// What is the maximum number of envelopes can you Russian doll ? (put one inside other)

// Example :
// 		Given envelopes = [[5, 4], [6, 4], [6, 7], [2, 3]], the maximum number of envelopes 
// you can Russian doll is 3 ([2, 3] = >[5, 4] = >[6, 7]).


class Solution {
public:
	int maxEnvelopes(vector<pair<int, int>>& envelopes) {
		if (envelopes.empty())
			return 0; 

		sort(envelopes.begin(), envelopes.end()); 

		int n = envelopes.size(); 
		vector<int> dp(n, 1);  // init num is 1, counting itself as one of the result. 

		int res = 1;  
		for (int i = 1; i < n; ++i){
			for (int j = 0; j < i; ++j){
				if (canRD(envelopes, i, j))
					dp[i] = max(dp[i], dp[j] + 1); 
			}
			res = max(res, dp[i]); 
		}
		return res; 
	}

	bool canRD(vector<pair<int, int>>& env, int big, int small){
		return env[big].first > env[small].first && env[big].second > env[small].second; 
	}
};






int main(){
	Solution a; 

	vector<pair<int, int>> b = { { 5, 4 }, { 6, 4 }, { 6, 7 }, { 2, 3 } }; 

	cout << a.maxEnvelopes(b); 


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

