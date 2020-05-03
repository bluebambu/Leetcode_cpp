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
#include <bitset>

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
	bool isPowOf4(int num){
		while (num != (num%4))
			num %= 4; 
		return num == 0; 
	}

	bool isPowOf4_2(int num){
		if (num == 0)
			return false;;

		// check if it is power of 2
		if (num&(num - 1) != 0)
			return false; 
		
		bitset<32> mask("0101010101010101010101010101010101010101010101010101"); 
		int m = mask.to_ulong(); 

		return (m&num) > 0; 
	}
};


class Solution2{
public:
	bool powOf4(int i){
		i = abs(i); 

		if (i == 0)
			return false; 
		if (i&(i - 1) != 0)
			return false; 

		bitset<32> mask("010101010101010101010101010101010101010101010101"); 
		int msk = mask.to_ulong(); 

		return i&msk > 0; 
	}
};








int main(){
	Solution a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	cout << a.isPowOf4_2(0) << endl;;
	cout << a.isPowOf4_2(1) << endl;;
	cout << a.isPowOf4_2(2) << endl;;
	cout << a.isPowOf4_2(3) << endl;;
	cout << a.isPowOf4_2(4) << endl;;
	cout << a.isPowOf4_2(5) << endl;;

	cout << a.isPowOf4_2(-1) << endl;;
	cout << a.isPowOf4_2(-2) << endl;;
	cout << a.isPowOf4_2(-3) << endl;;
	cout << a.isPowOf4_2(-4) << endl;;
	cout << a.isPowOf4_2(-5) << endl;;

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

