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
// Assume you have an array of length n initialized with all 0's and are given k update operations.

// Each operation is represented as a triplet: [startIndex, endIndex, inc] which increments each element of subarray A[startIndex ... endIndex] (startIndex and endIndex inclusive) with inc.

// Return the modified array after all k operations were executed.

// Example:

// Given:
//     length = 5,
//     updates = [
//         [1,  3,  2],
//         [2,  4,  3],
//         [0,  2, -2]
//     ]

// Output:

//     [-2, 0, 3, 5, 3]

// Explanation:

// Initial state:
// [ 0, 0, 0, 0, 0 ]

// After applying operation [1, 3, 2]:
// [ 0, 2, 2, 2, 0 ]

// After applying operation [2, 4, 3]:
// [ 0, 2, 5, 5, 3 ]

// After applying operation [0, 2, -2]:
// [-2, 0, 3, 5, 3 ]


class Solution {
public:
	vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
		vector<int> incVec(length, 0); 

		for (auto i : updates){
			incVec[i[0]] += i[2]; 
			if (i[1]+1<length)
				incVec[i[1]+1] -= i[2];
		}

		vector<int> res(length, 0); 
		int curInc = 0; 
		for (int i = 0; i < res.size(); ++i){
			curInc += incVec[i]; 
			res[i] += curInc; 
		}
		return res; 
	}
};

// optimized solution
class Solution2 {
public:
	vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
		vector<int> res(length + 1, 0); 

		for (auto i : updates){
			res[i[0]] += i[2]; 
			res[i[1] + 1] -= i[2]; 
		}

		for (int i = 1; i < res.size(); ++i){
			res[i] += res[i - 1]; 
		}
		res.pop_back(); 
		return res; 
	}
}; 

class Solution3 {
public:
	vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
		vector<int> inc(length + 1, 0); 
		for (auto mod : updates){
			inc[mod[0]] += mod[2]; 
			inc[mod[1] + 1] -= mod[2]; 
		}

		vector<int> res(length, 0); 
		int curinc = 0; 
		for (int i = 0; i < res.size(); ++i){
			curinc += inc[i]; 
			res[i] = curinc; 
		}

		return res; 
	}
}; 

class Solution4{
public:
	vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
		vector<int> flag(length, 0); 
		for (auto v : updates){
			flag[v[0]] += v[2]; 
			if (v[1]!=length-1)
				flag[v[1]+1] -= v[2];
		}

		vector<int> res(length, 0); 
		int add = 0; 
		for (int i = 0; i < length; ++i){
			add += flag[i]; 
			res[i] += add; 
		}

		return res; 
	}
};


int main(){
	Solution a; 
	Solution4 a2; 

	vector<vector<int>> updates = {
		{1, 3, 2}, 
		{2, 4, 3}, 
		{0, 2, -2}
	};

	auto r1 = a.getModifiedArray(5, updates),
		r2 = a2.getModifiedArray(5, updates); 

	prt1Layer(r1); 
	prt1Layer(r2); 


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

