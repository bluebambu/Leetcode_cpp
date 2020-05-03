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
// Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.

// Example 1

// Input: "2-1-1".

// ((2-1)-1) = 0
// (2-(1-1)) = 2

// Output: [0, 2]

// Example 2
// Input: "2*3-4*5"

// (2*(3-(4*5))) = -34
// ((2*3)-(4*5)) = -14
// ((2*(3-4))*5) = -10
// (2*((3-4)*5)) = -10
// (((2*3)-4)*5) = 10

// Output: [-34, -14, -10, -10, 10]
class Solution {
public:
	vector<int> diffWaysToCompute(string input) {
		vector<int> res; 

		int i = 0; 
		for (; i < input.size(); ++i){
			char c = input[i]; 
			if (!isalnum(input[i])){
				string left = input.substr(0, i),
					right = input.substr(i + 1); 

				auto l = diffWaysToCompute(left), r = diffWaysToCompute(right);
				for (auto a : l){
					for (auto b : r){
						if (c == '+') res.push_back(a + b); 
						if (c == '-') res.push_back(a - b); 
						if (c == '*') res.push_back(a * b); 
						if (c == '/') res.push_back(a / b); 
					}
				}
			}
		}
		
		if (res.size() == 0) res.push_back(stoi(input)); 
		return res; 
	}
}; 


class Solution2 {
public:
	vector<int> diffWaysToCompute(string input) {
		auto r = decode(input); 
		return vector<int>(r.begin(), r.end()); 
	}

	unordered_set<int> decode(string input) {
		unordered_set<int> res; 
		for (int i = 0; i < input.size(); ++i){
			if (isOp(input[i])){
				string pre = input.substr(0, i), post = input.substr(i + 1); 
				unordered_set<int> r1 = decode(pre), r2 = decode(post); 

				for (auto& a : r1){
					for (auto& b : r2){
						switch (input[i]) {
						case '+':res.insert(a + b); break;
						case '-':res.insert(a - b); break;
						case '*':res.insert(a*b); break;
						case '/':res.insert(a / b); break;
						}
					}
				}
			}
		}

		if (res.empty())
			return{ stoi(input) };
		else
			return res; 
	}

	bool isOp(char c){
		return c == '+' || c == '-' || c == '*' || c == '/'; 
	}
};


int main(){
	Solution a; 
	Solution2 a2; 

	auto b = a.diffWaysToCompute("1-2-3*4/7-3"); 
	prt1Layer(b); 

	auto b2 = a2.diffWaysToCompute("1-2-3*4/7-3"); 
	prt1Layer(b2); 

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

