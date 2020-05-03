// _template4.cpp : Defines the entry point for the console application.
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

typedef vector<int> VI; 
typedef vector<VI> VVI; 
typedef pair<int, int> PII; 

VVI dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 

// not tested
class Solution {
public:
	vector<vector<int>> nSum(vector<int>& nums, int target, int n){
		sort(nums.begin(), nums.end()); 
		return solve(nums, n, target, 0); 
	}

	vector<vector<int>> solve(vector<int>& nums, int n, int tgt, int start){
		if (start + n >= nums.size())
			return{}; 

		vector<vector<int>> res; 
		if (n == 2){
			int end = nums.size() - 1; 
			while (start < end){
				int sum = nums[start] + nums[end]; 
				if (sum > tgt)
					--end;
				else if (sum < tgt)
					++start; 
				else{
					res.push_back({ nums[start], nums[end] }); 
					int s_val = nums[start], e_val = nums[end]; 
					while (start < end && nums[start] == s_val) ++start; 
					while (start < end && nums[end] == e_val) --end; 
				}
			}
			return res; 
		}
		else{
			for (int i = start; i < nums.size(); ++i){
				int cur = nums[i];
				vector<vector<int>> NMinusOne = solve(nums, n - 1, tgt - cur, i + 1);
				if (NMinusOne.empty() == false){
					for (int j = 0; j < NMinusOne.size(); ++j){
						vector<int> c = { cur }; 
						c.insert(c.end(), NMinusOne[j].begin(), NMinusOne[j].end()); 
						res.push_back(c); 
					}
				}
			}

			return res; 
		}
	}
};


int main(){
	Solution a;

	vector<int> b = { 1, 2, 3, 4, 5 }; 



	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6,
		new TreeNode(3, new TreeNode(1),
						new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
						new TreeNode(9,
		                               new TreeNode(10),
		                               nullptr)));
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

