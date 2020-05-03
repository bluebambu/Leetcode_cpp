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
	struct node{
		unordered_map<node*, int> child; 
	};
	int raindrops(vector<vector<int>>& plates, int pos) {
		sort(plates.begin(), plates.end(), [](vector<int>&a, vector<int>&b){
			return a[1] > b[1]; 
		}); 
		node* root = build(plates, 0, pos); 

		return minLen(root); 
	}
	node *build(vector<vector<int>>& plates, int i, int pos){
		cout << i << " "; 
		if (i == plates.size()) return new node; 
		int x = plates[i][0],
			y = plates[i][1],
			len = plates[i][2],
			x2 = x + len, 
			leftWeight = pos-x, 
			rightWehght = x2-pos; 

		node *cur = new node; 
		for (int j = i + 1; j < plates.size(); ++j){
			if (plates[j][0]<x && plates[j][0] + plates[j][1]>x){
				node *child1 = build(plates, j, x); 
				cur->child[child1] = leftWeight; 
				break;
			}
		}

		for (int j = i + 1; j < plates.size(); ++j){
			if (plates[j][0]<x2 && plates[j][0] + plates[j][1]>x2){
				node *child2 = build(plates, j, x2); 
				cur->child[child2] = rightWehght; 
				break;
			}
		}

		if (cur->child.empty()){
			cur->child[nullptr] = min(leftWeight, rightWehght); 
		}

		cout << endl; 
		return cur; 
	}
	int minLen(node* root){
		if (!root) return 0; 
		int res = INT_MAX; 
		for (auto& p : root->child){
			int curweight = p.second; 
			res = min(res, curweight + minLen(p.first)); 
		}

		return res; 
	}
};



int main(){
	Solution a;

	VVI plates = {
		{ 5, 5, 4 },// 5-9
		{ 3, 4, 3 },//3-6
		{ 7, 3, 4 }, //7-11
		{ 1, 2, 3 }, //1-4
	}; 

	cout << a.raindrops(plates, 6) << endl; 

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

