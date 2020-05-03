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
	int calculate(string s){
		vector<string> numstk, opstk; 
		for (int i = 0; i < s.size(); ++i){
			char c = s[i]; 
			// cout << c << endl; 
			if (isOp(c)){
				while (opstk.size() && isOp(opstk.back().at(0)) && opPrec(opstk.back().at(0)) >= opPrec(c)){
					string cur = opstk.back(); 
					opstk.pop_back(); 
					numstk.push_back(cur); 
				}
				opstk.push_back(string() + c); 
			}
			else if (isdigit(c)){
				int j = i + 1; 
				while (j < s.size() && isdigit(s[j])) ++j; 
				string n = s.substr(i, j - i); 
				numstk.push_back(n); 
				i = j - 1; 
			}
			else if (c == '('){
				opstk.push_back(string() + c); 
			}
			else if (c == ')'){
				while (!opstk.empty() && opstk.back() != "("){
					string cur = opstk.back(); 
					opstk.pop_back(); 
					numstk.push_back(cur); 
				}
				opstk.pop_back(); 
			}
		}
		
		return rpn(numstk, opstk); 
	}

	int rpn(vector<string>& numstk, vector<string>& opstk){
		while (!opstk.empty()){
			numstk.push_back(opstk.back()); 
			opstk.pop_back(); 
		}

		vector<int> res;
		for (int i = 0; i < numstk.size(); ++i){
			string cur = numstk[i]; 
			if (isdigit(cur.at(0))){
				res.push_back(stoi(cur)); 
			}
			else{
				int n2 = res.back(); res.pop_back(); 
				int n1 = res.back(); res.pop_back(); 

				int r; 
				switch (cur.at(0)) {
				case '+': r = n1 + n2; break;
				case '-': r = n1 - n2; break;
				}

				res.push_back(r); 
			}
		}

		return res.back(); 
	}

	bool isOp(char c){
		return c == '+' || c == '-'; 
	}

	int opPrec(char c){
		switch (c) {
		case '+': return 0; 
		case '-': return 1; 
		}
	}
};

class Solution2 {
public:
	int calculate(string s){
		stack<int> numstk, signstk; 
		numstk.push(0); 
		signstk.push(1); 
		int sign = 1, num; 
		for (int i = 0; i < s.size(); ++i){
			if (isdigit(s[i])){
				int j = i + 1; 
				while (j < s.size() && isdigit(s[j])) ++j; 
				string n = s.substr(i, j - i); 
				num = stoi(n); 
				numstk.top() += sign * num; 
			}
			else if (s[i] == '+')
				sign = 1;
			else if (s[i] == '-')
				sign = -1;
			else if (s[i] == '(') {
				numstk.push(0); 
				signstk.push(sign); 
				sign = 1; 
			}
			else if (s[i] == ')'){
				int cur = numstk.top() * signstk.top(); 
				numstk.pop(); signstk.pop(); 
				numstk.top() += cur; 
			}
		}

		return numstk.top(); 
	}
}; 

class Solution3 {
public:
	int calculate(string s){
		int i = 0; 
		return dfs(s, i); 
	}

	int dfs(string& s, int& i){
		int r = 0, sign = 1; 
		for (; i < s.size(); ++i){
			char c = s[i]; 
			if (isdigit(c)){
				int j = i + 1; 
				while (j < s.size() && isdigit(s[j])) ++j; 
				string num = s.substr(i, j - i); 
				r += sign * stoi(num); 
			}
			else if (c == '+')
				sign = 1;
			else if (c == '-')
				sign = -1; 
			else if (c == '('){
				++i; 
				int k = dfs(s, i); 
				r += sign * k; 
			}
			else if (c == ')'){
				return r; 
			}
		}

		return r; 
	}
}; 


class Solution4 {
public:
	int calculate(string s){
		int i = 0; 
		return calculate(s, i);
	}

	int calculate(string& s, int& i){
		int sign = 1, res = 0; 
		for (; i < s.size(); ++i){
			char c = s[i];
			if (c == '+')
				sign = 1;
			if (c == '-')
				sign = -1;
			if (isdigit(c)){
				int j = i + 1;
				while (j < s.size() && isdigit(j)) ++j;
				int n = stoi(s.substr(i, j - i));
				res += sign*n;
				i = j - 1;
			}
			if (c == '(')
				res += sign*calculate(s, ++i);
			if (c == ')')
				break;
		}
		return res; 
	}
	
}; 


int main(){
	Solution a;
	Solution4 a2;

	string expr = "(1 - (2-1))-(8-4+(7-5))"; 

	cout << a.calculate(expr) << endl;
	cout << a2.calculate(expr) << endl;

	///////////////////////////
	auto start = std::chrono::high_resolution_clock::now();
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	cout << endl << microseconds << " microseconds elapsed..." << endl;
}