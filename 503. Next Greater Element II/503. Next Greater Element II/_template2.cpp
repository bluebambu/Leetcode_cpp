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



class Solution {
public:
	vector<int> nextGreaterElements(vector<int> nums) {
		if (nums.empty())
			return{}; 

		int maxv = nums[0], maxid = 0; 
		for (int i = 0; i < nums.size(); ++i){
			if (nums[i] > maxv){
				maxv = nums[i]; 
				maxid = i; 
			}
		}


		int n = nums.size(), cnt = 0; 
		deque<vector<int>> res; 
		deque<vector<int>> r2; 
		for (int j = maxid; cnt < nums.size(); j = (j + n - 1) % n, ++cnt){
			while (!res.empty() && res.front()[0] <= nums[j])
				res.pop_front(); 

			if (res.empty()){
				res.push_front({ nums[j], -1 }); 
				r2.push_front({ nums[j], -1 }); 
			}
			else{
				r2.push_front({ nums[j], res.front()[0] }); 
				res.push_front({ nums[j], res.front()[0] }); 
			}
		}

		for (int i = r2.size() - 1; i != maxid; --i){
			r2.push_back(r2.front()); 
			r2.pop_front(); 
		}

		vector<int> v(n); 
		transform(r2.begin(), r2.end(), v.begin(), [](vector<int>& a){return a[1]; });

		return v; 
	}
};

// wrong ans! 
class Solution2{
public:
	vector<int> nextGreaterElements(vector<int> nums){
		if (nums.empty())
			return{}; 

		vector<int> stk; 
		vector<int> res(nums.size(), -1); 
		for (int i = 0; i < nums.size(); ++i){
			int cur = nums[i]; 
			if (stk.empty() || cur <= nums[stk.back()])
				stk.push_back(i); 
			else{
				while (!stk.empty() && cur > nums[stk.back()]){
					int smaller_id = stk.back(); 
					stk.pop_back(); 

					res[smaller_id] = cur; 
				}
				stk.push_back(i); 
			}
		}

		int high_val = nums[stk[0]]; 
		for (int i = 1; i < stk.size(); ++i){
			if (nums[stk[i]] < high_val){
				res[stk[i]] = high_val; 
			}
		}

		return res; 
	}
};

class Solution3{
public:
	vector<int> nextGreaterElements(vector<int> nums){
		vector<int> stk; 
		vector<int> res(nums.size(), -1); 
		for (int k = 0; k < 2; ++k){
			for (int i = 0; i < nums.size(); ++i){
				if (stk.empty() || nums[i] <= nums[stk.back()])
					stk.push_back(i); 
				else{
					while (!stk.empty() && nums[stk.back()] < nums[i]){
						int smaller = stk.back(); 
						stk.pop_back(); 
						res[smaller] = nums[i]; 
					}
					stk.push_back(i); 
				}
			}
		}

		return res; 
	}
}; 


int main(){
	Solution a; 
	Solution3 a2; 

	vector<int> b = { 2, 1, 2 };
	vector<int> b2 = { 1, 2, 3, 2, 1 };
	vector<int> b3 = { 1,2,1}; 

	prt1Layer(a.nextGreaterElements(b2)); 
	prt1Layer(a2.nextGreaterElements(b2)); 


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

