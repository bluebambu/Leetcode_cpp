// _template.cpp : Defines the entry point for the console application.
//
#include <stdafx.h>

#include <iostream>
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
// Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.

// Note that it is the kth smallest element in the sorted order, not the kth distinct element.
// Example:

// matrix = [
// 	[1, 5, 9],
// 		[10, 11, 13],
// 		[12, 13, 15]
// ],
// k = 8,

// return 13.

// Note:
// You may assume k is always valid, 1 ¡Ü k ¡Ü n2.


// pass AC

// this problem is not a typical binary search, it is more like Finding first rank K element. 
// Reason: [1,3,5,6,9,10], let's say this is the array, and we want to find the 4th elem. 
// if on the value range, possible solution can be: 6,7,8. What we want is 6, which is always the first
// member within all 4th rank elements. 

// So this binary search is infact looking for the first kth tanking elements. 



class Solution {
public:
	// if use open-closed structure, only reasonable solution is ( ] range. 
	// maxPos + ( , ] 
	int kthSmallest(vector<vector<int>>& matrix, int k) {
		int n = matrix.size();
		int le = matrix[0][0]-1, ri = matrix[n - 1][n - 1], mid;

		while (le < ri-1){
			mid = le + (ri - le) / 2;
			int rank = calcMaxRank(matrix, mid);
			if (rank < k)
				le = mid;
			else
				ri = mid;
		}

		return ri;
	}

	// if use close-close structure, [ ] should be fine;  
	// maxPos + [ , ]
	int kthSmallest2(vector<vector<int>>& matrix, int k) {
		int n = matrix.size();
		int le = matrix[0][0], ri = matrix[n - 1][n - 1], mid;

		while (le < ri){
			mid = le + (ri - le) / 2;
			int rank = calcMaxRank(matrix, mid);
			if (rank < k)
				le = mid+1;
			else
				ri = mid;
		}

		return ri;
	}

	int calcMaxRank(vector<vector<int>>& mtx, int num){
		int cnt = 0, n = mtx.size(), i = n - 1, j = 0;
		while (i >= 0 && j < n){
			if (mtx[i][j] <= num){
				cnt += i + 1;
				++j;
			}
			else
				--i;
		}
		return cnt;
	}
};


class Solution2 {
public:
	// maxPos + [ , ]
	int kthSmallest(vector<vector<int>>& matrix, int k) {
		int left = matrix[0][0], right = matrix.back().back(); 
		while (left < right){
			int mid = left + (right - left) / 2; 
			int p = maxpos(matrix, mid); 
			if (p >= k)
				right = mid;
			else
				left = mid+1; 
		}
		return left; 
	}

	int maxpos(vector<vector<int>>& mtx, int num){
		int n = mtx.size(), m = mtx[0].size(), i = n - 1, j = 0, cnt = 0; 
		while (true){
			if (mtx[i][j] <= num){
				cnt += i + 1; 
				++j; 
			}
			if (j==m) break;

			while (i >= 0 && mtx[i][j]>num) --i;
			if (i<0) break;
		}
		return cnt; 
	}

	// minPos + [ , )
	int kthSmallest2(vector<vector<int>>& matrix, int k) {
		if (matrix.empty() || matrix[0].empty())
			return 0; 

		int left = matrix[0][0], right = matrix.back().back() + 1; // [ , )
		while (left + 1 < right){
			int mid = left + (right - left) / 2;
			int p = minpos(matrix, mid);
			if (p <= k)
				left = mid;
			else
				right = mid;
		}
		return left;
	}


	int minpos(vector<vector<int>>& mtx, int num){
		int n = mtx.size(), m = mtx[0].size(), i = n - 1, j = 0, cnt = 0;

		while (true){
			if (mtx[i][j] < num){
				cnt += i + 1; 
				++j; 
			}
			if (j==n) break;

			while (i >= 0 && mtx[i][j] >= num)--i; 
			if (i<0) break;
		}

		return cnt + 1; 
	}

	// this is wrong. [ , ] can not solve with minpos() 
	int kthSmallest3(vector<vector<int>>& matrix, int k) {
		if (matrix.empty() || matrix[0].empty())
			return 0;

		int left = matrix[0][0], right = matrix.back().back(); // [ , ]
		while (left < right){
			int mid = left + (right - left) / 2;
			int p = minpos(matrix, mid);
			if (p <= k)
				left = mid;
			else
				right = mid;
		}
		return left;
	}
}; 



class Solution3 {
public:
	int kthSmallest(vector<vector<int>>& matrix, int k) {
		int left = matrix[0][0], right = matrix.back().back() + 1; //[ , )  
		while (left + 1 < right){
			int mid = left + (right - left) / 2; 
			if (minRank(matrix, mid) < k)
				left = k;
			else
				right = k; 
		}
		return left; 
	}

	int kthSmallest2(vector<vector<int>>& matrix, int k) {
		int left = matrix[0][0], right = matrix.back().back(); 
		while (left < right){
			int mid = left + (right - left) / 2; 
			if (maxRank(matrix, mid) < k)
				left = k;
			else
				right = k; 
		}
		return left; 
	}

	int minRank(vector<vector<int>>& matrix, int value){
		int n = matrix.size(), m = matrix[0].size(); 
		int i = n - 1, j = 0; 
		int res = 0; 
		while (i >= 0 && j < m){
			int c = matrix[i][j]; 
			if (c >= value)
				--i;
			else{
				res += i + 1; 
				++j; 
			}
		}
		return res; 
	}

	int maxRank(vector<vector<int>>& matrix, int value){
		int n = matrix.size(), m = matrix[0].size(); 
		int i = n - 1, j = 0; 
		int res = 0; 
		while (i >= 0 && j < m){
			int c = matrix[i][j]; 
			if (c > value)
				--i;
			else{
				res += i + 1; 
				++j; 
			}
		}
		return res; 
	}
}; 



int main(){
	Solution a; 
	Solution2 a2; 

	vector<vector<int>> b = {
		{1, 5, 9}, 
		{10, 11, 13}, 
		{12, 13, 16}
	};

	cout << a.kthSmallest2(b, 8); 
	cout << a2.kthSmallest2(b, 8);


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

