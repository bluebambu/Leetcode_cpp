// _template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <functional>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <set>
#include <unordered_set>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a < b ? a : b; }


struct TreeNode {
	TreeNode(int a, int b) :start(a), end(b), left(nullptr), right(nullptr) {}
	TreeNode(int a, int b, TreeNode* x, TreeNode* y) :start(a), end(b), left(x), right(y) {}
	TreeNode() :start(0), end(0), left(nullptr), right(nullptr) {}

	int start;
	int end;
	int max;
	int key;

	int val;
	TreeNode *left;
	TreeNode *right;
};



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
			cout << j << "\t";
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
				cout << front->key << " ";
				q.push(front->left);
				q.push(front->right);
			}
		}
		cout << endl;
	}
}


vector<vector<int>> dirs{ { 0, -1 }, { 0, 1 }, { 1, 0 }, { -1, 0 } };
typedef pair<int, int> PII;

class Solution {
public:
	bool isRectangleCover(vector<vector<int>>& rectangles) {
		vector<int> rd = { -1, -1 }, lu = rd, ld = rd, ru = rd;
		int n = rectangles.size();
		int tarea = 0;
		for (int i = 0; i < n; ++i){
			vector<int> crd = { rectangles[i][2], rectangles[i][3] },
				clu = { rectangles[i][0], rectangles[i][1] },
				cld = { rectangles[i][2], rectangles[i][1] },
				cru = { rectangles[i][0], rectangles[i][3] };
			if (crd > rd || rd[0] == -1)
				rd = crd;
			if (clu < lu || lu[0] == -1)
				lu = clu;
			if ((cld[0] >= ld[0] && cld[1] <= ld[1]) || ld[0] == -1)
				ld = cld;
			if ((cru[0] <= ru[0] && cru[1] >= ru[1]) || ru[0] == -1)
				ru = cru;

			tarea += (crd[0] - cru[0] + 1)*(crd[1] - cld[1] + 1);
		}

		return (rd[0] - ru[0] + 1)*(rd[1] - ld[1] + 1) == tarea;
	}
};


int low_bnd(vector<int>& nums, int target){
	int l = 0, r = nums.size();
	while (l + 1 < r){
		int mid = l + (r - l) / 2;
		if (nums[mid] < target)
			l = mid;
		else
			r = mid;
	}

	return r;
}


class QuickSelect{
public:
	int getKth(vector<int>& nums, int k){
		return qs(nums, 0, nums.size() - 1, k);
	}

	int qs(vector<int>& nums, int i, int j, int k){
		if (i == j)
			return nums[i];

		while (i <= j){
			int r = rank(nums, i, j);
			if (r == k - 1)
				return nums[r];
			else if (r < k - 1)
				i = r + 1;
			else
				j = r - 1;
		}

		return -1;
	}

	int rank(vector<int>& nums, int left, int right){
		// [, ] range
		int i = left;
		int pivot = nums[left];
		left += 1;

		while (left <= right){
			if (nums[left] > pivot){
				while (right >= left && nums[right] >= pivot) --right;
				if (right == left - 1){
					swap(nums[i], nums[right]);
					return right;
				}

				swap(nums[left++], nums[right--]);
			}
			else
				++left;
		}

		swap(nums[i], nums[left - 1]);
		return left - 1;
	}
};

// [ , ) range
class QuickSelect2 {
public:
	int getKth(vector<int>& nums, int k){
		return q(nums, 0, nums.size(), k); 
	}

	int q(vector<int>& nums, int i, int j, int k){
		while (i < j){
			int r = rank(nums, i, j); 
			if (r == k - 1)
				return nums[r];
			else if (r < k - 1)
				i = r + 1;
			else
				j = r; 
		}

		return -1; 
	}

	int rank(vector<int>& nums, int i, int j){
		int pivot = nums[i]; 
		int left = i + 1, right = j; 
		while (left < right){
			if (nums[left]>pivot){
				while (right > left && nums[right - 1] >= pivot) --right; 
				if (right == left){
					swap(nums[i], nums[left - 1]);; 
					return left - 1; 
				}

				swap(nums[left], nums[right - 1]); 
			}
		}

		swap(nums[i], nums[left - 1]); 
		return left - 1;;
	}
}; 

int main() {

	vector<vector<int>> b = {
		{ 0, 0, 1, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 1, 0 },
		{ 1, 1, 0, 1, 1 },
		{ 0, 0, 0, 0, 0 }
	};

	vector<vector<int>> bb = {
		{ 3, 0, 1, 4, 2 },
		{ 5, 6, 3, 2, 1 },
		{ 1, 2, 0, 1, 5 },
		{ 4, 1, 0, 1, 7 },
		{ 1, 0, 3, 0, 5 }
	};

	vector<pair<string, string>> f = {
		{ "MUC", "LHR" }, { "JFK", "MUC" }, { "SFO", "SJC" }, { "LHR", "SFO" }
	};


	vector<pair<int, int>> cc = { { 0, 3 }, { 1, 3 }, { 2, 3 }, { 4, 3 }, { 5, 4 } };

	vector<vector<int>> dd = {
		{ INT_MAX, -1, 0, INT_MAX },
		{ INT_MAX, INT_MAX, INT_MAX, -1 },
		{ INT_MAX, -1, INT_MAX, -1 },
		{ 0, -1, INT_MAX, INT_MAX },
	};


	vector<int> nums = { 2, 6, 7, 12, 14, 19 };

	QuickSelect q;
	QuickSelect2 q2;
	for (int i = 0; i < nums.size(); ++i){
		cout << q.getKth(nums, i + 1) << endl;
	}

	for (int i = 0; i < nums.size(); ++i){
		cout << q2.getKth(nums, i + 1) << endl;
	}
}

