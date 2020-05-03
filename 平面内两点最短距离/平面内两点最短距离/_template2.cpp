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
	int shortest(VVI& pts){
		sort(pts.begin(), pts.end(), [](VI& a, VI&b){
			return a[0] < b[0]; 
		}); 

		int n = pts.size(); 
		return divide(pts, 0, n - 1); 
	}

	int divide(VVI& pts, int l, int r){
		if (l == r)
			return INT_MAX; 
		if (l + 1 == r)
			return dist(pts[l], pts[r]); 
		
		int n = pts.size(); 
		int lv = pts[l][0], rv = pts[r][0], mid = lv + (rv - lv) / 2; 
		int lboundary = 0;
		for (int i = 0; i < n; ++i){
			if (pts[i][0] <= mid)
				lboundary = i; 
			else
				break;
		}

		int lmin = divide(pts, l, lboundary), rmin = divide(pts, lboundary, r), d = min(lmin, rmin); 

		VVI midVec; 
		for (int i = 0; i < n; ++i){
			if (pts[i][0] <= mid + d / 2 && pts[i][0] >= mid - d / 2)
				midVec.push_back(pts[i]); 
		}

		sort(midVec.begin(), midVec.end(), [](VI& a, VI& b){
			return a[1] < b[1]; 
		}); 
		
		int midmin = INT_MAX; 
		for (int i = 0; i < midVec.size(); ++i){
			for (int j = 1; j < 7 && i + j < midVec.size(); ++j){ // neighbour 8 points compare
				midmin = min(midmin, dist(midVec[i], midVec[j])); 
			}
		}
		
		return min(midmin, d); 
	}

	int dist(VI& a, VI& b){
		return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2)); 
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

