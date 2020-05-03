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
	int removeStones(vector<vector<int>>& stones) {
		if (stones.empty())
			return 0; 

		int n = stones.size(); 
		vector<int> root(n, 0); 
		for (int i = 0; i < n; ++i)
			root[i] = i; 

		int cnt = 0; 
		unordered_map<int, unordered_set<int>> rows, cols; 
		for (int i = 0; i < n; ++i){
			int x = stones[i][0], y = stones[i][1]; 
			++cnt; 
			if (rows.count(x)){
				for (int other : rows[x]){
					unify(root, other, i, cnt); 
				}
			}
			if (cols.count(y)){
				for (int other : cols[y]){
					unify(root, other, i, cnt); 
				}
			}
			rows[x].insert(i); 
			cols[y].insert(i); 
		}

		return n-cnt; 
	}

	void unify(vector<int>& root, int o, int i, int& cnt){
		int ro = find(root, o); 
		if (ro == i)
			return; 

		root[ro] = i; 
		--cnt; 
	}

	int find(vector<int>& root, int i){
		while (i != root[i])
			i = root[i]; 
		return i; 
	}
};

int main(){
	Solution a;

	VVI b = { { 0, 0 }, { 0, 1 }, { 1, 0 }, { 1, 2 }, { 2, 1 }, { 2, 2 } }; 
	VVI b2 = { { 0, 1 }, { 1, 0 } };

	cout << a.removeStones(b2) << endl; 


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

