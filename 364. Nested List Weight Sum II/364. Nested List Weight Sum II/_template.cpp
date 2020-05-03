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

// Different from the previous question where weight is increasing from root to leaf, now the weight is 
// defined from bottom up.i.e., the leaf level integers have weight 1, and the root level integers have the largest weight.

// Example 1:
// Given the list[[1, 1], 2, [1, 1]], return 8. (four 1's at depth 1, one 2 at depth 2)
// 	Example 2:
// Given the list[1, [4, [6]]], return 17. (one 1 at depth 3, one 4 at depth 2, and one 6 at depth 1; 1 * 3 + 4 * 2 + 6 * 1 = 17)

/**
* // This is the interface that allows for creating nested lists.
* // You should not implement it, or speculate about its implementation
*/
class NestedInteger {
  public:
    // Constructor initializes an empty nested list.
    NestedInteger();

    // Constructor initializes a single integer.
    NestedInteger(int value);

    // Return true if this NestedInteger holds a single integer, rather than a nested list.
    bool isInteger() const;

    // Return the single integer that this NestedInteger holds, if it holds a single integer
    // The result is undefined if this NestedInteger holds a nested list
    int getInteger() const;

    // Set this NestedInteger to hold a single integer.
    void setInteger(int value);

    // Set this NestedInteger to hold a nested list and adds a nested integer to it.
    void add(const NestedInteger &ni);

    // Return the nested list that this NestedInteger holds, if it holds a nested list
    // The result is undefined if this NestedInteger holds a single integer
    const vector<NestedInteger> &getList() const;
};


class Solution {
public:
	int depthSumInverse(vector<NestedInteger>& nestedList) {
		int unweighted = 0, weighted = 0; 
		while (nestedList.empty()){
			vector<NestedInteger> cur; 
			for (auto& a : nestedList){
				if (a.isInteger()){
					unweighted += a.getInteger();
				} else{
					cur.insert(cur.end(), a.getList().begin(), a.getList().end()); 
				}
			}
			weighted += unweighted; 
			nestedList = cur; 
		}
		return weighted; 
	}
};


class Solution3 {
public:
	int depthSumInverse(vector<NestedInteger>& nestedList) {
		int res = 0, pre = 0; 
		while (!nestedList.empty()){
			vector<NestedInteger> next; 
			int curlvl = pre; 
			for (int i = 0; i < nestedList.size(); ++i){
				if (nestedList[i].isInteger())
					curlvl += nestedList[i].getInteger();
				else{
					for (auto& v : nestedList[i].getList())
						next.push_back(v); 
				}
			}
			pre = curlvl; 
			res += curlvl; 
			nestedList = next; 
		}
		return res; 
	}
};

class Solution4 {
public:
	int depthSumInverse(vector<NestedInteger>& nestedList) {
		int dep = 0; 
		for (int i = 0; i < nestedList.size(); ++i){
			dep = max(dep, depth(nestedList[i], 1)); 
		}

		return dfs(nestedList, dep, 1); 
	}
	int dfs(vector<NestedInteger>& nest, int dep, int curdep){
		int r = 0; 
		for (int i = 0; i < nest.size(); ++i){
			if (nest[i].isInteger())
				r += nest[i].getInteger()*(dep - curdep + 1);
			else
				r += dfs(nest[i].getList(), dep, curdep + 1); 
		}
		return r; 
	}
	int depth(vector<NestedInteger>& nest, int curd){
		int d = curd; 
		for (int i = 0; i < nest.size(); ++i){
			if (!nest[i].isInteger()){
				d = max(d, depth(nest[i].getList(), curd + 1)); 
			}
		}
		return d; 
	}
};


class Solution5 {
public:
	int depthSumInverse(vector<NestedInteger>& nestedList) {
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
						prelvl += e.getInteger();
					}
					else
						q.push(e.getList());
				}
			}
			r += prelvl;
		}
		return r;
	}
};

int main() {
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

