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
typedef vector<vector<int>> VII; 


class Solution {
public:
	double diameter(vector<vector<int>> vertices){
		int n = vertices.size(); 
		if (n < 2) return 0; 
		if (n == 2) return dist(vertices[0], vertices[1]); 
		int j = 2; 
		int res = dist(vertices[0], vertices[1]); 
		for (int i = 0; i < n; ++i){
			int next = (i + 1) % n; 
			while (cross_prod(vertices, i, next, j) < cross_prod(vertices, i, next, (j + 1) % n))
				j = (j + 1) % n; 

			res = max(res, max(dist(vertices[i], vertices[j]), dist(vertices[next], vertices[j]))); 
		}
		return res;
	}

	double dist(VI& a, VI& b){
		return sqrt((b[1] - a[1])*(b[1] - a[1]) + (b[0] - a[0])*(b[0] - a[0])); 
	}

	int cross_prod(VII& v, int i, int j, int k){
		VI ki = { v[i][0] - v[k][0], v[i][1] - v[k][1] },
			kj = { v[j][0] - v[k][0], v[j][1] - v[k][1] }; 

		return abs(ki[0] * kj[1] - ki[1] * kj[0]); 
	}

};


class Solution2 {
public:
	double diameter(vector<vector<int>> vertices){
		int n = vertices.size(); 
		int res = INT_MIN; 
		for (int i = 0; i < n; ++i){
			int j = (i + 1) % n; 
			int k = (j + 1) % n; 
			while (cross_prod(vertices, i, j, k) < cross_prod(vertices, i, j, (k + 1) % n)){
				k = (k + 1) % n; 
			}

			res = max(res, max(dist(vertices, i, k), dist(vertices, j, k))); 
		}
		return res; 
	}

	double dist(VI& a, VI& b){
		return sqrt((b[1] - a[1])*(b[1] - a[1]) + (b[0] - a[0])*(b[0] - a[0])); 
	}

	int cross_prod(VII& v, int i, int j, int k){
		VI ki = { v[i][0] - v[k][0], v[i][1] - v[k][1] },
			kj = { v[j][0] - v[k][0], v[j][1] - v[k][1] }; 

		return abs(ki[0] * kj[1] - ki[1] * kj[0]); 
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

