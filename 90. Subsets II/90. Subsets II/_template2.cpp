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

// wrong answer!!!!
class Solution {
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		vector<int> path; 
		vector<vector<int>> res; 
		helper(nums, 0, path, res); 
		return res; 
	}

	void helper(vector<int>& nums, int cur, vector<int>& path, vector<vector<int>>& res){
		if (cur == nums.size()){
			res.push_back(path); 
			return; 
		}

		helper(nums, cur + 1, path, res); 
		if (cur>0 && nums[cur]==nums[cur-1] && (path.empty() || path.back()!=nums[cur])){
			return; 
		}
		path.push_back(nums[cur]);
		helper(nums, cur + 1, path, res);
		path.pop_back();
	}
};



class Solution2 {
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		vector<int> path;
		vector<vector<int>> res;
		helper(nums, 0, path, res);
		return res;
	}

	void helper(vector<int>& nums, int cur, vector<int>& path, vector<vector<int>>& res){
		res.push_back(path); 

		for (int i = cur; i < nums.size(); ++i){
			path.push_back(nums[cur]); 
			helper(nums, i + 1, path, res); 
			path.pop_back(); 
			while (i + 1 < nums.size() && nums[i + 1] == nums[i]) ++i; 
		}
	}
}; 


// pass AC
class Solution3 {
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		vector<vector<int>> res; 
		res.push_back({}); 

		int startpos = 0, lastpos = 0; 
		for (int i = 0; i < nums.size(); ++i){
			if (i > 0 && nums[i] == nums[i - 1])
				startpos = lastpos; 
			else
				startpos = 0; 

			lastpos = res.size(); 
			int n = res.size(); 
			for (int j = startpos; j < n; ++j){
				res.push_back(res[j]); 
				res.back().push_back(nums[i]); 
			}
		}
		return res; 
	}
}; 

// pass
class Solution4 {
public:
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		sort(nums.begin(), nums.end()); 
		vector<int> path; 
		vector<vector<int>> res; 
		dfs(nums, 0, path, res); 
		return res; 
	}

	void dfs(vector<int>& nums, int i, vector<int>& path, vector<vector<int>>& res){
		if (i == nums.size()){
			res.push_back(path); 
			return; 
		}

		if (path.empty() || path.back() != nums[i])
			dfs(nums, i + 1, path, res);

		path.push_back(nums[i]);
		dfs(nums, i + 1, path, res);
		path.pop_back();
	}
}; 

class Solution5 {
public:
	vector<vector<int>> subsetsWithDup(vector<int>& nums) {
		sort(nums.begin(), nums.end()); 
		vector<vector<int>> res; 
		vector<int> path; 
		dfs(nums, 0, path, res); 
		return res; 
	}

	void dfs(vector<int>& nums, int i, vector<int>& path, vector<vector<int>>& res){
		if (i == nums.size()){
			res.push_back(path); 
			return; 
		}

		if (path.empty() || nums[i] != path.back()){
			dfs(nums, i + 1, path, res); 
		}

		path.push_back(nums[i]); 
		dfs(nums, i + 1, path, res); 
		path.pop_back(); 
	}
};



int main(){
	Solution3 a; 
	Solution5 a2; 

	vector<int> b = { 1,2,2 }; 

	prt2Layer(a.subsets(b));
	cout << "======" << endl; 
	prt2Layer(a2.subsetsWithDup(b));

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

