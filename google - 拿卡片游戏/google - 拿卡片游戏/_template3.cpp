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
	int takeCards(vector<int>& nums) {
		return 0; 
	}
	void getMax(vector<int>& nums, int i, int cur, int other, int pl, int& res){
		if (i == nums.size()){
			res = max(res, pl ? cur : other); 
			return; 
		}

		getMax(nums, i + 1, other, cur + nums[i], !pl, res); 
		if (i+1<nums.size())
			getMax(nums, i + 2, other, cur + nums[i]+nums[i+1], !pl, res);
		if (i+2<nums.size())
			getMax(nums, i + 2, other, cur + nums[i]+nums[i+1]+nums[2], !pl, res);
	}
};


class Solution2 {
public:
	unordered_map<int, int> cache; 
	int takeCards(vector<int>& nums) {
		return getMax(nums, 0); 
	}
	int getMax(vector<int>& nums, int i){
		if (i >= nums.size()) return 0; 
		if (cache.count(i)) return cache[i]; 

		int r1 = 0, r2 = 0, r3 = 0; 
		r1 = trimin(
			nums[i] + getMax(nums, i + 2),
			nums[i] + getMax(nums, i + 3),
			nums[i] + getMax(nums, i + 4)
			); 
		if (i + 1 < nums.size()){
			r2 = trimin(
				nums[i] + nums[i + 1] + getMax(nums, i + 3),
				nums[i] + nums[i + 1] + getMax(nums, i + 4),
				nums[i] + nums[i + 1] + getMax(nums, i + 5)
			); 
		}
		if (i + 2 < nums.size()){
			r3 = trimin(
				nums[i] + nums[i + 1] + nums[i + 2] + getMax(nums, i + 4),
				nums[i] + nums[i + 1] + nums[i + 2] + getMax(nums, i + 5),
				nums[i] + nums[i + 1] + nums[i + 2] + getMax(nums, i + 6)
				);
		}

		cache[i] = trimax(r1, r2, r3); 
		return cache[i]; 
	}

	int trimax(int i, int j, int k){
		return max(i, max(j, k)); 
	}
	int trimin(int i, int j, int k){
		return min(i, min(j, k)); 
	}
}; 

// totally wrong!!!! 
// should not use void function. A return value is needed!
class Solution3 {
public:
	int takeCards(vector<int>& nums) {
		int res = 0; 
		int othermax = 0; 
		dfs(nums, 0, 0, 0, 0, res, othermax); 
		return res; 
	}
	void dfs(vector<int>& nums, int i, int cur, int other, int player, int& res, int& othermax){
		if (i > nums.size()) return; 
		if (i == nums.size()){
			if (player == 0){ 
				if (othermax < other){
					othermax = other; 
					res = cur; 
				}
			}
			else {
				if (othermax < cur){
					othermax = cur; 
					res = other; 
				}
			}
			return; 
		}

		dfs(nums, i + 1, other, cur + nums[i], !player, res, othermax);
		if (i + 1 < nums.size())
			dfs(nums, i + 2, other, cur + nums[i] + nums[i + 1], !player, res, othermax);
		if (i + 2 < nums.size())
			dfs(nums, i + 3, other, cur + nums[i] + nums[i + 1] + nums[i + 2], !player, res, othermax);
	}
}; 

int main(){
	Solution3 a;

	vector<int> b = { 3, 1, 4, 6, 3, 8}; 

	cout << a.takeCards(b) << endl; 

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

