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



class Solution {
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end()); 
		vector<vector<int>> res; 
		vector<int> path; 
		helper(candidates, 0, target, path, 0, res);
		return res; 
	}

	void helper(vector<int>& cand, int cur, int target, vector<int>& path, int sum, vector<vector<int>>& res){
		if (sum == target){
			res.push_back(path); 
			return; 
		}
		if (sum > target){
			return; 
		}

		for (int i = cur; i < cand.size(); ++i){
			path.push_back(cand[i]); 
			sum += cand[i]; 
			helper(cand, i, target, path, sum, res); 
			path.pop_back(); 
			sum -= cand[i]; 
		}
	}
};


class Solution2 {
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end()); 
		vector<int> path; 
		vector<vector<int>> res; 
		dfs(candidates, 0, path, 0, res, target); 
		return res; 
	}

	void dfs(vector<int>& cand, int i, vector<int>& path, int sum, vector<vector<int>>& res, int tgt){
		if (sum == tgt){
			res.push_back(path); 
			return; 
		}
		if (sum > tgt)
			return; 

		for (int j = i; j < cand.size(); ++j){
			path.push_back(cand[j]); 
			dfs(cand, j, path, sum + cand[j], res, tgt); 
			path.pop_back(); 
		}
	}
}; 


class Solution3 {
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		vector<vector<int>> res; 
		dfs(candidates, 0, 0, {}, target, res); 
		return res; 
	}
	void dfs(vector<int>& cand, int i, int sum, vector<int> path, int tgt, vector<vector<int>>& res){
		if (sum > tgt) return; 
		if (sum == tgt){
			res.push_back(path); 
			return; 
		}
		for (int j = i; j < cand.size(); ++j){
			path.push_back(cand[j]); 
			dfs(cand, j, sum + cand[j], path, tgt, res); 
			path.pop_back(); 
		}
	}
};



int main(){
	Solution2 a; 

	vector<int> b = { 1, 3, 6, 7, 2  }; 

	prt2Layer(a.combinationSum(b, 7)); 


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
