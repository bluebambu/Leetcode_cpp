// _template.cpp : Defines the entry point for the console application.
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

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }


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
		for (int i = 0; i<n; ++i){
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

template <typename T>
void vprt(T v){
	for (auto i : v)
		cout << v << " ";
	cout << endl; 
}

template <typename T>
void vvprt(T v){
	for (auto i : v){
		for (auto j : i){
			cout << j << " "; 
		}
		cout << endl;
	}
	cout << endl; 
}


//////////////////////////////////////////////////////
// Suppose you are at a party with n people(labeled from 0 to n - 1) and among them, there may exist one celebrity.The 
// definition of a celebrity is that all the other n - 1 people know him / her but he / she does not know any of them.

// Now you want to find out who the celebrity is or verify that there is not one.The only thing you are allowed to do is 
// to ask questions like : "Hi, A. Do you know B?" to get information of whether A knows B.You need to find out the celebrity
// (or verify there is not one) by asking as few questions as possible(in the asymptotic sense).

// You are given a helper function bool knows(a, b) which tells you whether A knows B.Implement a function int findCelebrity(n), 
// your function should minimize the number of calls to knows.

// Note : There will be exactly one celebrity if he / she is in the party.Return the celebrity's label if there is a celebrity in 
// 	   the party. If there is no celebrity, return -1.





// Forward declaration of the knows API.
// Forward declaration of the knows API.
bool knows(int a, int b){
	return true;
}

// 本来想用set来做。 但是set有个问题，就是iterate的时候的erase操作很麻烦！！ 谨记。 

// most naive solution
class Solution {
public:
	int findCelebrity(int n) {
		vector<int> res; 
		int j; 
		for (int i = 0; i < n; ++i){
			for ( j = 0; j < n; ++j){
				if (j!=i && (knows(i,j) || !knows(j,i)))
					break;
			}
			if (j == n)
				res.push_back(i); 
		}
		return res.size() == 1 ? res.back() : -1;
	}
};

// 可以优化的地方： 凡是和anyone认识的，一定不是celebrity。 凡是不认识someone的，一定不是celebrity。 
// 这样通过 knows(i,j) 和 knows(j,i) 就可以判断出来 i，j 是否一定 不是 celebrity. 这个结果可以存储起来。 
// pass AC, time is the same as last solution.....
class Solution {
public:
	int findCelebrity(int n) {
		vector<bool> buf(n, true);
		for (int i = 0; i < n; ++i){
			if (buf[i] == false)
				continue;
			for (int j = 0; j < n; ++j){
				// knows(i,j) and knows(j,i) 在这里一定要都检查到！！
				if (j != i && (knows(i, j) || !knows(j, i))){
					buf[i] = false;
					break;
				}
				if (j != i && knows(j, i))
					buf[j] = false;
			}
		}

		int m = 0, res = -1;
		for (int i = 0; i < n; ++i){
			if (buf[i] == true){
				++m;
				res = i;
			}
		}

		return m == 1 ? res : -1;
	}
};


// 最优的方法是： first, if person A knows person B, then B could be the candidate of being a celebrity, A must not be a celebrity. 
// We iterate all the n persons and we will have a candidate that everyone knows this candidate.

// second, we check two things after we get this candidate. 1. If this candidate knows other person in the group, if the candidate 
// knows anyone in the group, then the candidate is not celebrity, return -1; 2. if everyone knows this candidate, if anyone does not know the candidate, return -1;
class Solution {
public:
	int findCelebrity(int n) {
		int candidate = 0; 
		for (int i = 1; i < n; ++i){
			if (knows(candidate, i))
				candidate = i;
		}

		for (int i = 0; i < n; ++i){
			if (i==candidate)
				continue;

			if (knows(candidate, i) || !knows(i, candidate))
				return -1;
		}
		return candidate; 
	}
};


int main()
{
	Solution a;

	cout<<a.findCelebrity(2); 
	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/

}

