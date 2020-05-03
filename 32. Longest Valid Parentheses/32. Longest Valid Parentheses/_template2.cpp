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


// wrong ans!!!
class Solution {
public:
	int longestValidParentheses(string s) {
		int n = s.size(); 
		vector<int> cumsum(n + 1, 0); 
		unordered_map<int, set<int>> cumMap; 
		int sum = 0; 
		int neg = -1; 
		int res = 0; 
		for (int i = 0; i < n; ++i){
			sum += (s[i] == '(' ? 1 : -1); 
			if (s[i] == ')'){
				if (cumMap.count(sum) && *(--cumMap[sum].end()) > neg){
					if (cumMap[sum].upper_bound(neg) != cumMap[sum].end()){
						int pre = *(cumMap[sum].upper_bound(neg)); 
						res = max(res, i - pre + 1); 
					}
				}
			}
			if (sum < 0) neg = i; 
			cumMap[sum].insert(i); 
		}
		return res; 
	}
};


class Solution2 {
public:
	int longestValidParentheses(string s) {
		int n = s.size(); 
		vector<int> dp(n, 0); 
		int res = INT_MIN; 
		for (int i = 1; i < dp.size(); ++i){
			int lastLen = dp[i - 1]; 
			if (s[i] == ')' && s[i - lastLen - 1] == '('){
				dp[i] = 2 + lastLen + (i - lastLen - 2 >= 0 ? dp[i - lastLen - 2] : 0); 
				res = max(res, dp[i]); 
			}
		}

		return res;
	}
};


int main(){
	Solution a; 
	Solution2 a2; 
	string s = "(()()"; 

	cout << a.longestValidParentheses(s) << endl; 
	cout << a2.longestValidParentheses(s) << endl; 


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

