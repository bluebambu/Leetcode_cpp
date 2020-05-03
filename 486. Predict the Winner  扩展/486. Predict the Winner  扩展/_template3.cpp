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


class Solution6{
public:
	int PredictTheWinner(vector<int>& nums) {
		int n = nums.size();
		vector<vector<int>> dp(n, vector<int>(n, 0));
		for (int j = 0; j < n; ++j){
			for (int i = j; i >= 0; --i){
				if (i == j)
					dp[i][j] = nums[i];
				else if (i == j - 1)
					dp[i][j] = max(nums[i], nums[j]);
				else{
					int r1 = nums[i] + min(dp[i + 2][j], dp[i + 1][j - 1]),
						r2 = nums[j] + min(dp[i][j - 2], dp[i + 1][j - 1]);

					dp[i][j] = max(r1, r2);
				}
			}
		}

		prt2Layer(dp); 

		return dp[0][n - 1];
	}
};


int main(){
	Solution6 a;

	vector<int> b = { 1, 5, 2 };
	vector<int> b2 = { 0 };
	vector<int> b3 = { 1,6,4,8,3,9,0 };

	cout << a.PredictTheWinner(b3) << endl;
}



