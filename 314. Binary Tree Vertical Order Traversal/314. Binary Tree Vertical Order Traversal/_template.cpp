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
#include <string> 
#include <unordered_set>
#include <set>
#include <map>
#include <utility>
#include <sstream>

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
			cout << j << "\t";
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

vector<vector<int>> dirs{ { 0, -1 }, { 0, 1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;
typedef vector<int> VI; 
typedef vector<vector<int>> VVI; 


/**
* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
* };
*/

// pass AC. 
class Solution {
public:
	vector<vector<int>> verticalOrder(TreeNode* root) {
		vector<vector<int>> res; 
		if (!root)
			return res; 

		map<int, vector<int>> m; 
		queue<pair<int, TreeNode*>> q; 
		q.push({ 0, root }); 

		while (q.size()){
			pair<int, TreeNode*> f = q.front(); 
			q.pop(); 
			
			m[f.first].push_back(f.first); 

			if (f.second->left)
				q.push({ f.first - 1, f.second->left }); 
			if (f.second->right)
				q.push({ f.first + 1, f.second->right }); 
		}

		for (auto a : m)
			res.push_back(a.second); 

		return res; 
	}
};


class Solution3 {
public:
	vector<vector<int>> vertical(TreeNode* root){
		vector<vector<int>> res(1); 
		queue<TreeNode*> q; 
		unordered_map<TreeNode*, int> node_id; 
		// [left, right] range
		int left = 0, right = 0;
		q.push(root); 
		node_id[root] = 0; 

		while (!q.empty()){
			TreeNode *f = q.front(); 
			q.pop(); 
			if (node_id[f] < left){
				left -= 1; 
				res.insert(res.begin(), {}); 
			}
			if (node_id[f] > right){
				right += 1; 
				res.push_back({}); 
			}
			res[node_id[f] - left].push_back(f->val); 

			if (f->left){
				node_id[f->left] = node_id[f] - 1; 
				q.push(f->left); 
			}
			if (f->right){
				node_id[f->right] = node_id[f] + 1; 
				q.push(f->right); 
			}
		}

		return res;
	}
}; 


int main() {
	Solution3 a;


	// TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
		3       8
	1    4   7    9
	*/

	prt2Layer(a.vertical(tree)); 

}

