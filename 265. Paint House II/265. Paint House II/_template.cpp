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


// �������֮ǰ�ǵ�Paint House����չ���ǵ���ֻ���ú�����������ɫ����ˢ���ӣ�
// ���������������k����ɫ������ⲻ����֮ǰ����Ľⷨ����TLE������Ľⷨ��
// ˼·������DP���������Ҳ�ͬ��ɫ����Сֵ���Ǳ������в�ͬ��ɫ��������min1��
// min2����¼֮ǰ���ӵ���С�͵ڶ�С�Ļ��ѵ���ɫ�������ǰ������ɫ��min1��ͬ��
// ��ô������min2��Ӧ��ֵ���㣬��֮������min1��Ӧ��ֵ�����ֽⷨʵ����Ҳ������
// ���Сֵ�ķ������о�Ҳ��һ�ֺܰ��Ľ���˼·���μ��������£�


// passed
// ����С������ֵ�� 
// 		min1, min2ҪԤ�����-1�� -1. ��һ��ʼ�����0�� 0 ���� 0�� 1�� ���������
// 			0��0 ������ ���dp[i][0]������С�ģ� ��min2 �Ҳ����ڶ�С����
// 			0��1 ������ ��Ҫ�������� Size==1 ��dp
// 		��һ��Ҫע��ĵ��ǣ� һ���ҵ�min1�� ��Ҫд min2 = min1. �мǡ� 
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

