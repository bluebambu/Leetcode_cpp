// _template4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
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
    bool isNumber(string s) {
		int i = 0; 
		while (i < s.size() && s[i] == ' ') ++i; 
		if (s[i] == '+' || s[i] == '-')
			++i; 
		int j = i ; 

		while (j < s.size() && isdigit(s[j])) ++j; 
		string positive_interger = s.substr(i, j - i); 
		bool good_interger = check_interger(positive_interger); 
		if (!good_interger) return false; 
		if (j == s.size()) return true; 

		if (s[j] == '.'){
			i = j + 1; 
			j = i; 
			while (j < s.size() && isdigit(s[j])) ++j; 
			string decimal = s.substr(i, j - i); 
            if(decimal=="") return false; // "." case
			bool good_decimal = check_decimal(decimal); 
			if (!good_decimal) return false; 
			if (j == s.size()) return true; 
		}

		if (s[j] == 'e'){
            if(positive_interger=="") return false; // "e" case
			i = j + 1; 
			j = i; 
			if (s[j] == '+' || s[j] == '-')
				++j, ++i; 
			while (j < s.size() && isdigit(s[j])) ++j;
			string positive_interger2 = s.substr(i, j - i);
			good_interger = check_interger(positive_interger2);
			if (!good_interger) return false; 
			if (j == s.size()) return true; 
		}

        if(s[j]==' '){ // trailing ' '  cases. 
            while(j<s.size() && s[j]==' ')++j; 
            return j==s.size(); 
        }
		return false; 
    }

	bool check_interger(string& num){
		int i = 0, j = 0; 
		while (j < num.size() && num[j] == '0') ++j; 
		if (j - i>1) return false; 
		i = j; 
		while (i < num.size() && isdigit(num[i])) ++i; 
		return i == num.size(); 
	}

	bool check_decimal(string& num){
		int i = 0; 
		while (i < num.size() && isdigit(num[i])) ++i; 
		return i == num.size(); 
	}
};


class Solution2 {
public:
	bool isNumber(string s) {
		int l = s.find_first_not_of(' '), r = s.find_last_not_of(' ');
		if (l == -1)// s only contains spaces
			return false;

		s = s.substr(l, r - l + 1);
		int i = 0;
		bool pass_dot = false, pass_e = false;
		int pos_dot = -1, pos_e = -1, pos_op = -1; 
		for (; i < s.size(); ++i){
			if (i == 0){
				if (!isdigit(s[i]) && s[i] != '+' && s[i] != '-' && s[i] != '.')
					return false;
				if (s[i] == '+' || s[i] == '-')
					pos_op = 0; 
			}

			if (i > 0 && !isdigit(s[i]) && s[i] != '.' && s[i] != 'e')
				return false;

			if (pass_dot && s[i] == '.')
				return false;
			if (pass_e && s[i] == 'e')
				return false;
			if (pass_e && s[i] == '.')
				return false;

			if (s[i] == '.') {
				pass_dot = true;
				pos_dot = i;
			}
			if (s[i] == 'e') {
				pass_e = true;
				pos_e = i;
			}

		}

		return pos_e != s.size() - 1 && !(pos_dot == s.size() - 1 && pos_dot == 0) && pos_e != 0 && !(pos_e >= 0 && pos_dot >= 0 && pos_e == pos_dot + 1) && (pos_dot>=0 && pos_op>=0 && pos_dot-pos_op>1);
	}
};;

int main(){
	Solution2 a;

	string s = ".";

	cout << a.isNumber(s) << endl; 



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

