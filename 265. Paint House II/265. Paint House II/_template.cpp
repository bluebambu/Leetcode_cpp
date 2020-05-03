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


// 这道题是之前那道Paint House的拓展，那道题只让用红绿蓝三种颜色来粉刷房子，
// 而这道题让我们用k种颜色，这道题不能用之前那题的解法，会TLE。这题的解法的
// 思路还是用DP，但是在找不同颜色的最小值不是遍历所有不同颜色，而是用min1和
// min2来记录之前房子的最小和第二小的花费的颜色，如果当前房子颜色和min1相同，
// 那么我们用min2对应的值计算，反之我们用min1对应的值，这种解法实际上也包含了
// 求次小值的方法，感觉也是一种很棒的解题思路，参见代码如下：


// passed
// 求最小的两个值： 
// 		min1, min2要预先设成-1， -1. 我一开始都设成0， 0 或者 0， 1， 都会出问题
// 			0，0 问题是 如果dp[i][0]就是最小的， 那min2 找不到第二小的了
// 			0，1 问题是 需要单独处理 Size==1 的dp
// 		另一个要注意的点是， 一旦找到min1， 需要写 min2 = min1. 切记。 
//
class Solution
{
public:
	int minCostII(vector<vector<int>>& costs) {
		if (costs.empty() || costs[0].empty())
			return 0; 
		int nhouse = costs.size(), ncol = costs[0].size(); 
		vector<vector<int>> dp = costs; 
		int min1 = -1, min2 = -1;
		for (int i = 0; i < nhouse; ++i){
			int last1 = min1, last2 = min2; 
			min1 = -1, min2 = -1;
			for (int j = 0; j < ncol; ++j){
				if (i > 0){
					if (j != last1)
						dp[i][j] += dp[i - 1][last1];
					else
						dp[i][j] += dp[i - 1][last2]; 
				}
				if (min1 < 0 || dp[i][j] < dp[i][min1]){
					min2 = min1; 
					min1 = j; 
				}
				else if (min2 < 0 || dp[i][j] < dp[i][min2])
					min2 = j; 
			}
		}
		return dp.back()[min1];
	}

};



class Solution2 {
public:
	int minCostII(vector<vector<int>>& costs) {
		if (costs.empty() || costs[0].empty())
			return 0;
		int nhouse = costs.size(), ncol = costs[0].size();
		
		int min1=0, min2=0, lastColor=-1; 

		for (int i = 0; i < nhouse; ++i){
			int lastmin1 = min1, lastmin2 = min2, curMinColor; 
			min1 = INT_MAX, min2 = INT_MAX; 
			for (int j = 0; j < ncol; ++j){
				int curCost = (j == lastColor ? costs[i][j] + lastmin2 : costs[i][j] + lastmin1); 
				if (curCost < min1){
					min2 = min1; 
					min1 = curCost; 
					curMinColor = j; 
				}
				else if (curCost < min2)
					min2 = curCost; 
			}
			lastColor = curMinColor; 
		}
		return min1; 
	}
};


int main() {
	Solution2 a;

	vector<vector<int>> b = {
		{ 4, 16 },
		{ 15, 5 },
		{ 18, 17 },
		{ 10, 12 },
		{ 14, 10 },
		{ 3, 10 },
		{ 2, 11 },
		{ 18, 14 },
		{ 9, 1 },
		{ 14, 13 }
	};

	cout << a.minCostII(b) << endl; 


	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/

}

