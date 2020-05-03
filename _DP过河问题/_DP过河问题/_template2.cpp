// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
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
// ������6����һ��ҹ�ڷ�ߵ����ϣ���n��n <= 50����С�������ŵ���ߣ�����������Ҫ���ţ����������ź�խ��
// ÿ��ֻ������������ͨ��������ֻ��һ���ֵ�Ͳ������ÿ�ι��ŵ���������Ҫ���ֵ�Ͳ��������i��С���ѹ��ŵ�ʱ��ΪT[i]��
// �����˹��ŵ���ʱ��Ϊ������ʱ�䳤�ߡ�������С���ѹ��ŵ���ʱ������Ƕ��١�

// һ�����Ӷȵ�Ԥ�о���: n<20 -> n^3 ; n = 30-50 -> n^2; n = 100 - 200�� nlogn; n>1000, n; �Դ�����


class Solution {
public:
	int crossRiver(vector<int>& T){
		// 1. dp[n] = dp[n-2] + time(T[n-1] & T[n])
		// 2. time( T[n-1] & T[n] ) = min( T[n-1]+T[n]+2T[1], T[n] + 2T[2] + T[1]); 
		int n = T.size(); 

		vector<int> dp(n, 0); 
		sort(T.begin(), T.end()); 

		for (int i = 0; i < n; ++i){
			if (i == 0)
				dp[i] = T[i]; 
			else if (i == 1)
				dp[i] = min(T[0], T[1]);
			else if (i == 2)
				dp[i] = T[2] + T[1] + T[0]; 
			else{
				dp[i] = dp[i - 2] + min(T[i] + T[i - 1] + 2T[0], T[i] + 2T[1] + T[0]); 
			}
		}

		return dp[n - 1]; 
	}
};
class Solution_op {
public:
	int crossRiver(vector<int>& T){
		int n = T.size(); 

		int odd = 0, even = 0; 
		for (int i = 0; i < n; ++i){
			
		}
	}
};








int main(){
	Solution a;

	vector<int> b = { 7, 2, 5, 10, INT_MAX };


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

