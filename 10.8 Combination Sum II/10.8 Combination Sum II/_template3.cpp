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

vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 


class Solution {
public:
	VVI combinationSum2(VI& nums, int target){
		sort(nums.begin(), nums.end()); 
		VI path; 
		VVI res; 
		dfs(nums, 0, path, 0, res, target); 
		return res; 
	}

	void dfs(VI& nums, int i, VI& path, int sum, VVI& res, int tgt){
		if (sum == tgt){
			res.push_back(path); 
			return; 
		}
		if (sum > tgt)
			return; 

		unordered_set<int> v; 
		for (int j = i; j < nums.size(); ++j){
			if (!v.count(nums[j])){
				path.push_back(nums[j]);
				dfs(nums, j + 1, path, sum + nums[j], res, tgt);
				path.pop_back();
				v.insert(nums[j]);
			}
		}
	}
};


class Solution2 {
public:
	VVI combinationSum2(VI& nums, int target){
		// [1,1,1,2,2]
		sort(nums.begin(), nums.end()); 
		VI path; VVI res; 
		dfs(nums, 0, 0, target, path, res); 
		return res; 
	}

	void dfs(VI& nums, int i, int sum, int tgt, VI& path, VVI& res){
		if (i == nums.size()){
			if (sum == tgt)
				res.push_back(path);
			return; 
		}

		path.push_back(nums[i]); 
		dfs(nums, i + 1, sum + nums[i], tgt, path, res); 
		path.pop_back(); 

		if (path.empty() || path.back() != nums[i])
			dfs(nums, i + 1, sum, tgt, path, res); 
	}
}; 


int main(){
	Solution a;
	Solution2 a2;

	vector<int> b = { 1, 1, 2, 5, 6, 7, 10 }; 

	auto r = a.combinationSum2(b, 8); 
	prt2Layer(r); 

	cout << "======\n"; 
	r = a2.combinationSum2(b, 8); 
	prt2Layer(r); 


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

