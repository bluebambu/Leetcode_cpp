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
// You have 4 cards each containing a number from 1 to 9. You need to judge whether they could operated through *, /, +, -, (, ) to get the value of 24.

//Example 1:

//Input: [4, 1, 8, 7]
//Output: True
//Explanation: (8-4) * (7-1) = 24

//Example 2:

//Input: [1, 2, 1, 2]
//Output: False

//Note:

//    The division operator / represents real division, not integer division. For example, 4 / (1 - 2/3) = 12.
//    Every operation done is between two numbers. In particular, we cannot use - as a unary operator. For example, with [1, 1, 1, 1] as input, the expression -1 - 1 - 1 - 1 is not allowed.
//    You cannot concatenate numbers together. For example, if the input is [1, 2, 1, 2], we cannot write this as 12 + 12.


// pass AC
double eps = 0.0001; 

class Solution {
public:
	bool judgePoint24(vector<int>& nums){
		vector<double> a(nums.begin(), nums.end()); 
		return helper(a); 
	}

	bool helper(vector<double> nums_o) {
		if (nums_o.size() == 1)
			return fabs(nums_o[0] - 24.0) < eps; // fabs is necessary!!

		int n = nums_o.size(); 
		bool res = false; 
		for (int i = 0; i < n; ++i){
			for (int j = i + 1; j < n; ++j){
				vector<double> nums = nums_o;;

				double a = nums[i], b = nums[j]; 
				nums.erase(nums.begin() + j); // use begin() + i to accurate delete
				nums.erase(nums.begin() + i); 

				nums.push_back(a + b); 
				res |= helper(nums); 
				nums.pop_back(); 

				nums.push_back(a - b); 
				res |= helper(nums); 
				nums.pop_back(); 

				nums.push_back(b - a); 
				res |= helper(nums); 
				nums.pop_back(); 

				nums.push_back(a * b); 
				res |= helper(nums); 
				nums.pop_back(); 

				if (fabs(b - 0.0) > eps){ // equality of double number
					nums.push_back(a / b);
					res |= helper(nums);
					nums.pop_back();
				}

				if (fabs(a - 0.0) > eps){
					nums.push_back(b / a);
					res |= helper(nums);
					nums.pop_back();
				}
			}
		}

		return res; 
	}
};


// wrong ans. Relative pos of nums should be able to be shuffled, but this ans does not consider this. 
class Solution2 {
public:
	bool judgePoint24(vector<int>& nums){
		vector<double> r = dfs(vector<double>(nums.begin(), nums.end())); 
		sort(r.begin(), r.end()); 
		prt1Layer(r); 
		return find_if(r.begin(), r.end(), [](double i){return i == 24;  }) != r.end();
	}

	vector<double> dfs(vector<double> nums){
		if (nums.size() == 1)
			return nums; 

		unordered_set<double> res; 

		for (int i = 1; i < nums.size(); ++i){
			vector<double> left = vector<double>(nums.begin(), nums.begin() + i),
				right = vector<double>(nums.begin() + i, nums.end()),
				rl = dfs(left), 
				rr = dfs(right); 

			for (auto a : rl){
				for (auto b : rr){
					res.insert(a + b); 
					res.insert(a - b); 
					res.insert(a*b); 
					if (b!=0.0)
						res.insert(a / b); 
				}
			}

		}

		return vector<double>(res.begin(), res.end()); 
	}
};


// wrong ans, because the order of numbers can be moved. 
class Solution3 {
public:
	double eps = 0.000001; 

	bool judgePoint24(vector<int>& nums){
		return judge(nums); 
	}
	bool judge(vector<double>& nums){
		if (nums.size() == 1 && nums[0] == 24.0)
			return true; 
		if (nums.size() == 1 && nums[0] != 24.0)
			return false; 

		for (int i = 1; i < nums.size(); ++i){
			double d1 = nums[i - 1], d2 = nums[i]; 
			
			double add = d1 + d2; 
			vector<double> vadd(nums.begin(), nums.begin() + i - 1); 
			vadd.push_back(add); 
			vadd.insert(vadd.end(), nums.begin() + i + 1, nums.end()); 
			if (judge(vadd)) return true; 

			double minus = d1 - d2; 
			vector<double> vminus(nums.begin(), nums.begin() + i - 1); 
			vminus.push_back(minus); 
			vminus.insert(vminus.end(), nums.begin() + i + 1, nums.end()); 
			if (judge(minus)) return true; 

			double multi = d1 * d2; 
			vector<double> vmulti(nums.begin(), nums.begin() + i - 1); 
			vmulti.push_back(multi); 			vmulti.insert(vmulti.end(), nums.begin() + i + 1, nums.end());
			if (judge(vmulti)) return true; 

			double div = d1 / d2; 
			vector<double> vdiv(nums.begin(), nums.begin() + i - 1); 
			vdiv.push_back(div); 
			vdiv.insert(vdiv.end(), nums.begin() + i + 1, nums.end()); 
			if (judge(vdiv)) return true; 
		}

		return false; 
	}
};

int main(){
	Solution a; 
	Solution2 a2; 

	vector<int> b = { 1, 2, 1, 2 }; 
	vector<int> b2 = { 4, 1, 8, 7 }; 

	cout << a.judgePoint24(b2) << endl; 
	cout << a2.judgePoint24(b2) << endl;

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
