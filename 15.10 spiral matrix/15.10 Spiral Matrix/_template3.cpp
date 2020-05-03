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
	void spiral(VVI& mtx){
		int n = mtx.size(), m = mtx[0].size(); 
		int l = 0, r = m - 1, u = 0, d = n - 1; 

		while (true){
			for (int j = l; j <= r; ++j)
				cout << mtx[u][j] << ' '; 
			++u; 
			if (u>d) break;

			for (int i = u; i <= d; ++i)
				cout << mtx[i][r] << ' '; 
			--r; 
			if (r<l) break;

			for (int j = r; j >= l; --j)
				cout << mtx[d][j] << ' '; 
			--d; 
			if (u>d) break;

			for (int i = d; i >= u; --i)
				cout << mtx[i][l] << ' '; 
			++l; 
			if (r<l) break;
		}
		cout << endl;
	}
};


class Solution2 {
public:
	void spiral(VVI& mtx){
		int n = mtx.size(), m = mtx[0].size(); 
		int tot = n*m; 
		int lb = 0, rb = m - 1, ub = 0, bb = n - 1; 
		int i = 1; 

		while (1){
			for (int j = lb; j <= rb; ++j)
				mtx[ub][j] = i++; 
			++ub; 
			if (ub>bb) break;

			for (int k = ub; k <= bb; ++k)
				mtx[k][rb] = i++; 
			--rb; 
			if (lb>rb) break;

			for (int j = rb; j >= lb; --j)
				mtx[bb][j] = i++; 
			--bb; 
			if (ub>bb) break;

			for (int k = bb; k >= ub; --k)
				mtx[k][lb] = i++; 
			++lb; 
			if (lb>rb) break;
		}
	}
};



int main(){
	Solution2 a;

	vector<int> b = { 4, 1, -9, 0, INT_MAX };

	VVI c = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
	}; 

	VVI c2 = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 },
		{ 7, 8, 9 },
		{ 7, 8, 9 },
	}; 
	VVI c3 = {
		{ 1, 2, 3 }
	}; 
	a.spiral(c); 
	a.spiral(c2); 
	a.spiral(c3); 

	prt2Layer(c); 
	prt2Layer(c2); 
	prt2Layer(c3); 

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

