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
void vprt(vector<T> v){
	for (auto i : v)
		cout << v << " ";
	cout << endl;
}

template <typename T>
void vvprt(vector<vector<T>> v){
	for (auto i : v){
		for (auto j : i){
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <typename C>
void setprt(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
// Given a nested list of integers, return the sum of all integers in the list weighted by their depth.
// Each element is either an integer, or a list -- whose elements may also be integers or other lists.
// Example 1:
// Given the list[[1, 1], 2, [1, 1]], return 10. (four 1's at depth 2, one 2 at depth 1)
// 	Example 2:
// Given the list[1, [4, [6]]], return 27. (one 1 at depth 1, one 4 at depth 2, and one 6 at depth 3; 1 + 4 * 2 + 6 * 3 = 27)


/**
* // This is the interface that allows for creating nested lists.
* // You should not implement it, or speculate about its implementation
*/
class NestedInteger {
  public:
    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};

class Solution {
public:
	int depthSum(vector<NestedInteger>& nestedList) {
		return dfs(nestedList, 1);
	}
	int dfs(vector<NestedInteger>& vn, int lvl){
		int res = 0; 
		for (NestedInteger& i : vn){
			if (i.isInteger()){
				res += i.getInteger() * lvl; 
			}
			else{
				res += dfs(i.getList(), lvl + 1); 
			}
		}
		return res; 
	}
};

class Solution2 {
public:
	int depthSum(vector<NestedInteger>& nestedList) {
		return dfs(nestedList, 1); 
	}
	int dfs(vector<NestedInteger>& nest, int lvl){
		int r = 0; 
		for (int i = 0; i < nest.size(); ++i){
			if (nest[i].isInteger())
				r += nest[i].getInteger()*lvl;
			else
				r += dfs(nest[i].getList(), lvl + 1);
		}
		return r; 
	}
}; 


class Solution3 {
public:
	int depthSum(vector<NestedInteger>& nestedList) {
		queue<vector<NestedInteger>> q; 
		q.push(nestedList); 

		int prelvl = 0, r = 0; 
		while (!q.empty()){
			int sz = q.size(); 
			while (sz--){
				vector<NestedInteger> f = q.front(); 
				q.pop(); 

				for (auto& e : f){
					if (e.isInteger()){
						prelvl += e; 
					}
					else
						q.push(e); 
				}
			}
			r += prelvl; 
		}

		return r; 
	}

};  


int main()
{
	Solution a;

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

