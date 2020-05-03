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

vector<string> keyboard{
		" ", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};  // 0 ~ 9

//should be right
// Iteration!

class Solution
{
public:
	vector<string> phone(string digits){
		vector<string> res(1); 

		for (int i = 0; i < digits.size(); ++i){
			string& posNums = keyboard[digits[i] - '0']; 
			int preSz = res.size(); 
			for (int j = 0; j < posNums.size()-1; ++j){
				res.insert(res.begin(), res.begin(), res.begin() + preSz); 
			}

			for (int j = 0; j < posNums.size(); ++j){
				for (int k = 0; k < preSz; ++k){
					res[j*preSz + k].push_back(posNums[j]); 
				}
			}
		}
		return res; 
	}

};



// recursion 

class Solution2 {
public:
	vector<string> phone(string digits){
		vector<string> res; 
		string path; 
		dfs(digits, 0, path, res);
		return res;
	}
	void dfs(string& digits, int cur, string& path, vector<string>& res){
		if (cur == digits.size()){
			res.push_back(path); 
			return;
		}
		for (int i = 0; i < keyboard[digits[cur]-'0'].size(); ++i){
			path.push_back(keyboard[digits[cur] - '0'][i]);
			dfs(digits, cur + 1, path, res); 
			path.pop_back();
		}
	}
};

class Solution3 {
public:
	vector<vector<int>> tsum(vector<int> nums, int target){
		sort(nums.begin(), nums.end()); 
		vector<vector<int>> res;
		int diff = nums[0] + nums[1] + nums[2] - target; 

		for (int i = 0; i < nums.size(); ++i){
			for (int j = i + 1, k = nums.size() - 1; j < k;){
				if (abs(nums[i] + nums[j] + nums[k] - target) < diff){
					diff = abs(nums[i] + nums[j] + nums[k] - target); 
					res.clear(); 
					res.push_back()
				}
			}
		}
	}
};

int main()
{
	Solution2 a;

	auto b = a.phone("234");

	for (auto i : b)
		cout << i << endl;


}

