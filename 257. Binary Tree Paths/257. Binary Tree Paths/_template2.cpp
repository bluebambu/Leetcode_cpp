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


class Solution {
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> res; 
		help(root, "", res); 
		return res;
	}

	bool help(TreeNode*node, string path, vector<string>& res){
		if (!node)
			return false; 

		if (path.empty())
			path += to_string(node->val); 
		else
			path += "->" + to_string(node->val);
		
		bool l = help(node->left, path, res); 
		bool r = help(node->right, path, res); 

		if (!l && !r)
			res.push_back(path); 

		return true;  // here must return true! 
	}
};


class Solution2 {
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> res; 
		if (!root)
			return res; 
		unordered_map<TreeNode*, string> m; 
		queue<TreeNode*> que; 
		que.push(root); 
		m[root] = to_string(root->val); 

		while (!que.empty()){
			TreeNode* front = que.front(); 
			que.pop(); 

			if (!front->left && !front->right){
				res.push_back(m[front]);
			}
			else{
				if (front->left){
					que.push(front->left); 
					m[front->left] = m[front] + "->"+to_string(front->left->val); 
				}
				if (front->right){
					que.push(front->right); 
					m[front->right] = m[front] + "->"+to_string(front->right->val); 
				}
			}
		}
		return res; 
	}
};


class Solution3 {
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> res; 
		dfs(root, res, ""); 
		return res; 
	}
	void dfs(TreeNode *n, vector<string>& res, string pre){
		if (!n)
			return; 
		if (!n->left && !n->right){
			res.push_back(pre + to_string(n->val)); 
			return; 
		}

		dfs(n->left, res, pre + to_string(n->val) + "->"); 
		dfs(n->right, res, pre + to_string(n->val) + "->"); 
	}
}; 


class Solution4 {
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> res; 
		stack<TreeNode*> stk; 
		stack<string> paths; 
		stk.push(root); 
		paths.push(""); 

		while (!stk.empty()){
			TreeNode *cur = stk.top(); 
			stk.pop(); 
			string curs = paths.top(); 
			paths.pop(); 

			if (!cur->left && !cur->right){
				res.push_back(curs + to_string(cur->val)); 
			}

			if (cur->left){
				stk.push(cur->left); 
				paths.push(curs + to_string(cur->val) + "->"); 
			}
			if (cur->right){
				stk.push(cur->right); 
				paths.push(curs + to_string(cur->val) + "->"); 
			}
		}

		return res; 
	}
}; 

int main(){
	Solution a; 
	Solution4 a2; 

	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, nullptr,
													nullptr),
									 new TreeNode(8, new TreeNode(0),
													nullptr));
	/*      6
		3       8
	1    4   7    9
	*/

	auto c1 = a.binaryTreePaths(tree); 
	auto c2 = a2.binaryTreePaths(tree); 

	prt1Layer(c1); 
	prt1Layer(c2); 


	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

