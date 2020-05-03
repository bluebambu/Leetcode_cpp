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


// nlgn solution
class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		vector<int> incVec; 

		for (int i = 0; i < nums.size(); ++i){
			int cur = nums[i]; 
			auto it = lower_bound(incVec.begin(), incVec.end(), cur); 
			if (it == incVec.end())
				incVec.push_back(cur);
			else
				*it = cur; 
		}

		return incVec.size(); 
	}
};

class Solution2 {
public:
	vector<int> lengthOfLIS(vector<int>& nums) {
		int n = nums.size(); 
		vector<int> dp(n, 1), parent(n, 0); 
		for (int i = 0; i < n; ++i)
			parent[i] = i; 

		int head = 0, max=0; 
		for (int i = 1; i < n; ++i){
			for (int j = i - 1; j >= 0; --j){
				if (nums[i] > nums[j]){
					if (dp[j] + 1 > dp[i]){
						dp[i] = dp[j] + 1; 
						parent[i] = j; 
						if (dp[i] > max){
							max = dp[i]; 
							head = i;
						}
					}
				}
			}
		}

		vector<int> res; 
		while (head != parent[head]){
			res.push_back(nums[head]); 
			head = parent[head]; 
		}
		res.push_back(nums[head]); 

		prt1Layer(dp); 

		return res; 
	}
}; 



int main(){
	Solution2 a; 

	vector<int> b = { 1, 4, 6, 2, 8, 5, 9, 4, 2, 6 }; 

	auto c = a.lengthOfLIS(b); 

	prt1Layer(c); 


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

