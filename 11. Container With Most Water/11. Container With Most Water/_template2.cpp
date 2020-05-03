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
// Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water. 
// wrong ans!!!
class Solution {
public:
	int maxArea(vector<int>& height) {
		int left = 0, right = height.size() - 1; 
		int min_boundary = min(height[left], height[right]); 
		int res = 0; 

		while (left < right){
			res = max(res, (right - left)*min_boundary);
			if (height[left] < height[right]){
				++left; 
			}
			else if (height[left] > height[right]){
				--right; 
			}
			else{
				++left; 
				--right;
			}
		}
		return res; 
	}
};


class Solution2{
public:
	int maxArea(vector<int>& height){
		int left = 0, right = height.size() - 1; 
		int res = 0; 

		while (left < right){
			res = max(res, (right - left)*min(height[left], height[right])); 
			if (height[left] < height[right]){
				int j = left + 1; 
				while (height[j] <= height[left]) ++j; 
				left = j; 
			}
			else if (height[left] > height[right]){
				int j = right - 1; 
				while (height[j] <= height[right])--j; 
				right = j; 
			}
			else{
				++left, --right; 
			}
		}
		return res; 
	}
};


class Solution3{
public:
	int maxArea(vector<int>& hts){
		int l = 0, r = hts.size() - 1; 
		int res = INT_MIN; 

		while (l < r){
			res = max(res, (r - l)*min(hts[l], hts[r])); 

			bool leftIsMin = hts[l] < hts[r] ? true : false; 

			if (leftIsMin){
				int ll = l + 1; 
				while (ll < r && hts[ll] <= hts[l]) ++ll; 
				l = ll; 
			}
			else{
				int rr = r - 1; 
				while (rr > l && hts[rr] <= hts[r]) --rr; 
				r = rr; 
			}
		}

		return res; 
	}
};


int main(){
	Solution2 a; 
	Solution3 a2; 

	vector<int> b = { 4, 1, 9, 0, 5, 7, 2 }; 
	vector<int> b2 = {2, 4, 6, 90, 3, 4, 2, 1, 100}; 
	vector<int> b3 = {2, 5, 1, 8, 8, 1, 5, 2}; 

	cout << a.maxArea(b3) << endl; 
	cout << a2.maxArea(b3) << endl; 

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

