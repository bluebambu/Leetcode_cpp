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
// Implement a basic calculator to evaluate a simple expression string.

// The expression string may contain open(and closing parentheses), the plus + or minus sign - , non - negative integers and empty spaces .

// You may assume that the given expression is always valid.

// Some examples :

// "1 + 1" = 2
// " 2-1 + 2 " = 3
// "(1+(4+5+2)-3)+(6+8)" = 23

// Note : Do not use the eval built - in library function.

// if you intend to push everything in stack first, even though here
// is only '+' and '-', you still need to set priority for them, i.e., use
// the classical approach

// pass AC!!
class Solution{
public:
	int calculate(string s){
		stack<int> st; 
		int sign = 1, res = 0; 

		for (int i = 0; i < s.size(); ++i){
			char c = s[i]; 

			if (c >= '0' && c <= '9'){
				int num = 0;
				while (s[i] >= '0' && s[i] <= '9'){
					num = num * 10 + s[i] - '0'; 
					++i; 
				}
				res += sign*num; 
				--i;
			}
			else if (c == '+'){
				sign = 1; 
			}
			else if (c == '-'){
				sign = -1; 
			}
			else if (c == '('){
				st.push(res); 
				st.push(sign); 
				res = 0; 
				sign = 1;
			}
			else if (c == ')'){
				res = res*st.top(); 
				st.pop(); 
				res += st.top(); 
				st.pop(); 
			}
		}
		return res; 
	}
};

// java
//
//int calculate(string s) {
//	stack<int> stack; 
//	int result = 0;
//	int number = 0;
//	int sign = 1;
//	for (int i = 0; i < s.length(); i++){
//		char c = s.charAt(i);
//		if (Character.isDigit(c)){
//			number = 10 * number + (int)(c - '0');
//		}
//		else if (c == '+'){
//			result += sign * number;
//			number = 0;
//			sign = 1;
//		}
//		else if (c == '-'){
//			result += sign * number;
//			number = 0;
//			sign = -1;
//		}
//		else if (c == '('){
//			//we push the result first, then sign;
//			stack.push(result);
//			stack.push(sign);
//			//reset the sign and result for the value in the parenthesis
//			sign = 1;
//			result = 0;
//		}
//		else if (c == ')'){
//			result += sign * number;
//			number = 0;
//			result *= stack.pop();    //stack.pop() is the sign before the parenthesis
//			result += stack.pop();   //stack.pop() now is the result calculated before the parenthesis

//		}
//	}
//	if (number != 0) result += sign * number;
//	return result;
//}

class Solution2{
public:
	int calculate(string s){
		vector<int> nst; 
		int res = 0, sign = 1; 

		for (int i = 0; i < s.size(); ++i){
			char c = s[i]; 
			if (c >= '0' && c <= '9'){
				int num = 0; 
				while (s[i] >= '0' && s[i] <= '9') {
					num = 10 * num + s[i] - '0'; 
					++i; 
				}
				res += sign*num; 
				--i; 
			}
			else if (c == '+'){
				sign = 1; 
			}
			else if (c == '-'){
				sign = -1; 
			}
			else if (c == '('){
				nst.push_back(res); 
				nst.push_back(sign); 
				res = 0; 
				sign = 1; 
			}
			else if (c == ')'){
				res = res*nst.back(); 
				nst.pop_back(); 
				res += nst.back(); 
				nst.pop_back(); 
			}
		}
		return res; 
	}
};


// wrong ans
class Solution3 {
public:
	int calculate(string s) {
		stack<string> stk; 
		stk.push(""); 

		for (int i = 0; i < s.size(); ++i){
			char c = s[i]; 
			if (c == '(')
				stk.push("");
			else if (c == ')')
			{
				string cur = stk.top(); 
				stk.pop(); 
				stk.top() += to_string(process(cur)); 
			}
			else
				stk.top() += c; 
		}

		return process(stk.top()); 
	}

	int process(string s){
		int res = 0; 
		int f = 1; 
		for (int i = 0; i < s.size(); ++i){
			if (s[i] == '+')
				f = 1;
			else if (s[i] == '-')
				f = -1; 
			else if (s[i] == ' ')
				continue;
			else{
				int j = i + 1, sum = s[i] - '0'; 
				while (j < s.size() && isdigit(s[j]))
					sum = sum * 10 + s[j] - '0', ++j; 
				i = j - 1; 
				res += f*sum; 
			}
		}
		return res; 
	}
};

class Solution4 {
public:
	int calculate(string s) {
		stack<int> sgstk; 
		stack<long long> nstk; 
		sgstk.push(1); 
		nstk.push(0); 
		int sign = 1; 

		for (int i = 0; i < s.size(); ++i){
			char c = s[i]; 
			if (isdigit(c)){
				int j = i + 1; long long sum = c - '0';
				while (j < s.size() && isdigit(s[j]))
					sum = 10 * sum + s[j] - '0', ++j; 
				nstk.top() += sum*sign; 
				i = j - 1; 
			}
			else if (c == '+')
				sign = 1;
			else if (c == '-')
				sign = -1; 
			else if (c == '('){
				sgstk.push(sign); 
				sign = 1; 
				nstk.push(0); 
			}
			else if (c == ')'){
				int cur = sgstk.top() * nstk.top(); 
				sgstk.pop(); 
				nstk.pop(); 
				nstk.top() += cur; 
			}
		}
		return nstk.top(); 
	}
}; 

// pass , int & 
class Solution5 {
public:
	int calculate(string s) {
		int i = 0;
		return dfs(s, i); 
	}

	int dfs(string& s, int& i){
		long long res = 0, sign = 1; 
		for (; i < s.size(); ++i){
			char c = s[i];
			if (isdigit(c)){
				int j = i + 1; 
				long long sum = c - '0';
				while (j < s.size() && isdigit(s[j]))
					sum = 10 * sum + s[j] - '0', ++j; 
				i = j - 1; 
				res += sign*sum; 
			}
			else if (c == '+')
				sign = 1;
			else if (c == '-')
				sign = -1; 
			else if (c == '('){
				++i; 
				res += sign * dfs(s, i); 
			}
			else if (c == ')'){
				return res; 
			}else
				continue;
		}
		return res; 
	}
}; 



int main(){
	Solution2 a; 
	Solution5 a2;

	cout << a.calculate("(1 - (4 - 5 + 2) - 3) + (6 - 8)")<<endl;
	cout << a2.calculate("(1 - (4 - 5 + 2) - 3) + (6 - 8)")<<endl;
	a2.calculate("2147483647"); 


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

