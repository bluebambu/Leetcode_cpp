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

// need to handle int overflow cases. 
class Solution3{
public:
	int calculate(string s){
		vector<string> nstk, opstk;

		for (int i = 0; i < s.size(); ++i){
			char c = s[i];
			if (isdigit(c)){
				int j = i + 1;
				string sum;
				sum.push_back(c);
				while (j < s.size() && isdigit(s[j]))
				{
					sum.push_back(s[j]);
					++j;;
				}
				i = j - 1;
				nstk.push_back(sum);
			}
			else if (c == '(')
				opstk.push_back(string() + c);
			else if (c == ')'){
				while (opstk.back() != "("){
					nstk.push_back(opstk.back());
					opstk.pop_back();
				}
				opstk.pop_back();
			}
			else if (c == ' ')
				continue;
			else{
				int prec = preced(c);
				while (!opstk.empty() && preced(opstk.back()[0]) >= prec){
					nstk.push_back(opstk.back());
					opstk.pop_back();
				}
				opstk.push_back(string() + c);
			}
		}

		while (!opstk.empty()){
			nstk.push_back(opstk.back());
			opstk.pop_back();
		}

		return process(nstk);
	}

	int preced(char c){
		switch (c){
		case'+':
		case'-': return 1;
		case'*':
		case'/': return 2;
		}
		return -1;
	}

	int process(vector<string>& v){
		vector<long long> stk;
		for (auto& s : v){
			if (isdigit(s[0]))
				stk.push_back(stoll(s));
			else{
				long long a = stk.back();
				stk.pop_back();
				long long b = stk.back();
				stk.pop_back();

				switch (s[0]){
				case'+':stk.push_back(b + a); break;
				case'-':stk.push_back(b - a); break;
				case'*':stk.push_back(b * a); break;
				case'/':stk.push_back(b / a); break;
				}
			}
		}
		return stk.back();
	}
};


class Solution4{
public:
	int calculate(string s){
		deque<string> nums; 
		stack<char> ops;
		for (int i = 0; i < s.size(); ++i){
			char c = s[i]; 
			if (isdigit(c)){
				int j = i + 1; 
				while (j < s.size() && isdigit(s[j])) ++j; 
				string n = s.substr(i, j - i); 
				i = j - 1;
				nums.push_back(n); 
			}
			else if (isop(c)){
				while (!ops.empty() && isop(ops.top()) && prio(c)>prio(ops.top())){
					char o = ops.top(); 
					ops.pop(); 
					nums.push_back(string(o)); 
				}
				ops.push(c); 
			}
			else if (c == '(')
				ops.push(c); 
			else if (c == ')'){
				while (!ops.empty() && ops.top() != '('){
					char o = ops.top(); 
					ops.pop(); 
					nums.push_back(string(0)); 
				}
				ops.pop(); 
			}
		}

		while (!ops.empty()){
			char o = ops.top();
			ops.pop();
			nums.push_back(string(0));
		}

		return rpn(nums); 
	}

	bool isop(char c){
		return c == '+' || c == '-' || c == '*' || c == '/'; 
	}
	int prio(char c){
		switch (c){
		case '+':return 1; 
		case '-':return 1; 
		case '*':return 2; 
		case '/':return 2; 
		}
	}
	int rpn(deque<string>& nums){
		stack<int> stk; 
		for (int i = 0; i < nums.size(); ++i){
			string cur = nums[i]; 
			if (isop(cur[0])){
				int a = stk.top(); stk.pop(); 
				int b = stk.top(); stk.pop(); 
			}
		}
	}
}; 


int main(){
	Solution a;

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

