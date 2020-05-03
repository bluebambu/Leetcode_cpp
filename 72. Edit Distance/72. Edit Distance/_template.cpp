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


// passed
//
// "a"
// "ab"
// ���������һ�������Ļ���Ԫ�� ���ֻ�����������ĸ�� ����ֻ�� a change to b�� ��steps = 2�� ��Ϊ "" "a" ��steps ��1. ��ʵ��
// ������Ĵ���1.������ΪӦ�ñȽ� word1[i] �� word2[j - 1]�� Ȼ����� dp[i][j - 1] == 0 �� ���� dp[i][j] = dp[i][j-1] + 1 =1�� 
// ��˶���ÿһ�� dp[i][j], ��Ӧ�ñȽ�   dp[i][j - 1],dp[i - 1][j], dp[i - 1][j - 1] �� �ҵ���Сֵ�� �ټ� 1. 

class Solution
{
public:
	int minDistance(string word1, string word2) {
		int n = word1.size(), m = word2.size(); 
		vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
		for (int i = 0; i < n + 1; ++i)
			dp[i][0] = i; 
		for (int j = 0; j < m + 1; ++j)
			dp[0][j] = j;

		for (int i = 1; i < n + 1; ++i){
			for (int j = 1; j < m + 1; ++j){
				if (word1[i-1] == word2[j-1])
					dp[i][j] = dp[i - 1][j - 1]; 
				else{
					dp[i][j] = 1 + min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1]));
				}
			}
		}
		return dp.back().back(); 
	}

};


// Ҫ�򻯣� ��2ά��1ά�� 


int main()
{
	Solution a;

	cout << a.minDistance("spartan", "part"); 


}

