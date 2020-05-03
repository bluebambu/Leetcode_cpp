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
// Imagine you have a special keyboard with the following keys:

// Key 1: (A): Print one 'A' on screen.
// Key 2: (Ctrl-A): Select the whole screen.
// Key 3: (Ctrl-C): Copy selection to buffer.
// Key 4: (Ctrl-V): Print buffer on screen appending it after what has already been printed.

// Now, you can only press the keyboard for N times (with the above four keys), find out the maximum numbers of 'A' you can print on screen.

// Example 1:
// Input: N = 3
// Output: 3
// Explanation: 
// We can at most get 3 A's on screen by pressing following key sequence:
// A, A, A

// Example 2:
// Input: N = 7
// Output: 9
// Explanation: 
// We can at most get 9 A's on screen by pressing following key sequence:
// A, A, A, Ctrl A, Ctrl C, Ctrl V, Ctrl V

// it is a greedy solution: 
// at least, you can get N * A 
// you want more, you must have C-A, C-c, which take 2 more steps,
// so you left N-2 steps. 
// now, in N-2 steps, you can try most of cases, i.e., try  maxA(N-2-j)*j. Pay attention that here uses maxA(N-1-j). 
class Solution {
public:
	int maxA(int N) {
		int res = N; 
		for (int j = 1; j < N - 2; ++j)
			res = max(res, maxA(N - 2 - j)*(j+1)); 
		return res; 
	}
};

// also you can change it to this solution, switch the j+1 and N-2-j; 
class Solution2{
public:
	int maxA(int N){
		int res = N; 
		for (int j = 1; j < N - 2; ++j)
			res = max(res, maxA(j)*(N - 2 - j + 1)); 
		return res; 
	}
};


class Solution3 {
public:
	int maxA(int N) {
		vector<int> dp(N + 1, INT_MIN); 
		for (int i = 1; i <= N; ++i){
			if (i < 6) dp[i] = i; 
			else{
				for (int j = i - 1; j >= 1; --j){
					dp[i] = max(dp[i], dp[j]*(i-j-1)); 
				}
			}
		}
		return dp[N]; 
	}
}; 


int main(){
	Solution a; 
	Solution3 a3; 

	cout << a3.maxA(7) << endl; 
	cout << a3.maxA(8) << endl;

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


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

