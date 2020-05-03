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
// Given an integer array of size n, find all elements that appear more 
// than [ n / 3 ]  times.The algorithm should run in linear time and in 
// O(1) space.



// wrong answer
// 主要错误在于： cand1 和 cand2 都不等于 nums[i]时，应该同时 --cnt1，--cnt2.   然后最后要验证。 
class Solution2 {
public:
	vector<int> majorityElement(vector<int>& nums) {
		int cand1 = 0, cand2 = 0, cnt1 = 0, cnt2 = 0; 
		for (int i = 0; i < nums.size(); ++i){
			if (cnt1 == 0 && cnt2 == 0){
				cand1 = nums[i];
			}
			else if (cnt1 != 0 && cnt2 == 0){
				cand2 = nums[i];
			} else if (cnt1 == 0 && cnt2 != 0){
				cand1 = nums[i];
			}

			if (cand1 != nums[i] && cand2 != nums[i] && cnt2 > 0)
				cnt2 -= 1;
			else if (cand1 != nums[i] && cand2 != nums[i] && cnt1 > 0)
				cnt1 -= 1; 
			else if (cand1 == nums[i])
				cnt1 += 1;
			else if (cand2 == nums[i])
				cnt2 += 1; 
		}

		return vector<int>{cand1, cand2}; 
	}
};



class Solution {
public:
	vector<int> majorityElement(vector<int>& nums) {
		vector<int> res;
		int m = 0, n = 0, cm = 0, cn = 0;
		for (auto &a : nums) {
			if (a == m) ++cm;
			else if (a == n) ++cn;
			else if (cm == 0) m = a, cm = 1;
			else if (cn == 0) n = a, cn = 1;
			else --cm, --cn;
		}
		cm = cn = 0;
		for (auto &a : nums) {
			if (a == m) ++cm;
			else if (a == n) ++cn;
		}
		if (cm > nums.size() / 3) res.push_back(m);
		if (cn > nums.size() / 3) res.push_back(n);
		return res;
	}
};


// pass AC
class Solution3 {
public:
	vector<int> majorityElement(vector<int>& nums) {
		vector<int> res; 
		int cand1 = 0, cand2 = 0, cnt1 = 0, cnt2 = 0; 
		for (int i = 0; i < nums.size(); ++i){
			// if else 的顺序不能错， 要先查cand1 和 cand2 的值， 再查count。 否则遇到两个一样的
			// 值，就会分别assign给 cand1 和 cand2， 而不是都记在一个candidate上面!!!! 
			if (cand1 == nums[i])
				cnt1 += 1;
			else if (cand2 == nums[i])
				cnt2 += 1;
			else if (cnt1 == 0)
				cand1 = nums[i], cnt1=1;
			else if (cnt2 == 0)
				cand2 = nums[i], cnt2=1;
			else
				--cnt1, --cnt2; 
		}

		cnt1 = 0, cnt2 = 0; 
		for (auto a : nums){
			if (a == cand1)
				++cnt1; 
			else if (a == cand2)
				++cnt2; 
		}

		if (cnt1 > nums.size() / 3) res.push_back(cand1); 
		if (cnt2 > nums.size() / 3) res.push_back(cand2); 

		return res; 
	}
};

class Solution4 {
public:
    vector<int> majorityElement(vector<int>& nums) {
		int n1=INT_MAX, n2=INT_MAX, c1 = 0, c2 = 0; 
		for (int i = 0; i < nums.size(); ++i){
			//if (c1 == 0 )
			//	n1 = nums[i], c1 = 1;
			//else if (nums[i] == n1)
			//	c1 += 1;
			//else if (c2 == 0)
			//	n2 = nums[i], c2 = 1;
			//else if (nums[i] == n2)
			//	c2 += 1; 

			if (nums[i] == n1 || nums[i] == n2){
				nums[i] == n1 ? c1 += 1 : c2 += 1; 
			}
			else if (c1 == 0 || c2 == 0){
				c1 == 0 ? (n1 = nums[i], c1 = 1) : (n2 = nums[i], c2 = 1); 
			}
			else
				--c1, --c2; 
		}

		int tot1 = 0, tot2 = 0;
		for (int i = 0; i < nums.size(); ++i){
			nums[i] == n1 ? tot1 += 1 : (nums[i] == n2 ? tot2 += 1 : true); 
		}
		
		vector<int> res; 
		if (tot1 > nums.size()/3)res.push_back(n1);
		if (tot2 > nums.size()/3)res.push_back(n2); 

		return res; 
    }
};

class Solution5 {
public:
	vector<int> majorityElement(vector<int>& nums) {
		if (nums.empty())
			return{}; 

		int cand1, cnt1 = 0, cand2, cnt2 = 0; 
		for (int i = 0; i < nums.size(); ++i){
			int c = nums[i]; 
			if (cnt1 == 0 && (cnt2 == 0 || cand2 != c))
				cand1 = c, cnt1 = 1;
			else if (cnt2 == 0 && cand1 != c)
				cand2 = c, cnt2 = 1;
			else if (cand1 == c)
				++cnt1;
			else if (cand2 == c)
				++cnt2;
			else
				--cnt1, --cnt2; 
		}
		
		cnt1 = 0, cnt2 = 0; 
		for (int i = 0; i < nums.size(); ++i){
			if (nums[i] == cand1) ++cnt1; 
			else if (nums[i] == cand2) ++cnt2; 
		}

		vector<int> res; 
		if (cnt1 > nums.size() / 3) res.push_back(cand1); 
		if (cnt2 > nums.size() / 3) res.push_back(cand2); 

		return res;
	}
};



int main(){
	Solution4 a;
	Solution5 a5;

	vector<int> b = { 5, 4, 8, 8, 3, 8, 8, 5, 4, 4, 4 }; 
	vector<int> b2 = { 8, 8, 8, 4, 4, 8, 8, 8 }; 
	vector<int> b3 = { 1, 2, 2, 3, 2, 1, 1, 3 }; 
	vector<int> b4 = { 2,2}; 
	vector<int> b5 = { 2,2}; 

	vector<int> c = a.majorityElement(b5);
	prt1Layer(c); 

	c = a5.majorityElement(b5);
	prt1Layer(c); 
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

