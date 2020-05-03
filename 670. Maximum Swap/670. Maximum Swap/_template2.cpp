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
// Discuss 
// Pick One 


// Given a non-negative integer, you could swap two digits at most once to get the maximum valued number. Return the maximum valued number you could get. 
// Example 1:
// Input: 2736
// Output: 7236
// Explanation: Swap the number 2 and the number 7.

// Example 2:
// Input: 9973
// Output: 9973
// Explanation: No swap.



// pass AC. Lots of pitholes.!!
class Solution {
public:
	int maximumSwap(int num) {
		if (num < 10)
			return num; 

		string n = to_string(num); 

		// 从头开始，期望是递减的。 如果出现递增趋势， 则开始找之后的最大数的最后一个位置
		// 找到之后， 再在前面的这一段找一个 最大的小于其的数， 做交换即可。 
		for (int i = 0; i + 1 < n.size(); ++i){
			if (n[i] >= n[i+1])
				continue;

			int to_exch = findMax(n, i + 1); 
			int pos = findpos(n, i, n[to_exch]); 
			swap(n[pos], n[to_exch]); 
			// remember to break!
			break; 
		}

		return stoi(n);
	}

	int findMax(string& num, int start){
		int std = num[start]; 
		int res = start; 
		for (int i = start + 1; i < num.size(); ++i){
			// '>=' so that if there are multiple max value, you track to the last of it; 
			// eg., 19993
			if (num[i] >= std){
				std = num[i]; 
				res = i; 
			}
		}
		return res; 
	}

	int findpos(string& num, int end, int val){
		if (end == 0)
			return 0; 

		// tricky binary search!!!  
		// we are looking for the ' max of all less number ' , so the range is ( ], 
		// so the starting range is (-1, end]。 because index=0 and index=end are all possible
		// to be chosen, and the >max number will never be chosen, so [0，end) or [0, end] range 
		// is not correct here!!!
		int i = -1, j = end; 
		while (j - 1 > i){
			int mid = i + (j - i) / 2;
			if (num[mid] < val)
				j = mid;
			else
				i = mid; 
		}

		return j; 
	}
};







int main(){
	Solution a;

	vector<int> b = { 7, 2, 5, 10, INT_MAX };

	cout << a.maximumSwap(93808); 

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

