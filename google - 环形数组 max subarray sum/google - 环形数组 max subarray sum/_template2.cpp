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
	// double arr solution
	int cycleSubarray(vector<int>& nums) {
		vector<int> db = nums; 
		db.insert(db.end(), nums.begin(), nums.end()); 

		int curSubSum = db[0], preSubSum, res = curSubSum; int len = 1;
		int n = nums.size(); 

		for (int i = 1; i < 2 * n; ++i){
			preSubSum = curSubSum; 
			if (preSubSum < 0){
				curSubSum = db[i]; 
				len = 1; 
			}
			else{
				curSubSum = preSubSum + db[i]; 
				len += 1; 
				if (len == n){
					return curSubSum; 
				}
			}

			res = max(res, curSubSum); 
		}

		return res; 
	}


	int cycleSubarray2(vector<int> nums){
		int n = nums.size(); 
		int curMax, preMax, curMin, preMin, res = INT_MIN; 
		curMax = curMin = nums[0]; 

		int total = 0; 
		for (int i = 0; i < n; ++i)
			total += nums[i]; 

		for (int i = 1; i < n; ++i){
			preMax = curMax, preMin = curMin; 
			curMax = preMax > 0 ? preMax + nums[i] : nums[i]; 
			curMin = preMin < 0 ? preMin + nums[i] : nums[i]; 
			res = max(res, max(curMax, total - curMin)); 
		}

		return res;
	}
};


class Solution5{
public:
	int cicleMaxSub(vector<int>& nums){
		int localMax = nums[0], localMin = nums[0], gmax = INT_MIN, gmin = INT_MAX;
		int tot = 0; 
		for (int i = 1; i < nums.size(); ++i){
			if (localMax > 0){
				localMax += nums[0]; 
				localMin = nums[0]; 
			}
			else{
				localMax = nums[0]; 
				localMin += nums[0]; 
			}
			gmax = max(gmax, localMax); 
			gmin = min(gmin, localMin); 
			tot += nums[i]; 
		}

		return max(gmax, tot - gmin); 
	}
};





int main(){
	Solution a; 

	vector<int> b = { 2, 1, -4, -2, 1, -7, 5, 1 }; 

	cout << a.cycleSubarray(b) << endl; 
	cout << a.cycleSubarray2(b) << endl; 


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

