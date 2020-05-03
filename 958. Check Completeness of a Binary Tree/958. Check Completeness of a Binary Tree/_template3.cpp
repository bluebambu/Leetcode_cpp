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

// pass, 32%
class Solution {
public:
    bool isCompleteTree(TreeNode* root) {
		return check(root).at(1) != -1; 
    }

	vector<int> check(TreeNode *node){
		if (!node) return{ 0, 0 }; 
		vector<int> left = check(node->left), right = check(node->right); 
		int total = 1 + left[0] + right[0]; 
		if (left[1] == -1 || right[1] == -1) return{ 0, -1 }; 
		if (left[1]<right[1] || left[1]>right[1] + 1) return{ 0, -1 }; 

		if (left[1] == right[1]){
			if (left[0] != pow(2, left[1]) - 1) return{ 0, -1 }; 
			else return{ total, left[1]+1 }; 
		}
		if (left[1] == right[1] + 1){
			if (right[0] != pow(2, right[1]) - 1) return{ 0, -1 }; 
			else return{ total, left[1]+1 }; 
		}
	}
};

// 4ms, 100%
class Solution {
public:
	bool isCompleteTree(TreeNode* root) {
		queue<TreeNode*> q; 
		q.push(root); 
		while (q.front() != nullptr){
			TreeNode *f = q.front(); 
			q.pop(); 
			q.push(f->left); 
			q.push(f->right );
		}
		while (!q.empty()){
			if (q.front() != nullptr) return false; 
			q.pop(); 
		}
		return true; 
	}
};


int main(){
	Solution a;

	vector<int> b = { 4, 1, -9, 0, INT_MAX };


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1, new TreeNode(9), nullptr),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/


	cout << a.isCompleteTree(tree) << endl; 

	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}

