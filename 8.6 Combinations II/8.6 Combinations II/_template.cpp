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

/*
����˼�룺 
	ÿһ��������block�� ���� ...2,2,2... ֻȡ��һ��2�� �������һ��2�� ����ض��Թ�ȥ�� �������ܼ�� ��2���� ��2��2���� ��2��2��2�� �������������Ϊÿ����ͬ��λ�õ�2����������1�Σ��� �ֲ�������ظ���������  
*/
class Solution
{
public:
	vector<vector<int>> comb(vector<int>& s){
		sort(s.begin(), s.end());
		vector<vector<int>> res; 
		vector<int> path; 
		dfs(s, 0, path, res); 
		return res; 
	}

	void dfs(vector<int>& s, int cur, vector<int>& path, vector<vector<int>>& res){
		if (path.size() == 3){
			res.push_back(path); 
			return;
		} 

		for (int i = cur; i < s.size(); ++i){
// 			while (i>cur && i<s.size() && s[i] == s[i - 1]) ++i; 
// 			if (i == s.size())
// 				break; 
			path.push_back(s[i]); 
			dfs(s, i + 1, path, res); 
			path.pop_back(); 
			while (i+1<s.size() && s[i] == s[i + 1]) ++i;  // д�ں����Ҫ��һ��condition�� ǰ��Ļ�����  i>cur && i<s.size() && s[i] == s[i - 1]
			
		}
	}

};

/*
Iteration ?? 
*/
class Solution2{
public:
	vector<vector<int>> comb(vector<int>& s){

	}
};

int main()
{
	Solution a;

	vector<int> b{ 1, 2, 2, 2 };

	auto c = a.comb(b);

	for (auto i : c){
		for (auto j : i)
			cout << j << " ";
		cout << endl;
	}


}

