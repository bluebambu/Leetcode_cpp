// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
#include <functional>
#include <bitset>
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

vector<vector<int>> dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 

class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
		if (!t1 && !t2)
			return nullptr; 

		TreeNode *newn = new TreeNode(0); 
		if (!t1 || !t2){
			if (t1){
				newn->val = t1->val; 
				newn->left = mergeTrees(t1->left, nullptr); 
				newn->right = mergeTrees(t1->right, nullptr); 
				return newn; 
			}
			else{
				newn->val = t2->val; 
				newn->left = mergeTrees(nullptr, t2->left); 
				newn->right = mergeTrees(nullptr, t2->right); 
				return newn; 
			}
		}

		newn->val = t1->val + t2->val; 
		newn->left = mergeTrees(t1->left, t2->left); 
		newn->right = mergeTrees(t1->right, t2->right); 
		return newn; 
    }
};


class Solution2 {
public:
	TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
		if (!t1 && !t2)
			return nullptr; 
		if (!t1 || !t2){
			return t1 ? t1 : t2; 
		}

		t1->val += t2->val; 
		t1->left = mergeTrees(t1->left, t2->left); 
		t1->right = mergeTrees(t1->right, t2->right); 
		return t1; 
	}
}; 



class Solution3 {
public:
	TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
		if (!t1 && !t2)
			return nullptr; 
		if (!t1 || !t2)
			return t1 ? t1 : t2; 
		
		t1->val += t2->val; 
		t1->left = mergeTrees(t1->left, t2->left); 
		t1->right = mergeTrees(t1->right, t2->right); 
		return t1; 
	}
}; 

int main(){
	Solution a;

	vector<int> b = { 4, 1, -9, 0, INT_MAX };


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




