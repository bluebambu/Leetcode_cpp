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

typedef pair<int, int> PII;
typedef vector<vector<int>> VII; 

class Solution {
public:
	bool isConvex(vector<vector<int>>& points) {
		if (points.empty())
			return false; 

		int n = points.size(); 
		long long lastProd = 0;
		for (int i = 0; i < n; ++i){
			int preI = (i - 1 + n) % n, postI = (i + 1) % n; 
			PII pre = { points[i][0] - points[preI][0], points[i][1] - points[preI][1] },
				post = { points[postI][0] - points[i][0], points[postI][1] - points[i][1] };
			long long X = pre.first*post.second - pre.second*post.first; 
			cout << X << endl; 
			if (X == 0)
				continue;
			else if (lastProd == 0)
				lastProd = X;
			else if (lastProd * X < 0)
				return false;
			else
				lastProd = X; 
		}

		return true; 
	}
};


class Solution2 {
public:
	bool isConvex(vector<vector<int>>& points) {
		int n = points.size(); 
		long long lastcross = 0; 
		for (int i = 0; i < n; ++i){
			int j = (i + 1) % n, k = (j + 1) % n; 
			vector<int> prevec = { points[j][0] - points[i][0], points[j][1] - points[i][1] },
			curvec = { points[k][0] - points[j][0], points[k][1] - points[j][1] }; 

			long long crossprod = cross(prevec, curvec); 

			if (crossprod == 0)
				continue;
			else if (lastcross == 0)
				lastcross = crossprod; 
			else if (crossprod * lastcross < 0)
				return false;
			else
				lastcross = crossprod; 
		}

		return true; 
	}

	int cross(vector<int>& a, vector<int>& b){
		return a[0] * b[1] - a[1] * b[0]; 
	}
};

class Solution3 {
public:
	bool isConvex(vector<vector<int>>& points) {
		int n = points.size(); 
		long long pre_cross = INT_MAX;
		for (int i = 0; i < n; ++i){
			int nxt = (i + 1) % n,
				prev = (i + n - 1) % n; 
			vector<int> pvec = { points[i][0] - points[prev][0], points[i][1] - points[prev][1] },
				nvec = { points[nxt][0] - points[i][0], points[nxt][1] - points[i][1] };

			long long cross = nvec[0] * pvec[1] - nvec[1] * pvec[0]; 
			if (cross == 0)
				continue;
			if (pre_cross == INT_MAX){
				pre_cross = cross; 
				continue;
			}
			if (pre_cross * cross < 0)
				return false; 
			pre_cross = cross; 
		}

		return true; 
	}
}; 

class Solution4 {
public:
	bool isConvex(vector<vector<int>>& points) {
		
	}
};




int main(){
	Solution a; 
	Solution3 a2; 

	VII  b = { { 0, 0 }, { 1, 1 }, { 0, 2 }, { -1, 2 }, { -1, 1 } }; 

	// overflow integer 
	VII  c = {{0,1907},{6,952},{12,29},{376,23},{1217,10},{2622,2},{9260,5},{9729,33},{9977,111},{9995,3692},{9984,8244},{9963,9092},{9941,9740},{9915,9966},{9754,9992},{9665,9999},{808,9997},{201,9966},{93,9928},{4,9247},{2,7152},{0,4926}}; 

	cout << a.isConvex(c) << endl; 
	cout << endl << endl; 
	cout << a2.isConvex(c) << endl; 


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

