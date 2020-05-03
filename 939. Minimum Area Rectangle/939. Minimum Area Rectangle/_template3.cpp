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

// pass
class Solution {
public:
	int minAreaRect(vector<vector<int>>& points) {
		unordered_map<int, unordered_map<int, int>> recs; 
		for (auto& point : points){
			recs[point[0]][point[1]] = 1; 
		}

		int res = INT_MAX;
		for (int i = 0; i < points.size(); ++i){
			for (int j = i + 1; j < points.size(); ++j){
				int x1 = points[i][0], y1 = points[i][1],
					x2 = points[j][0], y2 = points[j][1]; 

				if (x1!=x2 && y1!=y2 && recs[x1][y2] && recs[x2][y1]){
					res = min(res, abs(y2 - y1)*abs(x2 - x1));
				}
			}
		}

		return res == INT_MAX ? 0 : res; 
	}
};

// pass
class Solution2 {
public:
	int minAreaRect(vector<vector<int>>& points) {
		unordered_map<int, unordered_map<int, int>> g; 
		for (auto& p : points){
			g[p.first][p.second] = 1; 
		}

		int res = INT_MAX; 
		int n = points.size(); 
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				int x1 = points[i][0], y1 = points[i][1], x2 = points[j][0], y2 = points[j][1]; 
				if (x1 == x2 || y1 == y2) continue;
				if (x1<x2 && y1>y2 && g[x1][y2] && g[x2][y1] && (x2 - x1)*(y1 - y2) < res)
					res = (x2 - x1)*(y1 - y2); 
			}
		}
		return res; 
	}
}; 


int main(){
	Solution a;

	VVI b = { { 1, 1 }, { 1, 3 }, { 3, 1 }, { 3, 3 }, { 2, 2 } }; 

	cout << a.minAreaRect(b) << endl; 


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

