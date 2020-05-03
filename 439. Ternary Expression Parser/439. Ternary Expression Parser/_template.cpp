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

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }


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
		for (int i = 0; i<n; ++i){
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

template <typename T>
void vprt(vector<T> v){
	for (auto i : v)
		cout << v << " ";
	cout << endl;
}

template <typename T>
void vvprt(vector<vector<T>> v){
	for (auto i : v){
		for (auto j : i){
			cout << j << " ";
		}
		cout << endl;
	}
	cout << endl;
}

template <typename C>
void setprt(C v){
	for (auto i : v)
		cout << i << " ";
	cout << endl;
}

template <typename C>
void mapprt(C v){
	for (auto i : v)
		cout << i.first << " " << i.second << endl;
	cout << endl;
}
////////////////////////////////////////////////////////////////
// Given a string representing arbitrarily nested ternary expressions, calculate the result of the expression.You 
// can always assume that the given expression is valid and only consists of digits 0 - 9, ? , : , T and F(T and F 
// represent True and False respectively).

// Note :
// 	 The length of the given string is ≤ 10000.
// 	 Each number will contain only one digit.
// 	 The conditional expressions group right - to - left(as usual in most languages).
// 	 The condition will always be either T or F.That is, the condition will never be a digit.
// 	 The result of the expression will always evaluate to either a digit 0 - 9, T or F.

// 	 Example 1:
// Input : "T?2:3"

// Output : "2"



// 	 Explanation : If true, then result is 2; otherwise result is 3.

// 				   Example 2:
// 	Input : "F?1:T?4:5"

// 	Output : "4"

// 		 Explanation : The conditional expressions group right - to - left.Using parenthesis, it is read / evaluated as :

// 		"(F ? 1 : (T ? 4 : 5))"                   "(F ? 1 : (T ? 4 : 5))"
// 			-> "(F ? 1 : 4)"                 or       -> "(T ? 4 : 5)"
// 			-> "4"                                    -> "4"

// 			Example 3:
// 	Input : "T?T?F:5:3"

// 	Output : "F"

// 		 Explanation : The conditional expressions group right - to - left.Using parenthesis, it is read / evaluated as :

// 		"(T ? (T ? F : 5) : 3)"                   "(T ? (T ? F : 5) : 3)"
// 			-> "(T ? F : 3)"                 or       -> "(T ? F : 5)"
// 			-> "F"                                    -> "F"


// dfs with index reference!!  Pass AC
class Solution {
public:
	string parseTernary(string expression) {
		int i = 0; 
		return helper(expression, i); 
	}
	string helper(string& exp, int& idx){
		string res; 
		while (exp[idx] >= '0' && exp[idx] <= '9'){
			res += exp[idx++]; 
		}
		if ((exp[idx] == 'T' || exp[idx] == 'F') && idx<exp.size() && (idx == exp.size() - 1 || exp[idx + 1] != '?')){
			res += exp[idx++]; 
		}
		if (res != "")
			return res; 

		bool isfirst = false; 
		if (exp[idx] == 'T')
			isfirst = true; 

		idx += 2; 
		string first = helper(exp, idx);
		idx += 1; 
		string second = helper(exp, idx); 

		return isfirst ? first : second;
	}
};


class Solution2 {
public:
	string parseTernary(string expression) {
		if (expression.empty())
			return ""; 

		stack<string> st; 
		st.push(expression); 

		while (!st.empty()){
			string top = st.top(); 
			st.pop(); 

			if (isExp(top)){
				vector<string> splited = split(top);
				if (splited[0] == "T")
					st.push(splited[1]);
				else
					st.push(splited[2]);
			}
			else
				return top; 
		}
		return ""; 
	}

	bool isExp(string s){
		for (int i = 0; i < s.size(); ++i){
			if (s[i] == '?')
				return true; 
		}
		return false; 
	}

	vector<string> split(string s){
		int p = -1, c = -1, cnt = 0; 
		for (int i = 0; i < s.size(); ++i){
			if (s[i] == '?'){
				if (p == -1)
					p = i;
				else
					++cnt; 
			}
			if (s[i] == ':'){
				if (cnt == 0){
					c = i; 
					break;
				}
				--cnt;
			}
		}

		return{
			s.substr(0, p),
			s.substr(p + 1, c - p - 1),
			s.substr(c + 1)
		};
	}
};


// above solutions are all N2 solution. this one is O(N). 
class Solution3 {
public:
	string parseTernary(string expression) {
		stack<string> stk; 
		stk.push(""); 

		for (int i = 0; i < expression.size(); ++i){
			char c = expression[i]; 
			if (c == '?'){
				string cur = "";
				cur.push_back(expression[i - 1]); 
				cur.push_back(c); 
				stk.push(cur); 
			}
			else if (c == ':'){
				stk.top() += c; 
			}
			else{
				if (i + 1<expression.size() && expression[i + 1] == '?')
					continue;

				stk.top() += c; 
				while (stk.top().size() >=2 && stk.top()[stk.top().size() - 2] == ':'){
					string cur = stk.top(); 
					stk.pop(); 
					stk.top() += (cur[0] == 'T' ? cur[2] : cur[4]); 
				}
			}
		}

		return stk.top(); 
	}
};

class Solution4 {
public:
	string parseTernary(string expression) {
		int i = 0; 
		return parse(expression, i); 
	}

	string parse(string& expr, int& i){
		if (isdigit(expr[i])){
			int  j = i + 1; 
			while (isdigit(expr[j])) ++j; 
			string res = expr.substr(i, j - i); 
			i = j; 
			return res; 
		}

		char c = expr[i]; 
		i += 2; 
		string left = parse(expr, i); 
		i += 1; 
		string right = parse(expr, i); 

		return c == 'T' ? left : right; 
	}
}; 


int main(){
	Solution2 a;
	Solution4 a2;
	string exp = "T?T?F:5:3";
	string exp2 = "F?T?F?7:F?F?F?3:F?F?0:1:0:6:1:0:5"; 
	cout << a.parseTernary(exp2) << endl; 
	cout << a2.parseTernary(exp2) << endl;

	//    TreeNode* tree = new TreeNode(6,new TreeNode(3, new TreeNode(1), new TreeNode(4)),new TreeNode(8, new TreeNode(7), new TreeNode(9)));
	TreeNode* tree = new TreeNode(6, new TreeNode(3, new TreeNode(1),
		new TreeNode(4)),
		new TreeNode(8, new TreeNode(7),
		new TreeNode(9)));
	/*      6
	3       8
	1    4   7    9

	*/


}