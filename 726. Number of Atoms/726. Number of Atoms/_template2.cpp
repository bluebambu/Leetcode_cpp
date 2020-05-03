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
	string countOfAtoms(string formula) {
		int i = formula.size() - 1; 
		auto vv = count(formula, i); 
		map<string, int> v(vv.begin(), vv.end()); 

		string res; 
		for (auto p : v)
			res = res + p.first + (p.second==1 ? "" : to_string(p.second)); 
		return res; 
	}

	unordered_map<string, int> count(string s, int& i){
		unordered_map<string, int> res; 
		if (i < 0)
			return res; 
		if (s[i] == '(')
			return res; // Na(OH*(*SO3))2  this '(' is hard to pass over. 

		int j = i;
		while (i >= 0 && s[i] >= '0'&&s[i] <= '9') --i;
		string num = s.substr(i + 1, j - i);
		int curNum = num=="" ? 1 : stoi(num); 
		if (s[i] == ')'){
			auto sub = count(s, --i); 
			for (auto p : sub)
				res[p.first] += curNum*p.second; 
			--i; 
		}
		else{
			int k = i; 
			while (i >= 0 && s[i]>='a' && s[i]<='z') --i; 
			res[s.substr(i, k - i + 1)] += curNum; 
			--i; 
		}
		
		auto next = count(s, i); 
		for (auto p : next)
			res[p.first] += p.second;
		
		return res; 
	}
};


class Solution2 {
public:
	void countOfAtoms(string formula) {
		// K4(ON(SO3)2)3
		int i = 0; 
		unordered_map<string, int> r = dfs(formula, i); 

		for (auto p : r)
			cout << p.first << "->" << p.second << endl; 
	}

	unordered_map<string, int> dfs(string formula, int& pos){
		unordered_map<string, int> res; 
		while (pos < formula.size()){
			char c = formula[pos]; 
			if (formula[pos] == '('){
				unordered_map<string, int> cur = dfs(formula, ++pos);
				++pos;
				int n; 

				if (pos < formula.size() && (isupper(formula[pos]) || formula[pos]==')'|| formula[pos]=='(')) {
					n = 1; 
				}
				else if (pos < formula.size() && isdigit(formula[pos])){
					int j = pos + 1; 
					while (j < formula.size() && isdigit(formula[j])) ++j; 
					string num = formula.substr(pos, j - pos); 
					pos = j; 
					n = stoi(num); 
				}

				for (auto p : cur)
					res[p.first] += n*p.second;
			}
			else if (isalpha(formula[pos])){
				int j = pos + 1; 
				while (j < formula.size() && islower(formula[j])) ++j; 
				string elem = formula.substr(pos, j - pos); 
				pos = j; 
				if (pos == formula.size() || isupper(formula[pos]) || formula[pos] == '(')
					res[elem] += 1; 
				else{
					j = pos + 1; 
					while (j < formula.size() && isdigit(formula[j])) ++j; 
					string num = formula.substr(pos, j - pos); 
					pos = j; 
					res[elem] += stoi(num); 
				}
			} else if (formula[pos] == ')')
				break;
		}
		return res; 
	}
};



int main(){
	Solution a; 
	Solution2 a2; 
	string formula = "Na(OH(SO3))2";

	cout << a.countOfAtoms(formula)<<endl; 
	a2.countOfAtoms(formula); 

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

