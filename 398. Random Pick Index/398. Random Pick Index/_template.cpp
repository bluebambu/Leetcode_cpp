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

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }


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
		for (int i = 0; i<n; ++i){
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

template <typename T>
void vprt(vector<T> v){
	for (auto i : v)
		cout << v << " ";
	cout << endl;
}

template <typename T>
void vvprt(vector<vector<T>> v){
	for (auto i : v){
		for (auto j : i){
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <typename C>
void setprt(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
// Given an array of integers with possible duplicates, randomly output the index of a given target number.You can assume that the given target number must exist in the array.
// Note:
// The array size can be very large.Solution that uses too much extra space will not pass the judge.
// Example :
// 		int[] nums = new int[] {1, 2, 3, 3, 3};
// Solution solution = new Solution(nums);

// // pick(3) should return either index 2, 3, or 4 randomly. Each index should have equal probability of returning.
// solution.pick(3);

// // pick(1) should return 0. Since in the array only nums[0] is equal to 1.
// solution.pick(1);



class Solution {
	vector<int> vec; 
public:
	Solution(vector<int> nums):vec(nums) { }

	int pick(int target) {
		int cnt = 0, res = -1;
		for (int i = 0; i < vec.size(); ++i){
			if (vec[i] == target){
				cnt += 1; 
				if (rand() % cnt == 0)
					res = i; 
			}
		}
		return res; 
	}
};

/**
* Your Solution object will be instantiated and called as such:
* Solution obj = new Solution(nums);
* int param_1 = obj.pick(target);
*/

class Solution2 {
public:
	vector<int> core; 
	Solution2(vector<int> nums) {
		core = nums; 
	}

	int pick(int target) {
		int cnt = 0; 
		int res; 
		auto iter = core.begin(); 
		while (iter != core.end()){
			if (*iter == target){
				cnt += 1; 
				if (rand() % cnt == 0){
					res = iter-core.begin();
				}
			}
			++iter; 
		}
		return res; 
	}
};


int main() {
	
	vector<int> b = {  1, 2, 3, 3, 3 }; 
	Solution2 a(b);

	unordered_map<int, int> m; 
	for (int i = 0; i < 100000; ++i){
		int r = a.pick(3); 
		m[r] += 1; 
	}

	for (auto p : m){
		cout << p.first << " --> " << p.second << endl; 
	}
	

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/


}

