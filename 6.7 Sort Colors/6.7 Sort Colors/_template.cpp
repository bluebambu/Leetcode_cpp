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


class Solution
{
public:
	void sortcolor(vector<int>& v) {
		int red = 0, blue = v.size() - 1; 
		for (int white = 0; white <= blue;){
			if (v[white] == 0)
				swap(v[red++], v[white]); 
			if (v[white] == 2)
				swap(v[blue--], v[white]);
			if (white < red || v[white] == 1) // white<red 必需！！！
				++white; 
		}
	}

	void sortcolor2(vector<int>& vec){
		int i = 0, j = 0, idx = 0; 

		for (; i <vec.size();){
			for (j = i; j < vec.size(); ++j){  // 这里 j 必须从 i 开始！！ 
				if (vec[j] == idx)
					swap(vec[i++], vec[j]); 
			}

			++idx; 
		}
	}

	void sortcolor3(vector<int>& vec){
		int i = 0, j = 0, pivot = 0; 

	}

};

int main()
{
	Solution a;

	vector<int> bb = { 0, 0, 1, 1, 2, 2, 1, 0, 2, 1, 0 };

	a.sortcolor2(bb);

	for (auto i : bb)
		cout << i << " ";


}

