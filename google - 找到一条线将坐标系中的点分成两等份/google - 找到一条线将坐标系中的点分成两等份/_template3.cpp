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

// not tested, shall be fine. 
class Solution {
public:
	int splitPoints(vector<vector<int>>& points){
		vector<int> mostLeft = points[0]; 
		for (auto& p : points)
			if (p[0] < mostLeft[0])
				mostLeft = p; 

		vector<double> slopes; 
		for (auto& p : points){
			if (p != mostLeft){
				slopes.push_back(double((p[1] - mostLeft[1]) / (p[0] - mostLeft[0]))); 
			}
		}
		
		double mid_slope = qs(slopes, slopes.size()/2);
		return{ mid_slope, mostLeft[1] - mid_slope*mostLeft[0] }; 
	}

	double qs(vector<double>& nums, int k){
		int left = 0, right = nums.size()-1; 
		while (left < right){
			int r = rk(nums, left, right); 
			if (r == k - 1) return nums[r]; 
			else if (r>k - 1)	right = r; 
			else left = r; 
		}
		return -1.0; 
	}

	int rk(vector<double>& nums, int l, int r){
		double pivot = nums[l]; 
		int i = l + 1, j = r; 
		while (1){
			for (i <= j && nums[i] <= pivot) ++i; 
			for (i <= j && nums[j] >= pivot) ++j; 
			if (i==j)
				break;

			swap(nums[i], nums[j]); 
		}
		swap(nums[l], nums[i - 1]); 
		return i - 1; 
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

