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
//  Initially on a notepad only one character 'A' is present. You can perform two operations on this notepad for each step:

//     Copy All: You can copy all the characters present on the notepad (partial copy is not allowed).
//     Paste: You can paste the characters which are copied last time.

// Given a number n. You have to get exactly n 'A' on the notepad by performing the minimum number of steps permitted. Output the minimum number of steps to get n 'A'.
// Example 1:

// Input: 3
// Output: 3
// Explanation:
// Intitally, we have one character 'A'.
// In step 1, we use Copy All operation.
// In step 2, we use Paste operation to get 'AA'.
// In step 3, we use Paste operation to get 'AAA'.

// Note:
//     The n will be in the range [1, 1000].



class Solution {
public:
	unordered_map<int, int> visited; 

	int minSteps(int n) {
		if (n == 1)
			return 0; 
		if (n == 2)
			return 2; 
		if (visited.count(n))
			return visited[n]; 

		int res = INT_MAX; 
		for (int i = 1; i < n; ++i){
			if (n%i == 0){
				int cpTimes = n / i; 
				res = min(res, minSteps(i) + cpTimes); 
			}
		}
		visited[n] = res; 

		return res; 
	}
};

class Solution2 {
public:
	int minSteps(int n) {
		vector<int> dp(n + 1, INT_MAX); 
		for (int i = 1; i <= n; ++i){
			if (i == 1) dp[i] = 0; 
			else if (i < 6) dp[i] = i; 
			else{
				for (int j = i - 1; j>=1; --j){ 
					if ((i%j) == 0){
						dp[i] = min(dp[i], dp[j] + (i / j)); 
						if (dp[i] < i - j)
							break;
					}
				}
			}
		}

		prt1Layer(dp); 
		return dp[n]; 
	}
}; 


int main(){
	Solution a; 
	Solution2 a2;

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	cout << a.minSteps(9) << endl;
	cout << a2.minSteps(9) << endl;


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

