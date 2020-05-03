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


// Morgan Stanley: find the deepest node of a tree

class Solution{
public:
	int	lvl(TreeNode* root){
		vector<TreeNode*> result;
		result.push_back(root);
		lvl(result);
		return result[0]->val;
	}
	void lvl(vector<TreeNode*>& result){
		vector<TreeNode*> tmp;
		for (int i = 0; i < result.size(); ++i){
			if (result[i]->left)
				tmp.push_back(result[i]->left);
			if (result[i]->right)
				tmp.push_back(result[i]->right);
		}

		if (tmp.empty())
			return;
		result = tmp;
		lvl(result);
	}
};


class Solution2{
public:
	int lvl(TreeNode* root){
		queue<TreeNode*> q;
		q.push(root);
		vector<TreeNode*> lvl;

		while (!q.empty()){
			lvl.clear();

			int n = q.size();
			for (int i = 0; i < n; ++i){
				TreeNode* tmp = q.front();
				q.pop();
				lvl.push_back(tmp);

				if (tmp->left)
					q.push(tmp->left);
				if (tmp->right)
					q.push(tmp->right);
			}
		}
		return lvl[0]->val;
	}
};


int main()
{
	Solution a;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1, new TreeNode(2), nullptr),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9
	2

	*/

	cout << a.lvl(tree);


}
