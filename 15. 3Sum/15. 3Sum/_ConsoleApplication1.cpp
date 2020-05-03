// _template4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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

typedef vector<int> VI; 
typedef vector<VI> VVI; 
typedef pair<int, int> PII; 

VVI dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 

// TLE
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
		if (nums.size() < 3) return{}; 
		unordered_map<int, set<vector<int>>> sum_to_val; 
		set<vector<int>> res; 
		sum_to_val[nums[0] + nums[1]].insert({ nums[0], nums[1] });
		for (int i = 2; i < nums.size(); ++i){
			int tgt = -1 * nums[i]; 
			if (sum_to_val.count(tgt)){
				for (auto v : sum_to_val[tgt]){
					v.push_back(nums[i]); 
                    sort(v.begin(), v.end()); 
					res.insert(v); 
				}
			}
			for (int j = 0; j < i; ++j){
				sum_to_val[nums[j] + nums[i]].insert({ nums[j], nums[i] }); 
			}
		}
		return vector<vector<int>>(res.begin(), res.end());
    }
};


// two pointer
class Solution2 {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		sort(nums.begin(), nums.end()); 
		vector<vector<int>> res; 
		for (int i = 0; i < nums.size(); ){
			int j = i + 1, k = nums.size() - 1; 
			int tgt = -1 * nums[i]; 
			while (j < k){
				int tmp = nums[j] + nums[k]; 
				if (tmp < tgt)
					++j;
				else if (tmp > tgt)
					--k; 
				else{
					res.push_back({ nums[i], nums[j], nums[k] }); 
					int j_val = nums[j], k_val = nums[k]; 
					while (j < k && nums[j] == j_val) ++j; 
					while (j < k && nums[k] == k_val) --k; 
				}
			}
			int i_val = nums[i]; 
			while (i < nums.size() && nums[i] == i_val) ++i; 
		}
		return res; 
	}
};


int main(){
	Solution2 a;

	vector<int> b = { -1, 0, 1, 2, -1, -4 }; 


	auto c = a.threeSum(b); 
	prt2Layer(c);


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6,
		new TreeNode(3, new TreeNode(1),
						new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
						new TreeNode(9,
		                               new TreeNode(10),
		                               nullptr)));
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

