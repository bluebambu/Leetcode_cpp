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

// pass AC
class Solution {
public:
	vector<string> restoreIpAddresses(string s) {
		vector<string> res; 
		helper(s, 0, 4, res, ""); 
		return res;
	}

	void helper(string& s, int cur, int num, vector<string>& res, string prefix){
		if (num == 0 && cur==s.size()){
			prefix.pop_back(); 
			res.push_back(prefix); 
			return; 
		}
		if (num == 0 && cur != s.size())
			return; 
		
		for (int i = cur; i < s.size(); ++i){
			string sub = s.substr(cur, i - cur + 1); 
			if (sub.size() > 3)
				return; 
			if (sub.size()>1 && sub[0] == '0')
				continue;
			if (stoi(sub)>255)
				continue;

			helper(s, i + 1, num - 1, res, prefix + sub + "."); 
		}
	}
};



class Solution2 {
public:
	vector<string> restoreIpAddresses(string s) {
		if (s.size() < 4 || s.size() > 12)
			return{}; 

		vector<string> res;
		dfs(s, 0, 1, "", res); 
		return res; 
	}

	void dfs(string& s, int start, int num, string path, vector<string>& res){
		if (start == s.size() && num == 5){
			res.push_back(path.substr(1)); 
			return; 
		}
		if (start == s.size() || num > 5)
			return; 

		for (int i = start + 1; i <= s.size(); ++i){
			if (i-start > 3)
				break;
			if (i>start + 1 && s[start] == '0')
				break;

			string sub = s.substr(start, i - start); 
			int n = stoi(sub); 
			if (n <= 255){
				dfs(s, i, num + 1, path + "." + sub, res); 
			}
		}
	}
}; 


int main(){
	Solution a; 
	Solution2 a2; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 

	prt2Layer(a.restoreIpAddresses("101100")); 
	prt2Layer(a2.restoreIpAddresses("101100")); 

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

