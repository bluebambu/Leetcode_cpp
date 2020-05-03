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


struct TreeNode {
	TreeNode(int a) :val(a), left(nullptr), right(nullptr), rank(0) {}
	TreeNode(int a, TreeNode* x, TreeNode* y) :val(a), left(x), right(y), rank(0){}
	TreeNode() :val(0), left(nullptr), right(nullptr), rank(0){}

	int val;
	TreeNode *left;
	TreeNode *right;
	int rank; 
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


class oneDRange{
public:
	TreeNode* root; 
	oneDRange() :root(new TreeNode()) {}

	void insert(int i){
		root = insert(root, i, 0); 
	}
	TreeNode* insert(TreeNode* n, int i, int r){
		if (!n){
			TreeNode* tmp = new TreeNode(i); 
			tmp->rank = r; 
			return tmp; 
		}
	
		if (i == n->val)
			return n; 
		else if (i > n->val){
			n->right = insert(n->right, i, n->rank + 1); 
			return n; 
		}
		else{
			n->rank += 1; 
			n->left = insert(n->left, i, r); 
			return n; 
		}
	}

	int rank(int i){
		return rank(root, i, 0); 
	}

	int rank(TreeNode* n, int i, int r){
		if (!n)
			return r;
		
		if (i == n->val)
			return n->rank; 
		else if (i > n->val)
			return rank(n->right, i, n->rank + 1);
		else
			return rank(n->left, i, r); 
	}

	vector<TreeNode*> range(int low, int high){
		// ....	
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

