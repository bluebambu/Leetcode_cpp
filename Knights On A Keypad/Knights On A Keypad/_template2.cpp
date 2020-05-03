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
// The numbers on a telephone keypad are arranged thus:
// 1 2 3
// 4 5 6
// 7 8 9
//   0
// Starting from the digit 1, and choosing successive digits as a knight 
// moves in chess, determine how many different paths can be formed of length n. 
// There is no need to make a list of the paths, only to count them.
// A knight moves two steps either horizontally or vertically followed by one 
// step in the perpendicular direction; thus, from the digit 1 on the keypad a knight can 
// move to digits 6 or 8, and from the digit 4 on the keypad 
// a knight can move to digits 3, 9 or 0. A path may visit the same digit more than once.




class Solution {
public:
	int Knights(int n){
		vector<int> corner(n + 1, 0), side28(n + 1, 0), side46(n + 1, 0), center(n + 1, 0), zero(n + 1, 0);
		
		// initial state is '1'. If it is others, need to change
		// to other init condition. 
		corner[0] = 1; 

		for (int i = 1; i <= n; ++i){
			side28[i] = corner[i - 1]; 
			side46[i] = corner[i - 1] + 2*zero[i-1]; 
			corner[i] = 2*side28[i - 1] + 2*side46[i - 1]; 
			zero[i] = side46[i - 1]; 
		}

		return corner.back() + side46.back() + side28.back() + zero.back(); 
	}
};



int main(){
	Solution a;

	vector<int> b = { 7, 2, 5, 10, INT_MAX };

	for (int i = 1; i <= 10; ++i){
		cout << a.Knights(i) << endl;;
	}

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

