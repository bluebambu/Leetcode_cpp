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
	int longestConsecutive(vector<int>& nums) {
		unordered_map<int, bool> unvisited; 
		for (auto i : nums)
			unvisited[i] = true; 

		int res = INT_MIN; 
		for (int i = 0; i < nums.size(); ++i){
			if (unvisited[nums[i]]){
				int cur = 1; 
				for (int j = nums[i] + 1; unvisited[j]; ++j) {
					++cur;
					unvisited[j] = false; 
				}
				for (int j = nums[i] - 1; unvisited[j]; --j) {
					++cur;
					unvisited[j] = false; 
				}; 
				res = max(res, cur); 
			}
		}

		return res; 
	}
};

// pass
class Solution2 {
public:
	int longestConsecutive(vector<int>& nums) {
		unordered_map<int, int> cnts; 
		for (auto i : nums) cnts[i] += 1; 

		int len = 0, start, end; 
		for (int i : nums){
			if (cnts[i]){
				cnts[i] -= 1; 
				int curlen = 1; 
				int j = i; 
				while (cnts[j - 1]) ++curlen, --j, cnts[j] -= 1;
				int k = i; 
				while (cnts[k + 1]) ++curlen, ++k, cnts[k] -= 1; 
				if (curlen > len){
					len = curlen; 
					start = j + 1; 
					end = k - 1; 
				}
			}
		}

		return len; 
	}
};

class Solution3 {
public:
	int longestConsecutive(vector<int>& nums) {
		// sort(nums.begin(), nums.end()); prt1Layer(nums); 
		unordered_map<int, int> bndry_cnt; 
		int res = 0; 
		for (auto i : nums){
			if (bndry_cnt[i]) continue;

			int left_len = bndry_cnt[i - 1],
				right_len = bndry_cnt[i + 1]; 
			int len = left_len + 1 + right_len; 

			int left_node = i - left_len,
				right_node = i + right_len; 
			if (len > bndry_cnt[left_node])
				bndry_cnt[left_node] = len; 
			if (len > bndry_cnt[right_node])
				bndry_cnt[right_node] = len; 

			bndry_cnt[i] = len; // must have!! make sure all the numbers in all ranges are registered in hashtable!!

			res = max(res, len); 

			mapprt(bndry_cnt); 
		}
		return res; 
	}
}; 


int main(){
	Solution3 a;

	vector<int> b = { 100, 4, 200, 1, 3, 2 }; 
	vector<int> b2 = { 1, 2, 0, 1 }; 
	vector<int> b3 = { 4, 0, -4, -2, 2, 5, 2, 0, -8, -8, -8, -8, -1, 7, 4, 5, 5, -4, 6, 6, -3 }; 

	cout << a.longestConsecutive(b3) << endl; 


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

