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
// We are playing the Guess Game. The game is as follows:

// I pick a number from 1 to n. You have to guess which number I picked.
// Every time you guess wrong, I'll tell you whether the number I picked is higher or lower. 
// However, when you guess a particular number x, and you guess wrong, you pay $x. You win the game when you guess the number I picked.
// Example: 
// n = 10, I pick 8.

// First round:  You guess 5, I tell you that it's higher. You pay $5.
// Second round: You guess 7, I tell you that it's higher. You pay $7.
// Third round:  You guess 9, I tell you that it's lower. You pay $9.

// Game over. 8 is the number I picked.

// You end up paying $5 + $7 + $9 = $21.

// Given a particular n ¡Ý 1, find out how much money you need to have to guarantee a win.


// passed. Problem is hard to understand. It is better to start understanding from 1 number, 2 numbers and 3 numbers ........ 
class Solution {
public:
	// 1 -> n
	int getMoneyAmount(int n) {
		vector<vector<int>> m(n, vector<int>(n, 0));
		return helper(1, n + 1, m);
	}

	int helper(int st, int end, vector<vector<int>>& m){
		if (end - st <= 1)
			return 0;
		if (end - st == 2)
			return st;
		if (end - st == 3)
			return st + 1;
		if (m[st - 1][end - 2])
			return m[st - 1][end - 2];

		int res = INT_MAX;
		for (int i = st; i < end; ++i){
			res = min(res, i + max(helper(st, i, m), helper(i + 1, end, m)));
		}
		m[st - 1][end - 2] = res;
		return res;
	}
};




int main(){
	Solution a;

	vector<int> b = { 7, 2, 5, 10, INT_MAX };

	cout << a.getMoneyAmount(8); 

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

