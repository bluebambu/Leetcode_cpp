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
// dir						lvl1
//     subdir1				lvl2
//         file1.ext		lvl3
//         subsubdir1
//     subdir2				lvl2
//         subsubdir2		lvl3
//             file2.ext	lvl4
//
//
//	用hashmap， 或者vector 来记录 lvl vs length。  lvl 用 \n 和 \t 来计算。 当遇到 '.'的时候， 更新 maxlength 
//
//	Caution: \n  & \t 都是 1 个char 不是2个char， string size == 1. 
//
class Solution {
public:
	int lengthLongestPath(string input) {
		int level = 1, res = 0;
		unordered_map<int, int> table;
		table[0] = 0;
		for (int i = 0; i < input.size(); ++i){
			int curstart = i;
			while (i < input.size() && input[i] != '\n' && input[i] != '\t') ++i;
			string curstr = input.substr(curstart, i - curstart);
			if (i == input.size() || input[i] == '\n'){
				table[level] = curstr.size() + table[level - 1] + 1;
				if (curstr.find('.') != string::npos){
					res = max(res, table[level]);
				}
				level = 1;
			}
			else if (input[i] == '\t')
				++level;
		}
		return res == 0 ? res : res - 1;
	}
};

int main()
{
	Solution a;

	cout << a.lengthLongestPath("dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext");


}

