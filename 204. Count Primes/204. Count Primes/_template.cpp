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
	int countPrimes(int n) {
		if (n < 2)
			return 0;

		vector<bool> prime(n, true);
		prime[0] = false; 
		prime[1] = false; 

		int sqrtn = sqrt(n); 
		for (int i = 2; i <= sqrtn; ++i){ // <= 必需！！
			if (prime[i]){
				for (int j = i*i; j < n; j += i)
					prime[j] = false; 
			}
		}

		int res = 0; 
		for (bool i : prime)
			if (i)
				++res; 
		return res; 
	}
};


class Solution2
{
public:
	int countPrimes(int n) {
		if (n < 2)
			return 0;

		vector<bool> prime(n, true);
		prime[0] = false;
		prime[1] = false;
		int res = 0;
		int sqrtn = sqrt(n);

		for (int i = 2; i < n; ++i){ 
			if (prime[i]){
				++res;

				if (i<=sqrtn)	// <= 必需！！
					for (int j = i*i; j < n; j += i)
						prime[j] = false;
			}
		}

		return res;
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

	a.flatten(tree);


}

