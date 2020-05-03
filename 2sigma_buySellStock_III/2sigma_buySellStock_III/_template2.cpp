// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <cassert>
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


struct TreeNode {
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


// pass AC
class Solution {
public:
	int stockIII(vector<int>& nums){
		if (nums.size()<2)
			return 0; 

		int n = nums.size(); 
		vector<int> left(n, 0), right(n, 0); 

		int lowest = nums[0]; 
		for (int i = 1; i < n; ++i){
			lowest = min(lowest, nums[i]);
			left[i] = max(left[i - 1], nums[i] - lowest); 
		}
		
		int highest = nums[n - 1]; 
		for (int i = n - 2; i >= 0; --i){
			highest = max(highest, nums[i]); 
			right[i] = max(right[i + 1], highest - nums[i]); 
		}

		int res = 0; 
		for (int i = 0; i < n; ++i){
			res = max(res, left[i] + right[i]); 
		}
		return res; 
	}
};

void TEST_invalid_input(){
	Solution s; 
	vector<int> a = {}; 
	assert(s.stockIII(a) == 0); 
}

void TEST_one_price(){
	Solution s; 
	vector<int> a = {6}; 
	assert(s.stockIII(a) == 0); 
}

void TEST_two_price(){
	Solution s; 
	vector<int> a = {6, 8}; 
	assert(s.stockIII(a) == 2); 
}

void TEST_decreasing(){
	Solution s; 
	vector<int> a = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	assert(s.stockIII(a) == 0); 
}

void TEST_increasing(){
	Solution s; 
	vector<int> a = { 1, 2, 3, 4, 5, 6, 7, 8, 9 }; 
	assert(s.stockIII(a) == 8); 
}



class Solution2{
public:
	int maxProfit(vector<int>& prices){
		if (prices.size() < 2)
			return 0; 

		int n = prices.size(); 
		vector<int> left(n, 0), right(n, 0); 
		
		// left 
		int lowest = prices[0]; 
		for (int i = 1; i < n; ++i){
			lowest = min(lowest, prices[i]); 
			left[i] = max(left[i - 1], prices[i] - lowest); 
		}

		int hightest = prices.back(); 
		for (int j = n - 2; j >= 0; --j){
			hightest = max(hightest, prices[j]); 
			right[j] = max(right[j + 1], hightest - prices[j]); 
		}

		int res = 0; 
		for (int i = 0; i < n; ++i){
			res = max(res, left[i] + right[i]); 
		}

		return res; 
	}
};


void TEST_random(){
	Solution2 s; 
	vector<int> a = { 2, 4, 5, 7, 0, 5, 1, 9, 11, 111 }; 
	assert(s.maxProfit(a) == 116); 
}




int main(){
	TEST_random(); 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

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

