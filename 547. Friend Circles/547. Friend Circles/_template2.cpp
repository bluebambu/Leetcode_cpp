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
//  There are N students in a class. Some of them are friends, while some are not. Their friendship is transitive in nature. For example, if A is a direct friend of B, and B is a direct friend of C, then A is an indirect friend of C. And we defined a friend circle is a group of students who are direct or indirect friends.
// Given a N*N matrix M representing the friend relationship between students in the class. If M[i][j] = 1, then the ith and jth students are direct friends with each other, otherwise not. And you have to output the total number of friend circles among all the students.
// Example 1:

// Input: 
// [[1,1,0],
//  [1,1,0],
//  [0,0,1]]
// Output: 2
// Explanation:The 0th and 1st students are direct friends, so they are in a friend circle. 
// The 2nd student himself is in a friend circle. So return 2.

// Example 2:
// Input: 
// [[1,1,0],
//  [1,1,1],
//  [0,1,1]]
// Output: 1
// Explanation:The 0th and 1st students are direct friends, the 1st and 2nd students are direct friends, 
// so the 0th and 2nd students are indirect friends. All of them are in the same friend circle, so return 1.

// Note:
//     N is in range [1,200].
//     M[i][i] = 1 for all students.
//     If M[i][j] = 1, then M[j][i] = 1.

// weighted Union Find
class UnionFind{
	vector<int> arr, sz; 
	int n; 
public:
	UnionFind(int m) :arr(m, 0), sz(m, 1), n(m) {
		for (int i = 0; i < n; ++i)
			arr[i] = i; 
	}

	int find(int i){
		if (i < 0 || i >= n)
			throw runtime_error("Out of boundary!! \n"); 

		while (arr[i] != i){
			arr[i] = arr[arr[i]]; // same statement: arr[i] = find(arr[i]); 
			i = arr[i]; 
		}
		return i; 
	}

	void unify(int i, int j){
		if (i == j)
			return; 
		
		int iroot = find(i), jroot = find(j); 
		if (iroot == jroot)
			return; 

		if (sz[iroot] < sz[jroot]){
			arr[jroot] = iroot; 
			sz[iroot] += 1; 
		}
		else{
			arr[iroot] = jroot; 
			sz[jroot] += 1; 
		}
	}

	int numOfComp(){
		int res = 0; 
		for (int i = 0; i < n; ++i){
			if (arr[i] == i)
				++res;
		}
		return res; 
	}
};


class Solution {
public:
	int findCircleNum(vector<vector<int>>& M) {
		int n = M.size(); 
		UnionFind helper(n); 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < i; ++j){
				if (M[i][j]>0)
					helper.unify(i, j); 
			}
		}

		return helper.numOfComp(); 
	}
};;




int main(){
	Solution a;

	vector<int> b = { 7, 2, 5, 10, INT_MAX };

	vector<vector<int>> mx = {
		{1,1,0},
		{1,1,0},
		{0,0,1}
	};

	cout << a.findCircleNum(mx); 

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

