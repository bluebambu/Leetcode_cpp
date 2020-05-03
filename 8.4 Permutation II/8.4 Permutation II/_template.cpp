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

//Wrong ans. 
class Solution{
public:
	vector<vector<int>> perm(vector<int>& s){
		sort(s.begin(), s.end());
		vector<vector<int>> res; 
		vector<int> path; 
		dfs(s, 0, res);
		return res; 
	}

	void dfs(vector<int>& s, int cur,  vector<vector<int>>& res){
		if (cur == s.size()){
			res.push_back(s); 
			return; 
		}

		for (int i = cur; i < s.size(); ++i){
			while (i > cur && i<s.size() && s[i] == s[i - 1])  // 判断重复可以取第一个， 也可以取最后一个
				++i; 
			if (i == s.size())	// 取第一个要记得注意端点
				continue;
			swap(s[cur], s[i]); 
			dfs(s, cur + 1, res); 
			swap(s[cur], s[i]); 
// 			while (i + 1 < s.size() && s[i] == s[i + 1])	// 最后一个
// 				++i;
		}
	}

};


// pass
class Solution2 {
public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		sort(nums.begin(), nums.end()); 
		vector<vector<int>> res; 
		dfs(nums, 0, res); 
		return res; 
	}

	void dfs(vector<int> nums, int cur, vector<vector<int>>& res){
		if (cur == nums.size()){
			res.push_back(nums); 
			return; 
		}

		for (int i = cur; i < nums.size(); ++i){
			if (i == cur || nums[i] != nums[i - 1]){
				vector<int> copy = nums; 
				copy.erase(copy.begin() + i); 
				copy.insert(copy.begin() + cur, nums[i]); 
				dfs(copy, cur + 1, res); 
			}
		}
	}
};


class Solution3 {
public:
	vector<vector<int>> permuteUnique(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		vector<vector<int>> res;
		dfs(nums, 0, res);
		return res;
	}

	void dfs(vector<int> nums, int cur, vector<vector<int>>& res){
		if (cur == nums.size()){
			res.push_back(nums);
			return;
		}

		for (int i = cur; i < nums.size(); ++i){
			if (i == cur || nums[i] != nums[i - 1]){
				swap(nums[cur], nums[i]); 
				dfs(nums, cur + 1, res); 
			}
		}
	}
};




int main(){
	Solution a;
	Solution3 a2; 

	vector<int> b{ 0,1,0,0,9 }; 

	auto c = a.perm(b); 
	auto c2 = a2.permuteUnique(b); 

	for (auto i : c2){
		for (auto j : i)
			cout << j << " ";
		cout << endl; 
	}


}

