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
// Numbers can be regarded as product of its factors. For example,

// 8 = 2 x 2 x 2;
//   = 2 x 4.

// Write a function that takes an integer n and return all possible combinations of its factors.

// Note:
//     You may assume that n is always positive.
//     Factors should be greater than 1 and less than n.

// Examples:
// input: 1
// output:

// []

// input: 37
// output:

// []

// input: 12
// output:

// [
//   [2, 6],
//   [2, 2, 3],
//   [3, 4]
// ]

// input: 32
// output:

// [
//   [2, 16],
//   [2, 2, 8],
//   [2, 2, 2, 4],
//   [2, 2, 2, 2, 2],
//   [2, 4, 4],
//   [4, 8]
// ]



// pass AC
class Solution {
public:
	vector<vector<int>> getFactors(int n) {
		if (n <= 1)
			return{}; 

		vector<vector<int>> res; 
		for (int i = 2; i <= sqrt(n); ++i){
			vector<int> cur; 
			if (n%i == 0){
				int r = n / i; 
				cur.push_back(i); 
				vector<vector<int>> tmp = getFactors(r); 
				for (int j = 0; j < tmp.size(); ++j){
					if (tmp[j][0]>=i){ // make sure the answer is ascending order. 
						cur.insert(cur.end(), tmp[j].begin(), tmp[j].end());
						res.push_back(cur);
						cur = vector<int>(cur.begin(), cur.begin() + 1);
					}
				}
				res.push_back({ i, r }); 
			}
		}
		return res; 
	}
};

class Solution2 {
public:
	vector<vector<int>> getFactors(int n) {
		unordered_map<int, vector<vector<int>>> m; 
		return f(n, m, 0); 
	}

	vector<vector<int>> f(int n, unordered_map<int, vector<vector<int>>>& m, int smallestFactor){
		vector<vector<int>> res; 
		for (int i = 2; i <= sqrt(n); ++i){
			if (n%i == 0 && i>=smallestFactor){
				auto rest = f(n / i, m, i);
				res.push_back({ i, n / i });
				for (auto v : rest){
					vector<int> head = { i };
					head.insert(head.end(), v.begin(), v.end());
					res.push_back(head);
				}			
			}
		}
		return res; 
	}
};



int main(){
	Solution a; 
	Solution2 a2; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	prt2Layer(a.getFactors(24)); 
	prt2Layer(a2.getFactors(24)); 

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

