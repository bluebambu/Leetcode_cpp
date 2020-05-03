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
	void qsort(vector<int>& nums) {
		qsort(nums, 0, nums.size());
	}

	void qsort(vector<int>& nums, int l, int r){
		if (l + 1 >= r)
			return; 

		int pivot = nums[l],
			i = l + 1, j = r;
		while (i < j){
			while (i < j && nums[i] <= pivot) ++i; 
			while (i < j && nums[j - 1] >= pivot) --j; 
			if (i==j)
				break;;

			swap(nums[i], nums[j - 1]); 
		}

		swap(nums[l], nums[i - 1]); 

		qsort(nums, l, i); 
		qsort(nums, i + 1, r);
	} 


	void merge(vector<in>& nums){
		merge(nums, 0, nums.size()); 
	}
	void merge(vector<int>& nums, int l, int r){
		if (l + 1 >= r)
			return; 

		int mid = l + (r - l) / 2; 
		merge(nums, l, mid); 
		merge(nums, mid, r); 

		vector<int>& copy = nums; 
		int i = l, j = mid; 
		int k = 0; 
		while(k<r){
			;
		}
	}


	void raddix(vector<int>& nums){

	}
};

class Solution2 {
public:
	void qsort(vector<int>& nums) {
		qsort(nums, 0, nums.size()); 
	}
	void qsort(vector<int>& nums, int i, int j){
		//[i, j)
		if (i >= j) return; 
		int pivot = nums[i]; 
		int ii = i + 1, jj = j; 
		while (1){
			while (ii < jj && nums[ii] < pivot) ++ii; 
			while (ii<jj && nums[jj - 1]>pivot) --jj; 
			if (ii == jj) break;;

			swap(nums[ii], nums[jj]); 
		}
		swap(nums[i], nums[jj - 1]); 
		qsort(nums, i, jj); 
		qsort(nums, jj+1, j); 
	}
};


int main(){
	Solution a;

	vector<int> b = { 4, 1, -9, 0, 8 };
	vector<int> b2 = { 4 };

	a.qsort(b); 
	a.qsort(b2); 

	prt1Layer(b); 
	prt1Layer(b2); 


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

