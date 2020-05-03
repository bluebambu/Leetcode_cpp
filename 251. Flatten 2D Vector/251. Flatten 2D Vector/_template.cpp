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
#include <string> 
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>

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

// 
// Implement an iterator to flatten a 2d vector.
// 
// For example,
// Given 2d vector =
// 
// [
// 	[1, 2],
// 	[3],
// 	[4, 5, 6]
// ]
// 
// 
// 
// By calling next repeatedly until hasNext returns false, the order of elements returned by next should be : [1, 2, 3, 4, 5, 6].
// 
// Hint :
// 
// 	 How many variables do you need to keep track ?
// 	 Two variables is all you need.Try with x and y.
// 	 Beware of empty rows.It could be the first few rows.
// 	 To write correct code, think about the invariant to maintain.What is it ?
// 	 The invariant is x and y must always point to a valid point in the 2d vector.Should you maintain your invariant ahead of time or right when you need it ?
// 	 Not sure ? Think about how you would implement hasNext().Which is more complex ?
// 	 Common logic in two different places should be refactored into a common method.
// 
// 	 Follow up :
// As an added challenge, try to code it using only iterators in C++ or iterators in Java.
// 
// 
// 
// 这道题让我们压平一个二维向量数组，并且实现一个iterator的功能，包括next和hasNext函数，那么最简单的方法就是将二维数组按顺序先存入到一个一维数组里，然后此时只要维护一个变量i来记录当前遍历到的位置，hasNext函数看当前坐标是否小于元素总数，next函数即为取出当前位置元素，坐标后移一位，参见代码如下：
// 


class Vector2D {
public:
	vector<vector<int>> v; 
	int row, col; 


	Vector2D(vector<vector<int>>& vec2d):v(vec2d), row(0), col(0) {
		
	}

	int next() {
		int res = v[row][col]; 
		if (col == v[row].size() - 1)
			++row, col = 0;
		else
			++col; 
		return res; 
	}

	bool hasNext() {
		while (row < v.size() && col == v[row].size()){
			++row; 
			col = 0; 
		}
		return row < v.size(); 
	}
};


// another solution
class Vector2D2 {
public:
	Vector2D2(vector<vector<int>>& vec2d) {
		for (auto a : vec2d) {
			v.insert(v.end(), a.begin(), a.end());
		}
	}
	int next() {
		return v[i++];
	}
	bool hasNext() {
		return i < v.size();
	}
private:
	vector<int> v;
	int i = 0;
};


class Vector2D3 {
public:
	stack<vector<int>*> stk; 
	int idx; 

	Vector2D3(vector<vector<int>>& vec2d) {
		idx = 0; 
		for (int i = vec2d.size() - 1; i >= 0; --i)
			stk.push(&vec2d[i]); 
	}

	bool hasNext(){
		while (!stk.empty() && idx == stk.top()->size()){
			stk.pop(); 
			idx = 0; 
		}

		if (stk.empty())
			return false; 
			
		return idx < stk.top()->size(); 
	}

	int next(){
		return stk.top()->at(idx++); 
	}
}; 

// pass
class Vector2D4 {
public:

	int i, j; 
	vector<vector<int>> core; 
	Vector2D4(vector<vector<int>>& vec2d) {
		core = vec2d; 
		i = 0, j = 0; 
	}

	bool hasNext(){
		while (true){
			if (i >= core.size())
				return false; 
			if (j >= core[i].size())
				++i, j = 0;
			else
				return true; 
		}
		return true; 
	}

	int next(){
		return core[i][j++]; 
	}
}; 


/**
* Your Vector2D object will be instantiated and called as such:
* Vector2D i(vec2d);
* while (i.hasNext()) cout << i.next();
*/

int main() {

	vector<vector<int>> b = {
		{ },
		{  },
		{ 4, 5, 6 }
	}; 

	Vector2D a(b); 

	while (a.hasNext())
		cout << a.next() << ' '; 

	cout << endl; 



	Vector2D4 a2(b); 

	while (a2.hasNext())
		cout << a2.next() << ' '; 

	cout << endl; 

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

