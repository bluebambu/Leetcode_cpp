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
	int splitArray(vector<int>& nums) {
		int sum = 0;
		for (auto n : nums) sum += n; 

		int target = sum / 2; 

		vector<bool> dp(target + 1, false); 
		dp[0] = true; 

		for (int i = 0; i < nums.size(); ++i){
			for (int j = target; j >= nums[i]; --j){
				dp[j] = dp[j] || dp[j - nums[i]]; 
			}
		}

		for (int i = target; i >= 0; --i){
			if (dp[i])
				return i; 
		}

		return -1; 
	}
};

class Solution2{
public:
	int split(vector<int> nums){
		int negSum = 0, sum = 0, possum=0; 
		for (auto n : nums) {
			sum += n; 
			if (n < 0) negSum += n; 
			else possum += n; 
		}

		int offset = -negSum; 

		int target = sum / 2; 
		int n = nums.size(); 
		vector<vector<bool>> dp(n + 1, vector<bool>(possum + offset + 1, false)); 
		dp[0][offset] = true; 

		for (int i = 1; i<=n; ++i){
			int cur = nums[i-1]; 
			for (int j = 0; j <= possum+offset; ++j){
				if (j-cur >= 0 && j - cur <= possum + offset)
					dp[i][j] = dp[i - 1][j] || dp[i - 1][j - cur];
				else
					dp[i][j] = dp[i - 1][j]; 
			}
			prt2Layer(dp); 
		}
		
		for (int i = 0; i < dp[0].size(); ++i)
			cout << i%10 << " "; 
		cout << endl; 
		cout << "sum: " << sum << endl; 
		cout << "posSum: " << possum  << "  negSum: " << negSum << endl;;
		cout << "target: " << target + offset << endl; 

		return dp.back()[target + offset]; 
	}
};



int main(){
	Solution2 a;

	vector<int> b = { -6, -7, 8, 9, 10 };

	cout << a.split(b) << endl;;


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

