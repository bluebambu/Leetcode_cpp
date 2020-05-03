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
	int twoSubarray(vector<int>& nums) {
		int n = nums.size(); 
		vector<int> llcl(n, 0); 
		vector<int> lgbl = llcl, rlcl = llcl, rgbl = llcl;  

		llcl[0] = nums[0], lgbl[0] = nums[0]; 
		for (int i = 1; i < n; ++i){
			llcl[i] = (llcl[i - 1]>0) ? nums[i] + llcl[i-1] : nums[i]; 
			lgbl[i] = max(lgbl[i - 1], llcl[i]); 
		}
		prt1Layer(lgbl); 

		rlcl[n-1] = nums[n-1], rgbl[n-1] = nums[n-1]; 
		for (int i = n-2; i>=0; --i){
			rlcl[i] = (rlcl[i + 1] > 0) ? rlcl[i + 1] + nums[i] : nums[i]; 
			rgbl[i] = max(rgbl[i + 1], rlcl[i]); 
		}
		prt1Layer(rgbl); 

		int res = lgbl[0]; 
		for (int i = 0; i < n - 1; ++i){
			res = max(res, lgbl[i] + rgbl[i + 1]); 
		}

		return res; 
	}
};

class Solution2 {
public:
	int twoSubarray(vector<int>& nums) {
		int left = nums[0], right = nums.back(); 
		int n = nums.size(); 
		vector<int> lglobal(n, 0), rglobal = lglobal; 
		lglobal[0] = nums[0]; 
		for (int i = 1; i < nums.size(); ++i){
			if (left >= 0)
				left += nums[i];
			else
				left = nums[i]; 

			lglobal[i] = max(left, lglobal[i - 1]); 
		}
	}
}; 


int main(){
	Solution a; 

	vector<int> b = { 2, 4, -3, 7, -3, 4, 0 }; 

	cout << a.twoSubarray(b) << endl; 




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

