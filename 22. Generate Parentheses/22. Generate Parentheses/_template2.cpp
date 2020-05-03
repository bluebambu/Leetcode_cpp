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
// Given n pairs of parentheses, write a function to generate all combinations of well - formed parentheses.

// For example, given n = 3, a solution set is :
// [
// 	"((()))",
// 	"(()())",
// 	"(())()",
// 	"()(())",
// 	"()()()"
// ]

// pass AC. 
class Solution {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> res; 
		string path; 
		helper(n, path, res, 0, 0); 
		return res; 
	}

	void helper(int n, string& path, vector<string>& res, int left, int right){
		if (left == n && right == n){
			res.push_back(path); 
			return;
		}
		if (left > n || right > n)
			return; 

		path.push_back('('); 
		helper(n, path, res, left + 1, right); 
		path.pop_back(); 

		if (right < left){
			path.push_back(')'); 
			helper(n, path, res, left , right + 1);
			path.pop_back();
		}
	}
};

class Solution2 {
public:
	vector<string> generateParenthesis(int n) {
		vector<string> res; 
		dfs(n, res, 0, 0, ""); 
		return res; 
	}
	void dfs(int n, vector<string>& res, int left, int right, string path){
		if (left == n && right == n){
			res.push_back(path); 
			return; 
		}
		if (left > n || right > n || left < right)
			return; 

		dfs(n, res, left + 1, right, path + "(");
		dfs(n, res, left, right + 1, path + ")");
	}
}; 


class Solution3 {
public:
	vector<string> generateParenthesis(int n) {	
		vector<string> res; 
		dfs(n, 0, 0, "", res); 
		return res; 
	}
	void dfs(int n, int left, int right, string path, vector<string>& res){
		if (left > n || right > n)
			return; 

		if (left == n && right == n){
			res.push_back(path); 
			return; 
		}

		if (left >= right)
			dfs(n, left + 1, right, path + "(", res); 
		if (left > right)
			dfs(n, left, right + 1, path + ")", res); 
	}
};



int main(){
	Solution a;
	Solution3 a2; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	prt2Layer(a.generateParenthesis(4)); 
	prt2Layer(a2.generateParenthesis(4));

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

