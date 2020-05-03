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


// passed. 
// �߼��ǣ� �Ȳ� left�� �ٲ��ȥ��ǰ node����remaining count�ǲ���0�� �ٲ�right��  
class Solution {
public:
	int kthSmallest(TreeNode* root, int k) {
		return dfs(root, k);
	}
	int dfs(TreeNode* root, int &k) {
		if (!root)
			return -1;
		int left = dfs(root->left, k);
		if (k == 0)
			return left;

		--k;
		if (k == 0)	   
			// k ��ʣ��count��������ĳһ�㣬�ͻ�ʣk-1���㣬 k=0 �����ҵ��ˡ� 
			// ����Ҫ�� k--�� �����ж�
			return root->val;

		return dfs(root->right, k);
	}
};

int main()
{
	Solution a;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/

	TreeNode* t = new TreeNode(4); 

	cout << a.kthSmallest(t, 1); 


}

