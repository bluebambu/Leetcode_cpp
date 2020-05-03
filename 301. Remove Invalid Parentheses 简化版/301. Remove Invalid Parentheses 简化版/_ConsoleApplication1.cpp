// _template4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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

typedef vector<int> VI; 
typedef vector<VI> VVI; 
typedef pair<int, int> PII; 

VVI dirs = { { 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 } }; 


class Solution {
public:
	string removeParen(string s){
		string r; 
		int score = 0; 
		for (int i = 0; i < s.size(); ++i){
			switch (s[i]){
			case '(': r.push_back(s[i]); score += 1; break;
			case ')':
				if (score > 0) {
					r.push_back(s[i]); 
					score -= 1;
				}
				break;
			}
		}

		reverse(r.begin(), r.end()); 
		for (int i = 0; i < r.size(); ++i){
			switch (r[i]){
			case '(': r[i] = ')'; break; 
			case ')': r[i] = '('; break; 
			}
		}

		s = ""; 
		score = 0; 
		for (int i = 0; i < r.size(); ++i){
			switch (r[i]){
			case '(': s.push_back(r[i]); score += 1; break;
			case ')':
				if (score > 0) {
					s.push_back(r[i]); 
					score -= 1;
				}
				break;
			}
		}

		return s;
	}
};

class Solution2 {
public:
	string removeParen(string s){
		s = strip(s); 
		s = reverse(s); 
		s = strip(s); 
		return reverse(s); 
	}
	string strip(string s){
		string r; 
		int score = 0; 
		for (int i = 0; i < s.size(); ++i){
			switch (s[i]){
			case '(': 
				score += 1; 
				r.push_back('('); 
				break;
			case ')':
				if (score > 0){
					score -= 1; 
					r.push_back(')'); 
				}
				break;
			default:
				r.push_back(s[i]); 
			}
		}
		return r; 
	}
	string reverse(string& s){
		string r; 
		for (int i = s.size() - 1; i >= 0; --i){
			switch (s[i]){
			case '(': 
				r.push_back(')'); 
				break;
			case ')':
				r.push_back('('); 
				break;
			default:
				r.push_back(s[i]); 
			}
		}
		return r; 
	}
}; 


int main(){
	Solution2 a;
	string str = "()))()))";//")()(()))))))(()())()((((" will bloat the memory
	string str2 = ")()(()))))))(()";
	string str3 = "(r(()()(";
	string str4 = "()r)r)";

	cout << a.removeParen(str) << endl; 
	cout << a.removeParen(str2) << endl; 
	cout << a.removeParen(str3) << endl; 
	cout << a.removeParen(str4) << endl; 


	//TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6,
		new TreeNode(3, new TreeNode(1),
						new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
						new TreeNode(9,
		                               new TreeNode(10),
		                               nullptr)));
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

