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


struct TreeNode {
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
// Implement a basic calculator to evaluate a simple expression string.

// The expression string contains only non - negative integers, +, -, *, / operators and empty spaces.The integer division should truncate toward zero.

// You may assume that the given expression is always valid.

// Some examples :

// "3+2*2" = 7
// " 3/2 " = 1
// " 3+5 / 2 " = 5

// Note : Do not use the eval built - in library function.


class Solution {
public:
	int calculate(string s) {
		if (s.empty())
			return 0; 

		int res = 0, sign = 1;
		vector<int> vst; 

		for (int i = 0; i < s.size(); ++i){
			char c = s[i]; 

			if (c >= '0' && c <= '9'){
				int num = 0; 
				while (s[i] >= '0' && s[i] <= '9'){
					num = 10 * num + s[i] - '0'; 
					++i; 
				}
				vst.push_back(sign*num); 
				--i; 
			}
			else if (c == '-'){
				sign = -1; 
			}
			else if (c == '+'){
				sign = 1; 
			}
			else if (c == '*' || c == '/'){
				int num = 0; 
				while (s[i]<'0' || s[i]>'9') ++i; 
				while (s[i] >= '0' && s[i] <= '9'){
					num = 10 * num + s[i] - '0'; 
					++i; 
				}
				--i; 

				int top = vst.back(); 
				vst.pop_back(); 
				c == '*' ? vst.push_back(top*num) : vst.push_back(top / num); 
			}
		}

		while (!vst.empty()){
			res += vst.back(); 
			vst.pop_back(); 
		}
		return res; 
	}
};


class Solution2{
public:
	int calculate(string s) {
		auto a = rpn(s); 
		return eval(a); 
	}

	int getPrec(char c){
		switch (c){
		case '+': 
		case '-': return 2; 
		case '*':
		case '/': return 3; 
		}
		return -1; 
	}

	vector<string> rpn(string s){
		string num; 
		vector<string> mstk, opstk; 

		for (auto c : s){
			if (isalnum(c)){
				num.push_back(c); 
			}
			else{
				if (num != ""){
					mstk.push_back(num);
					num = "";
				}

				if (string("+-*/").find(c) != string::npos){
					int prec = getPrec(c); 
					while (opstk.size() && getPrec(opstk.back()[0]) >= prec){
						mstk.push_back(opstk.back()); 
						opstk.pop_back(); 
					}
					opstk.push_back(string(1,c)); 
				}
				else if (c == '(')
					opstk.push_back(string(1, c)); 
				else{
					while (opstk.size() && opstk.back() != "("){
						mstk.push_back(opstk.back()); 
						opstk.pop_back(); 
					}
					opstk.pop_back(); 
				}
			}
			prt1Layer(mstk); 
			prt1Layer(opstk); 
		}

		if (num != "")
			mstk.push_back(num);

		while (opstk.size()){
			mstk.push_back(opstk.back());
			opstk.pop_back();
		}
		return mstk; 
	}

	int eval(vector<string> expr){
		vector<int> stk; 
		for (auto s : expr){
			if (isalnum(s[0]))
				stk.push_back(stoi(s)); 
			else {
				int i1 = stk.back();; 
				stk.pop_back(); 
				int i2 = stk.back(); 
				stk.pop_back(); 

				if (s == "+") stk.push_back(i2 + i1); 
				if (s == "-") stk.push_back(i2 - i1); 
				if (s == "*") stk.push_back(i2 * i1); 
				if (s == "/") stk.push_back(i2 / i1); 
			}
		}
		return stk.back(); 
	}

};


class Solution3{
public:
	int calculate(string s) {
		
	}
}; 


int main(){
	Solution2 a; 
	Solution3 a2; 

	cout << a.calculate("(3-(4+5)*6)/(9-(7)+1)")<<endl<<endl; 
	cout << a2.calculate("(3-(4+5)*6)/(9-(7)+1)")<<endl<<endl; 

	vector<int> b = { 4, 1, -9, 0, INT_MAX }; 


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

