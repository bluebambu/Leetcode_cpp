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
			cout << j << "\n";
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


typedef pair<int, int>  PII; 

class Solution {
public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> res; 
		vector<int> path; 
		helper(n, 0, path, res); 
		return res; 
	}

	void helper(int n, int cur, vector<int>& path, vector<vector<string>>& res){
		if (cur == n){
			res.push_back(conv(n, path)); 
			return; 
		}

		for (int i = 0; i < n; ++i){
			PII c = { cur, i }; 
			bool isGood = true; 
			for (int j = 0; j < path.size(); ++j){
				PII prev = { j, path[j] }; 
				if (conflict(c, prev)){
					isGood = false; 
					break;
				}
			}
			if (isGood == false)
				continue;

			path.push_back(i); 
			helper(n, cur + 1, path, res); 
			path.pop_back(); 
		}
	}

	vector<string> conv(int n, vector<int>& path){
		vector<string> res; 
		for (int i = 0; i < n; ++i){
			res.push_back(""); 
			for (int j = 0; j < n; ++j){
				if (i == path[j])
					res.back().push_back('Q');
				else
					res.back().push_back('.');
			}
		}
		return res; 
	}

	bool conflict(PII a, PII b){
		return a.first == b.first || a.second == b.second || abs(a.first - b.first) == abs(a.second - b.second); 
	}
};

int main(){
	Solution a; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	prt2Layer(a.solveNQueens(8)); 


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

