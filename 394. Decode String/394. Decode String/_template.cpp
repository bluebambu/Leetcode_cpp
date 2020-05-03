// _template.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <list>
#include <vector>
#include <algorithm>    // std::for_each
#include <unordered_map>
#include <queue>
#include <stack>

using namespace std;

inline int exchg(int &a, int &b)  { int c = a; a = b; b = c; }
inline int log2(int N){ return log10(N) / log10(2); }
inline float min(float a, float b) { return a<b ? a : b; }


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

// Given an encoded string, return it's decoded string.

// The encoding rule is : k[encoded_string], where the encoded_string inside the square brackets is being 
// repeated exactly k times.Note that k is guaranteed to be a positive integer.

// You may assume that the input string is always valid; No extra white spaces, square brackets are well - formed, etc.

// Furthermore, you may assume that the original data does not contain any digits and that digits are only for those 
// repeat numbers, k.For example, there won't be input like 3a or 2[4].

// Examples:

// s = "3[a]2[bc]", return "aaabcbc".
// s = "3[a2[c]]", return "accaccacc".
// s = "2[abc]3[cd]ef", return "abcabccdcdcdef".

class Solution {
public:
	string decodeString(string s) {
		int i = 0; 
		return helper(s, i); 
	}

	// 貌似 dfs + reference 是解决这种结构的问题： ([][])([][{}{}][]) 
	// 就是pattern之间存在串联， tandem
	// 而 dfs 是解决这种问题： （（（（（）））））
	// 没有串联
	string helper(string s, int& i){
		string res; 
		int n = s.size(); 
		while (i < n && s[i] != ']'){
			if (s[i]<'0' || s[i]>'9'){
				res.push_back(s[i++]);
			}
			else{
				int cnt = 0; 
				while (s[i] >= '0' && s[i] <= '9' && i < n){
					cnt = 10 * cnt + s[i] - '0';
					++i;
				}
				++i; // this is '['
				string t = helper(s, i);
				++i; // this is ']'
				for (int j = 0; j < cnt; ++j){
					res += t; 
				}
			}
		}
		return res;
	}																						
};


class Solution2 {
public:
	string decode(string s){
		int i = 0; 
		return helper(s, i);
	}

	string helper(string s, int& i){
		string res = "";
		int n = s.size(); 
		while (i < n && s[i]!=']'){ // 这里 ！= 】 是必须的，用来在一个括号结束后停止while循环！！ 也可以将这个放到下面的判断条件里。 
			if (s[i]<'0' || s[i]>'9')// && s[i]!=']') 就像这样.
				res += s[i++]; 
			else{
				int cnt = 0;
				while (s[i] >= '0' && s[i] <= '9'){
					cnt = cnt * 10 + s[i] - '0'; 
					++i;
				}
				++i; 
				string next = helper(s, i);
				++i; 
				for (int j = 0; j < cnt ; ++j)
					res += next; 
			}
		}
		return res; 
	}
};


// iteration is much easier.....
// 2018-07-23 wrong ans now... but can borrow the idea. 
class Solution3 {
public:
	string decode(string s){
		stack<string> wstk; 
		stack<int>	nstk; 

		for (int i = 0; i < s.size(); ++i){
			if (s[i] >= '0' && s[i] <= '9'){
				nstk.push(s[i] - '0'); 
			}
			else if (s[i] == '['){
				wstk.push(""); 
			}
			else if (s[i] == ']'){
				string tmp = ""; 
				for (int i = 0; i < nstk.top(); ++i){
					tmp += wstk.top(); 
				}
				wstk.pop(); 
				nstk.pop(); 
				if (wstk.empty())
					return tmp;
				wstk.top() += tmp; 
			}
			else{
				wstk.top().push_back(s[i]); 
			}
		}

		return ""; 

	}
};


class Solution4 {
public:
	string decodeString(string s) {
		string res;
		int id = 0;
		return dfs(id, s);
	}

	string dfs(int& i, string& s){
		string res; 
		for (; i < s.size(); ++i){
			if (s[i] == ']')
				break; 

			if (isalpha(s[i]))
				res.push_back(s[i]); 
			else{
				int j = i; 
				while (j < s.size() && s[j] != '[') ++j; 
				int num = stoi(s.substr(i, j - i)); 

				i = j + 1; 
				string next = dfs(i, s); 
				for (int k = 0; k < num; ++k)
					res += next; 
			}
		}
		return res; 
	}
};


class Solution5 {
public:
	string decodeString(string s) {
		string res; 
		stack<int> stk1; 
		stack<string> stk2; 
		stk1.push(1); stk2.push(""); 

		for (int i = 0; i < s.size(); ++i){
			char c = s[i]; 
			if (isdigit(c)){
				int j = i + 1, sum = c-'0'; 
				while (j < s.size() && isdigit(s[j])) sum = sum * 10 + s[j] - '0', ++j; 
				stk1.push(sum); 
				i = j - 1; 
			}
			else if (c == '['){
				stk2.push(""); 
			}
			else if (c == ']'){
				string res; 
				for (int i = 0; i < stk1.top(); ++i)
					res += stk2.top(); 
				stk1.pop(); stk2.pop(); 
				stk2.top() += res; 
			}
			else
				stk2.top().push_back(c); 
		}
		return stk2.top(); 
	}
};


class Solution6 {
public:
	string decodeString(string s) {
		int i = 0; 
		return dfs(s, i); 
	}

	string dfs(string& s, int& i){
		string res; 
		for (; i < s.size(); ++i){
			char c = s[i]; 
			if (isdigit(s[i])){
				int j = i + 1, sum=s[i]-'0'; 
				while (j < s.size() && isdigit(s[j])) sum = 10 * sum + s[j] - '0', ++j; 
				i = j + 1; 
				string cur = dfs(s, i); 
				while (sum > 0){
					res += cur; 
					--sum; 
				}
			}else if (isalpha(s[i]))
				res.push_back(s[i]); 
			else{
				break;
			}
		}
		return res; 
	}
}; 

class Solution7 {
public:
	string decodeString(string s) {
		int i = 0; 
		return d(s, i); 
	}
	string d(string& s, int& i){
		string res; 
		while (i < s.size()){
			char c = s[i]; 
			if (isalpha(c))
				res.push_back(c); 
			else if (isdigit(c)){
				int j = i + 1; 
				while (j < s.size() && isdigit(s[j])) ++j; 
				string num = s.substr(i, j - i); 
				i = j + 1; 
				string content = d(s, i); 
				int n = stoi(num); 
				for (int k = 0; k < n; ++k){
					res += content; 
				}
			}
			else if(c==']'){
				return res; 
			}
			++i; 
		}

		return res; 
	}
}; 

int main() {
	Solution7 a;

	string b = a.decodeString("2[abc]3[cd]ef");
	cout << b << endl; 

	b = a.decodeString("2[a4[b2[z]]a]grg10[a]");
	cout << b << endl; 

}
