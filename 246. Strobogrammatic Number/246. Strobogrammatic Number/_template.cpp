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


struct TreeNode {
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


class Solution {
public:
	bool isStrobogrammatic(string num) {
		if (num.empty())
			return false; 
		int i = 0, j = num.size() - 1; 

		while (i <= j){
			if (stro(num[i]) != num[j])
				return false;
			++i, --j; 
		}
		return true; 
	}

	char stro(char c){
		switch (c){
		case '0': return '0'; 
		case '1': return '1'; 
		case '6': return '9'; 
		case '8': return '8'; 
		case '9': return '6';
		default: return 'a'; 	 // single number such as '2' is tested as false !!! 
		}
		return c; 
	}
};


class Solution2 {
public:
	bool isStrobogrammatic(string num) {	
		int i = 0, j = num.size() - 1; 
		for (; i <= j; ++i, --j){
			if (stro(num[i]) != num[j])
				return false; 
		}
		return true; 
	}

	char stro(char c){
		switch (c){
		case '1': return '1'; 
		case '0': return '0'; 
		case '6': return '9'; 
		case '9': return '6'; 
		case '8': return '8'; 
		default: return 0  ; 
		}
	}
}; 

int main()
{
	Solution2 a;

	cout << a.isStrobogrammatic("962") << endl; 

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/

	cout << a.isStrobogrammatic("2");


}

