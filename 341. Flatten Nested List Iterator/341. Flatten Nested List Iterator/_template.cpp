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
// Given a nested list of integers, implement an iterator to flatten it.
// Each element is either an integer, or a list -- whose elements may also be integers or other lists.
// Example 1:
// Given the list[[1, 1], 2, [1, 1]],
// By calling next repeatedly until hasNext returns false, the order of elements returned by next should be : [1, 1, 2, 1, 1].

// Example 2 :
// Given the list[1, [4, [6]]],
// By calling next repeatedly until hasNext returns false, the order of elements returned by next should be : [1, 4, 6].



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


// pass AC
class NestedIterator {
public:
	vector<NestedInteger> st; 

	NestedIterator(vector<NestedInteger> &nestedList){
		for (int i = nestedList.size() - 1; i >= 0; --i){
			st.push_back(nestedList[i]); 
		}
	}

	int next() {
		int tmp = st.back().getInteger();
		st.pop_back();
		return tmp;
	}

	bool hasNext() {
		// 复杂情况： [[[[]]],[]]， 参照此种情况， 空list 的情况必须在hasNext 中检查！！ 
		while (!st.back().isInteger()){
			vector<NestedInteger> tmp = st.back().getList();
			st.pop_back();
			for (int i = tmp.size() - 1; i >= 0; --i){
				st.push_back(tmp[i]);
			}
		}

		return st.size(); 
	}
};

// pass AC
class NestedIterator {
public:
	stack<NestedInteger*> stk;
	NestedIterator(vector<NestedInteger> &nestedList) {
		for (int i = nestedList.size() - 1; i >= 0; --i)
			stk.push(&nestedList[i]);
	}

	int next() {
		if (hasNext()){
			NestedInteger* top = stk.top();
			stk.pop();
			return top->getInteger();
		}
		else
			throw runtime_error("error");
	}

	bool hasNext() {
		if (stk.empty())
			return false;
		while (!stk.empty() && !stk.top()->isInteger()){
			NestedInteger* front = stk.top();
			stk.pop();

			vector<NestedInteger>& vec = front->getList();
			for (int i = vec.size() - 1; i >= 0; --i){
				stk.push(&vec[i]);
			}
		}
		return !stk.empty();
	}
};

class NestedIterator5 {
public:
	stack<NestedInteger*> stk;

	NestedIterator5(vector<NestedInteger> &nestedList) {
		for (int i=nestedList.size()-1; i>=0; --i)
			stk.push(&(nestedList[i])); 
	}

	bool hasNext(){
		while (!stk.empty() && !(stk.top()->isInteger())){
			NestedInteger *top = stk.top(); 
			stk.pop(); 
			for (int i = top->getList().size(); i >= 0; --i)
				stk.push(&(top->getList()[i])); 
		}

		if (stk.empty())
			return false; 
		return true; 
	}

	int next(){
		
	}
}; 


int main() {

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

