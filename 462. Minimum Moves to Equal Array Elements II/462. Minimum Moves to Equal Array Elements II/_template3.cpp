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
	int minMoves2(vector<int>& nums){
		int m = getMedian(nums); 
		int r = 0; 
		for (auto i : nums)
			r += abs(m - i); 
		return r; 
	}

	int getMedian(vector<int>& nums) {
		int n = nums.size(); 
		if (n % 2)
			return quickSelect(nums, n / 2);
		else
			return (quickSelect(nums, (n - 1) / 2) + quickSelect(nums, n / 2)) / 2; 
	}

	int quickSelect(vector<int>& nums, int k){
		int n = nums.size(); 
		return q(nums, 0, n - 1, k); 
	}

	int q(vector<int>& nums, int left, int right, int k){
		if (left == right)
			return nums[left]; 

		while (left < right){
			int r = rank(nums, left, right); 
			if (r == k)
				return nums[k];
			else if (r < k)
				left = r+1;
			else
				right = r-1; 
		}
		return nums[left]; 
	}

	int rank(vector<int>& nums, int i, int j){
		int pivot = nums[i]; 
		int ii = i + 1; 

		for (; ii <= j; ){
			if (nums[ii]>pivot){
				while (j >= ii && nums[j]>pivot) --j; 
				if (j == ii - 1){
					swap(nums[i], nums[ii - 1]); 
					return ii - 1; 
				}

				swap(nums[ii], nums[j]); 
				++ii, --j; 
			}
			else
				++ii; 
		}

		swap(nums[ii-1], nums[i]); 
		return ii - 1; 
	}
};




int main(){
	Solution a;

	vector<int> b = { 2, 6, 4, 9, 3, 1 }; 
	vector<int> bb = { 1, 3, 2 }; 
	vector<int> bbb = { 1, 1, 1, 3, 2 }; 

	cout << a.getMedian(bbb) << endl; 


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

