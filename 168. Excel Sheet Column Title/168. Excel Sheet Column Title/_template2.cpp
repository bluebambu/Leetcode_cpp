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
	string convertToTitle(int n) {
		string res; 
		while (n >= 0){
			int major = (n-1)/26, minor = (n - 1) % 26 + 1; 
			char last = 'A' + minor - 1; 
			res.push_back(last); 
			n = major; 
			if (n==0)
				break;
		}
		reverse(res.begin(), res.end()); 
		return res; 
	}
};

class Solution2 {
public:
	string convertToTitle(int n) {
		string res; 
		while (n != 0){
			res.push_back('A' + (n - 1) % 26); 
			n = (n - 1) / 26; 
		}
		return string(res.rbegin(), res.rend()); 
	}
}; 

class Solution3 {
public:
	string convertToTitle(int n) {
		if (n < 27)
			return string()+ char('A' + n - 1); 
		int div = (n - 1) / 26;
		return convertToTitle(div) + char('A' + (n - 1) % 26); 
	}
}; 


class Solution4 {
public:
	string convertToTitle(int n) {
		string res; 
		while (n) {
			int rem = (n - 1) % 26; 
			res.push_back('A' + rem); 
			n = (n - 1) / 26; 
		}
		return string(res.rbegin(), res.rend()); 
	}
}; 


int main(){
	Solution a; 
	Solution3 a2; 
	cout << a.convertToTitle(1) << endl; 
	cout << a.convertToTitle(26) << endl; 
	cout << a.convertToTitle(27) << endl; 
	cout << a.convertToTitle(28) << endl; 
	cout << a.convertToTitle(153) << endl; 

	cout << "====" << endl; 
	cout << a2.convertToTitle(1) << endl; 
	cout << a2.convertToTitle(26) << endl; 
	cout << a2.convertToTitle(27) << endl; 
	cout << a2.convertToTitle(28) << endl; 
	cout << a2.convertToTitle(153) << endl; 

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

